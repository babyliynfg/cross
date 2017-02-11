//
//  CATableView.cpp
//  CrossApp
//
//  Created by Li Yuanfeng on 14-4-28.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#include "CATableView.h"
#include "CAImageView.h"
#include "CAScale9ImageView.h"
#include "basics/CAApplication.h"
#include "basics/CAScheduler.h"
#include "dispatcher/CATouch.h"
#include "support/CAPointExtension.h"
#include "CCEGLView.h"
#include "animation/CAViewAnimation.h"
#include "platform/CADensityDpi.h"
#include "support/CAThemeManager.h"
#include "support/ccUtils.h"
NS_CC_BEGIN

#pragma CATableView

CATableView::CATableView()
:m_pTableHeaderView(NULL)
,m_pTableFooterView(NULL)
,m_pDraggingOutCell(NULL)
,m_obSeparatorColor(ccc4Int(0xffefeef4))
,m_nSeparatorViewHeight(1)
,m_nTableHeaderHeight(0)
,m_nTableFooterHeight(0)
,m_nSections(0)
,m_pTableViewDataSource(NULL)
,m_pTableViewDelegate(NULL)
,m_bAllowsSelection(false)
,m_bAllowsMultipleSelection(false)
,m_bAlwaysTopSectionHeader(true)
,m_bAlwaysBottomSectionFooter(true)
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CACell");
    m_obSeparatorColor = ccc4Int(CrossApp::hex2Int(map.at("separatorColor")));
}

CATableView::~CATableView()
{
    for (auto& pair : m_mpFreedTableCells)
    {
        pair.second.clear();
    }
    m_vpUsedTableCells.clear();
    m_mpFreedTableCells.clear();
    m_pFreedLines.clear();
    this->clearData();
    
    CC_SAFE_RELEASE_NULL(m_pTableHeaderView);
    CC_SAFE_RELEASE_NULL(m_pTableFooterView);
    m_pTableViewDataSource = NULL;
    m_pTableViewDelegate = NULL;
}

void CATableView::onEnterTransitionDidFinish()
{
    CAScrollView::onEnterTransitionDidFinish();
    
    CAViewAnimation::beginAnimations("", NULL);
    CAViewAnimation::setAnimationDuration(0);
    CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation0_selector(CATableView::firstReloadData));
    CAViewAnimation::commitAnimations();
}

void CATableView::onExitTransitionDidStart()
{
    CAScrollView::onExitTransitionDidStart();
}

CATableView* CATableView::createWithFrame(const DRect& rect)
{
    CATableView* tableView = new CATableView();
    if (tableView && tableView->initWithFrame(rect))
    {
        tableView->autorelease();
        return tableView;
    }
    CC_SAFE_DELETE(tableView);
    return NULL;
}

CATableView* CATableView::createWithCenter(const DRect& rect)
{
    CATableView* tableView = new CATableView();
    if (tableView && tableView->initWithCenter(rect))
    {
        tableView->autorelease();
        return tableView;
    }
    CC_SAFE_DELETE(tableView);
    return NULL;
}

CATableView* CATableView::createWithLayout(const CrossApp::DLayout &layout)
{
    CATableView* tableView = new CATableView();
    if (tableView && tableView->initWithLayout(layout))
    {
        tableView->autorelease();
        return tableView;
    }
    CC_SAFE_DELETE(tableView);
    return NULL;
}

bool CATableView::init()
{
    if (!CAScrollView::init())
    {
        return false;
    }
    
    this->setShowsHorizontalScrollIndicator(false);
    this->setBounceHorizontal(false);
    this->setHorizontalScrollEnabled(false);
    return true;
}

void CATableView::setContentSize(const CrossApp::DSize &var)
{
    CAScrollView::setContentSize(var);
    
    if (!m_mpUsedTableCells.empty())
    {
        this->reloadData();
    }
}

bool CATableView::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
    if (!CAScrollView::ccTouchBegan(pTouch, pEvent))
        return false;
    
    return true;
}

void CATableView::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
    CC_RETURN_IF(m_vTouches.contains(pTouch) == false);
    CAScrollView::ccTouchMoved(pTouch, pEvent);
}

void CATableView::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
    CC_RETURN_IF(m_vTouches.contains(pTouch) == false);
    CAScrollView::ccTouchEnded(pTouch, pEvent);
}

void CATableView::ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent)
{
    CC_RETURN_IF(m_vTouches.contains(pTouch) == false);
    CAScrollView::ccTouchCancelled(pTouch, pEvent);
}

void CATableView::switchPCMode(bool var)
{
    CAScrollView::switchPCMode(var);
    this->setMouseMovedEnabled(true);
}

float CATableView::maxSpeed(float dt)
{
    return (128 * 60 * dt);
}

float CATableView::decelerationRatio(float dt)
{
    return 1.8f * dt;
}

CATableViewCell* CATableView::dequeueReusableCellWithIdentifier(const char* reuseIdentifier)
{
    CATableViewCell* cell = NULL;
    
    if (!m_mpFreedTableCells[reuseIdentifier].empty())
    {
        cell = m_mpFreedTableCells[reuseIdentifier].back();
        cell->retain()->autorelease();
        m_mpFreedTableCells[reuseIdentifier].eraseObject(cell);
    }
    return cell;
}

void CATableView::setAllowsSelection(bool var)
{
    m_bAllowsSelection = var;
    CC_RETURN_IF(!m_bAllowsSelection);
    CC_RETURN_IF(m_pSelectedTableCells.empty());
    for (auto& indexPath : m_pSelectedTableCells)
    {
        if (CATableViewCell* cell = m_mpUsedTableCells[indexPath])
        {
            cell->setControlState(CAControlStateNormal);
        }
    }
    m_pSelectedTableCells.clear();
}

void CATableView::setAllowsMultipleSelection(bool var)
{
    m_bAllowsMultipleSelection = var;
    CC_RETURN_IF(m_pSelectedTableCells.empty());
    std::set<CAIndexPath2E>::iterator itr;
    for (auto& indexPath : m_pSelectedTableCells)
    {
        if (CATableViewCell* cell = m_mpUsedTableCells[indexPath])
        {
            cell->setControlState(CAControlStateNormal);
        }
    }
    m_pSelectedTableCells.clear();
}

void CATableView::setSelectRowAtIndexPath(unsigned int section, unsigned int row)
{
    CC_RETURN_IF(section >= m_nSections);
    CC_RETURN_IF(row >= m_nRowsInSections[section]);
    
    if (!m_pSelectedTableCells.empty() && m_bAllowsMultipleSelection == false)
    {
        for (auto& indexPath : m_pSelectedTableCells)
        {
            if (CATableViewCell* cell = m_mpUsedTableCells[indexPath])
            {
                cell->setControlState(CAControlStateNormal);
            }
        }
        m_pSelectedTableCells.clear();
    }
    
    CAIndexPath2E indexPath = CAIndexPath2E(section, row);
    if (CATableViewCell* cell = m_mpUsedTableCells[indexPath])
    {
        cell->setControlState(CAControlStateSelected);
    }
    
    m_pSelectedTableCells.insert(indexPath);
}

void CATableView::setUnSelectRowAtIndexPath(unsigned int section, unsigned int row)
{
    CC_RETURN_IF(section >= m_rSectionRects.size());
    
    CAIndexPath2E indexPath = CAIndexPath2E(section, row);
    CC_RETURN_IF(m_pSelectedTableCells.find(indexPath) == m_pSelectedTableCells.end());
    if (CATableViewCell* cell = m_mpUsedTableCells.at(indexPath))
    {
        cell->setControlState(CAControlStateNormal);
    }
    m_pSelectedTableCells.erase(indexPath);
}

void CATableView::setShowsScrollIndicators(bool var)
{
    this->setShowsVerticalScrollIndicator(var);
    m_bShowsScrollIndicators = var;
}

CATableViewCell* CATableView::cellForRowAtIndexPath(unsigned int section, unsigned int row)
{
    return m_mpUsedTableCells[CAIndexPath2E(section, row)];
}

const CAVector<CATableViewCell*>& CATableView::displayingTableCell()
{
    return m_vpUsedTableCells;
}

void CATableView::clearData()
{
    m_nSections = 0;
    m_nRowsInSections.clear();
    m_nSectionHeaderHeights.clear();
    m_nSectionFooterHeights.clear();
    
    for (auto& vec : m_nRowHeightss)
    {
        vec.clear();
    }
    m_nRowHeightss.clear();
    
    for (auto& vec : m_rTableCellRectss)
    {
        vec.clear();
    }
    m_rTableCellRectss.clear();
    
    m_rSectionRects.clear();
    
    for (auto& vec : m_rLineRectss)
    {
        vec.clear();
    }
    m_rLineRectss.clear();
    m_pUsedLines.clear();
    
    for (auto& pair : m_mpUsedTableCells)
    {
        CATableViewCell* cell = pair.second;
        CC_CONTINUE_IF(cell == NULL);
        m_mpFreedTableCells[cell->getReuseIdentifier()].pushBack(cell);
        pair.second = NULL;
        cell->removeFromSuperview();
        cell->resetCell();
    }
    m_mpUsedTableCells.clear();
    m_vpUsedTableCells.clear();
    m_pSectionHeaderViews.clear();
    m_pSectionFooterViews.clear();
}

void CATableView::reloadViewSizeData()
{
    this->clearData();
    
    m_nSections = m_pTableViewDataSource->numberOfSections(this);
    m_nRowsInSections.resize(m_nSections);
    for (unsigned int i=0; i<m_nSections; i++)
    {
        unsigned int rowsInSection = m_pTableViewDataSource->numberOfRowsInSection(this, i);
        m_nRowsInSections[i] = rowsInSection;
    }
    
    m_nSectionHeaderHeights.resize(m_nSections);
    for (unsigned int i=0; i<m_nSections; i++)
    {
        unsigned int sectionHeaderHeight = m_pTableViewDataSource->tableViewHeightForHeaderInSection(this, i);
        m_nSectionHeaderHeights[i] = sectionHeaderHeight;
    }
    
    m_nSectionFooterHeights.resize(m_nSections);
    for (unsigned int i=0; i<m_nSections; i++)
    {
        unsigned int sectionFooterHeight = m_pTableViewDataSource->tableViewHeightForFooterInSection(this, i);
        m_nSectionFooterHeights[i] = sectionFooterHeight;
    }
    
    m_nRowHeightss.resize(m_nSections);
    for (unsigned int i=0; i<m_nSections; i++)
    {
        std::vector<unsigned int> rowHeights(m_nRowsInSections.at(i));
        for (unsigned int j=0; j<m_nRowsInSections.at(i); j++)
        {
            unsigned int rowHeight = m_pTableViewDataSource->tableViewHeightForRowAtIndexPath(this, i, j);
            rowHeights[j] = rowHeight;
        }
        m_nRowHeightss[i] = rowHeights;
    }
    
    unsigned int viewHeight = 0;
    
    m_nSectionHeights.resize(m_nSections);
    for (unsigned int i=0; i<m_nSections; i++)
    {
        unsigned int sectionHeight = 0;
        sectionHeight += m_nSectionHeaderHeights.at(i);
        sectionHeight += m_nSectionFooterHeights.at(i);
        for (unsigned int j=0; j<m_nRowHeightss.at(i).size(); j++)
        {
            sectionHeight += m_nRowHeightss.at(i).at(j);
            sectionHeight += s_px_to_dip(m_nSeparatorViewHeight);
        }
        m_nSectionHeights[i] = sectionHeight;
        viewHeight += sectionHeight;
    }
    
    viewHeight += m_nTableHeaderHeight;
    viewHeight += m_nTableFooterHeight;
    
    DSize size = this->getBounds().size;
    size.height = viewHeight;
    this->setViewSize(size);
}

void CATableView::reloadData()
{
    CC_RETURN_IF(m_pTableViewDataSource == NULL);
    this->reloadViewSizeData();
    
    this->removeAllSubviews();
    
    float width = this->getBounds().size.width;
    unsigned int y = 0;
    
    if (m_pTableHeaderView)
    {
        m_pTableHeaderView->setFrame(DRect(0, y, width, m_nTableHeaderHeight));
        this->addSubview(m_pTableHeaderView);
        y += m_nTableHeaderHeight;
    }
    
    unsigned int sectionCount = m_pTableViewDataSource->numberOfSections(this);
    
    m_rTableCellRectss.resize(sectionCount);
    m_rLineRectss.resize(sectionCount);
    for (unsigned int i=0; i<sectionCount; i++)
    {
        DRect sectionHeaderRect = DRect(0, y, width, m_nSectionHeaderHeights.at(i));
        CAView* sectionHeaderView = m_pTableViewDataSource->tableViewSectionViewForHeaderInSection(this, sectionHeaderRect.size, i);
        
        if (sectionHeaderView)
        {
            sectionHeaderView->setFrame(sectionHeaderRect);
            this->insertSubview(sectionHeaderView, 2);
            m_pSectionHeaderViews[i] = sectionHeaderView;
        }
        y += m_nSectionHeaderHeights[i];
        
        m_rTableCellRectss[i].resize(m_nRowHeightss[i].size());
        m_rLineRectss[i].resize(m_nRowHeightss[i].size());
        for (unsigned int j=0; j<m_rTableCellRectss[i].size(); j++)
        {
            m_rTableCellRectss[i][j] = DRect(0, y, width, m_nRowHeightss[i][j]);
            y += m_nRowHeightss[i][j];
            
            m_rLineRectss[i][j] = DRect(0, y, width, s_px_to_dip(m_nSeparatorViewHeight));
            y += s_px_to_dip(m_nSeparatorViewHeight);
        }
        
        DRect sectionFooterRect = DRect(0, y, width, m_nSectionFooterHeights.at(i));
        
        CAView* sectionFooterView = m_pTableViewDataSource->tableViewSectionViewForFooterInSection(this, sectionFooterRect.size, i);
        
        if (sectionFooterView)
        {
            sectionFooterView->setFrame(sectionFooterRect);
            this->insertSubview(sectionFooterView, 2);
            m_pSectionFooterViews[i] = sectionFooterView;
        }
        
        DRect sectionRect = sectionHeaderRect;
        sectionRect.size.height = sectionFooterRect.origin.y
        + sectionFooterRect.size.height
        - sectionHeaderRect.origin.y;
        m_rSectionRects.push_back(sectionRect);
        
        y += m_nSectionFooterHeights.at(i);
    }
    
    if (m_pTableFooterView)
    {
        m_pTableFooterView->setFrame(DRect(0, y, width, m_nTableFooterHeight));
        this->addSubview(m_pTableFooterView);
        y += m_nTableFooterHeight;
    }
    
    this->loadTableCell();
    this->updateSectionHeaderAndFooterRects();
    this->layoutPullToRefreshView();
    
    if (this->isScrollWindowNotOutSide())
    {
        this->startDeaccelerateScroll();
    }
}

void CATableView::firstReloadData()
{
    CC_RETURN_IF(!m_mpUsedTableCells.empty());
    this->reloadData();
}

void CATableView::loadTableCell()
{
    DRect rect = this->getBounds();
    rect.origin = getContentOffset();
    rect.origin.y -= rect.size.height * 0.1f;
    rect.size.height *= 1.2f;
    
    for (unsigned int i=0; i<(unsigned int)m_rTableCellRectss.size(); i++)
    {
        for (unsigned int j=0; j<(unsigned int)m_rTableCellRectss.at(i).size(); j++)
        {
            CAIndexPath2E indexPath = CAIndexPath2E(i, j);
            CC_CONTINUE_IF(m_mpUsedTableCells.count(indexPath) && m_mpUsedTableCells[indexPath]);
            DRect cellRect = m_rTableCellRectss[i][j];
            CC_CONTINUE_IF(!rect.intersectsRect(cellRect));
            CATableViewCell* cell = m_pTableViewDataSource->tableCellAtIndex(this, m_rTableCellRectss[i][j].size, i, j);
            CC_CONTINUE_IF(cell == NULL);
            cell->m_pTarget = this;
            cell->m_nSection = i;
            cell->m_nRow = j;
            cell->updateDisplayedAlpha(this->getAlpha());
            cell->setMouseMovedEnabled(m_bPCMode);
            m_pContainer->addSubview(cell);
            cell->setFrame(m_rTableCellRectss[i][j]);
            m_mpUsedTableCells[indexPath] = cell;
            m_vpUsedTableCells.pushBack(cell);
            if (m_pSelectedTableCells.count(indexPath))
            {
                cell->setControlState(CAControlStateSelected);
            }
            if (m_pTableViewDataSource)
            {
                m_pTableViewDataSource->tableViewWillDisplayCellAtIndex(this, cell, i, j);
            }
            
            CAView* view = this->dequeueReusableLine();
            DRect lineRect = m_rLineRectss[i][j];
            if (view == NULL)
            {
                view = CAView::createWithFrame(lineRect, m_obSeparatorColor);
            }
            m_pUsedLines[indexPath] = view;
            this->insertSubview(view, 1);
            view->setFrame(lineRect);
        }
    }
}

void CATableView::recoveryTableCell()
{
    DRect rect = this->getBounds();
    rect.origin = getContentOffset();
    rect.origin.y -= rect.size.height * 0.1f;
    rect.size.height *= 1.2f;
    
    for (auto& pair : m_mpUsedTableCells)
    {
        CATableViewCell* cell = pair.second;
        CC_CONTINUE_IF(cell == NULL);
        DRect cellRect = cell->getFrame();
        
        CC_CONTINUE_IF(rect.intersectsRect(cellRect));
        m_mpFreedTableCells[cell->getReuseIdentifier()].pushBack(cell);
        cell->removeFromSuperview();
        cell->resetCell();
        pair.second = NULL;
        m_vpUsedTableCells.eraseObject(cell);
        
        CAView* line = m_pUsedLines[pair.first];
        CC_CONTINUE_IF(line == NULL);
        m_pFreedLines.pushBack(line);
        line->removeFromSuperview();
        m_pUsedLines[pair.first] = NULL;
    }
}

CAView* CATableView::dequeueReusableLine()
{
    if (m_pFreedLines.empty())
    {
        return NULL;
    }
    CAView* view = m_pFreedLines.front();
    view->retain()->autorelease();
    m_pFreedLines.popFront();
    return view;
}

void CATableView::updateSectionHeaderAndFooterRects()
{
    DRect rect = this->getBounds();
    rect.origin = getContentOffset();
    
    int i = 0;
    for (auto& r : m_rSectionRects)
    {
        if (rect.intersectsRect(r))
        {
            CAView* header = NULL;
            CAView* footer = NULL;
            float headerHeight = m_nSectionHeaderHeights[i];
            float footerHeight = m_nSectionFooterHeights[i];
            if (m_pSectionHeaderViews.find(i) != m_pSectionHeaderViews.end())
            {
                header = m_pSectionHeaderViews[i];
            }
            if (m_pSectionFooterViews.find(i) != m_pSectionFooterViews.end())
            {
                footer = m_pSectionFooterViews[i];
            }
            if (header && m_bAlwaysTopSectionHeader)
            {
                DPoint p1 = rect.origin;
                p1.y = MAX(p1.y, r.origin.y);
                p1.y = MIN(p1.y, r.origin.y + r.size.height
                           - headerHeight - footerHeight);
                header->setFrameOrigin(p1);
            }
            if (footer && m_bAlwaysBottomSectionFooter)
            {
                DPoint p2 = DPointZero;
                p2.y = MIN(rect.origin.y + this->getBounds().size.height - footerHeight,
                           r.origin.y + r.size.height - footerHeight);
                p2.y = MAX(p2.y, r.origin.y + headerHeight);
                footer->setFrameOrigin(p2);
            }
            
        }
        ++i;
    }
}

void CATableView::update(float dt)
{
    CAScrollView::update(dt);
    
    this->recoveryTableCell();
    this->loadTableCell();
    this->updateSectionHeaderAndFooterRects();
}

unsigned int CATableView::getNumberOfSections()
{
    return m_nSections;
}

unsigned int CATableView::getNumberOfRowsInSection(unsigned int section)
{
    if (section >= m_nRowsInSections.size())
    {
        return 0;
    }
    return m_nRowsInSections.at(section);
}

float CATableView::getSectionHeightInSection(unsigned int section)
{
    if (section >= m_nSectionHeights.size())
    {
        return 0.0f;
    }
    return (float)m_nSectionHeights.at(section);
}

float CATableView::getSectionHeaderHeightInSection(unsigned int section)
{
    if (section >= m_nSectionHeaderHeights.size())
    {
        return 0.0f;
    }
    return (float)m_nSectionHeaderHeights.at(section);
}

float CATableView::getSectionFooterHeightInSection(unsigned int section)
{
    if (section >= m_nSectionFooterHeights.size())
    {
        return 0.0f;
    }
    return (float)m_nSectionFooterHeights.at(section);
}

float CATableView::getRowHeightInSectionInRow(unsigned int section, unsigned int row)
{
    if (section >= m_nRowHeightss.size())
    {
        return 0.0f;
    }
    if (row >= m_nRowHeightss[section].size())
    {
        return 0.0f;
    }
    return (float)m_nRowHeightss[section][row];
}

#pragma CATableViewCell

CATableViewCell::CATableViewCell()
:m_nSection(UINT_NONE)
,m_nRow(UINT_NONE)
,m_nDraggingLength(0)
,m_bDragging(false)
{
    this->setHaveNextResponder(false);
    this->setVerticalScrollEnabled(false);
    this->setMultipleTouchEnabled(false);
}

CATableViewCell::~CATableViewCell()
{
    
}

CATableViewCell* CATableViewCell::create(const std::string& reuseIdentifier)
{
    CATableViewCell* cell = new CATableViewCell();
    if (cell && cell->initWithReuseIdentifier(reuseIdentifier))
    {
        cell->autorelease();
        return cell;
    }
    CC_SAFE_DELETE(cell);
    return NULL;
}
void CATableViewCell::normalTableViewCell()
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CACell");
    CC_RETURN_IF(m_pBackgroundView == NULL);
    m_pBackgroundView->setColor(ccc4Int(CrossApp::hex2Int(map.at("backgroundColor_normal"))));
}

void CATableViewCell::highlightedTableViewCell()
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CACell");
    CC_RETURN_IF(m_pBackgroundView == NULL);
    m_pBackgroundView->setColor(ccc4Int(CrossApp::hex2Int(map.at("backgroundColor_highlighted"))));
}


void CATableViewCell::selectedTableViewCell()
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CACell");
    CC_RETURN_IF(m_pBackgroundView == NULL);
    m_pBackgroundView->setColor(ccc4Int(CrossApp::hex2Int(map.at("backgroundColor_selected"))));
}


void CATableViewCell::disabledTableViewCell()
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CACell");
    CC_RETURN_IF(m_pBackgroundView == NULL);
    m_pBackgroundView->setColor(ccc4Int(CrossApp::hex2Int(map.at("backgroundColor_disabled"))));
}

void CATableViewCell::setDraggingLength(unsigned int var)
{
    m_nDraggingLength = var;
    this->setPriorityScroll((bool)(m_nDraggingLength > 0));
}

bool CATableViewCell::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
    bool isInertia = m_pTarget->m_tInertia.getLength() < 1.0f;
    
    if (this->getControlState() != CAControlStateDisabled
        && m_pTarget->isAllowsSelection()
        && m_pTarget->isScrollWindowNotOutSide() == false
        && isInertia)
    {
        if (m_pTarget->isAllowsMultipleSelection())
        {
            this->setControlState(CAControlStateHighlighted);
        }
        else if (m_pTarget->m_pSelectedTableCells.count(CAIndexPath2E(m_nSection, m_nRow)) == 0)
        {
            this->setControlState(CAControlStateHighlighted);
        }
    }
    
    if (m_pTarget->m_pDraggingOutCell)
    {
        m_pTarget->m_pDraggingOutCell->dragInAnimation();
        m_pTarget->m_pDraggingOutCell = NULL;
    }
    return true;
}

void CATableViewCell::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
    if (m_nDraggingLength > 0)
    {
        DPoint p_off = DPointZero;
        
        p_off = ccpSub(this->convertToNodeSpace(pTouch->getLocation()),
                       this->convertToNodeSpace(pTouch->getPreviousLocation()));
        
        DLayout layout = m_pContentView->getLayout();
        layout.horizontal.left = MIN(0, layout.horizontal.left + p_off.x);
        layout.horizontal.right = MAX(0, layout.horizontal.right - p_off.x);
        layout.horizontal.left = MAX(-(int)m_nDraggingLength, layout.horizontal.left);
        layout.horizontal.right = MIN((int)m_nDraggingLength, layout.horizontal.right);
        m_pContentView->setLayout(layout);
        
        this->setDragging((bool) (layout.horizontal.left < 0));
        
        if (m_pTarget->isAllowsSelection() && this->getControlState() == CAControlStateHighlighted)
        {
            if (m_pTarget->isAllowsMultipleSelection())
            {
                if (m_pTarget->m_pSelectedTableCells.count(CAIndexPath2E(m_nSection, m_nRow)) == 0)
                {
                    this->setControlState(CAControlStateNormal);
                }
                else
                {
                    this->setControlState(CAControlStateSelected);
                }
            }
            else
            {
                if (m_pTarget->m_pSelectedTableCells.count(CAIndexPath2E(m_nSection, m_nRow)) == 0)
                {
                    this->setControlState(CAControlStateNormal);
                }
                else
                {
                    this->setControlState(CAControlStateSelected);
                }
            }
        }
    }
}

void CATableViewCell::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
    if (m_pTarget->isAllowsSelection()
        && (this->getControlState() == CAControlStateHighlighted || this->getControlState() == CAControlStateSelected))
    {
        CAIndexPath2E indexPath = CAIndexPath2E(m_nSection, m_nRow);
        
        if (m_pTarget->isAllowsMultipleSelection())
        {
            if (m_pTarget->m_pSelectedTableCells.count(indexPath) == 0)
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateSelected), 0.05f);
                m_pTarget->m_pSelectedTableCells.insert(indexPath);
                if (m_pTarget->getTableViewDelegate())
                {
                    m_pTarget->getTableViewDelegate()->tableViewDidSelectRowAtIndexPath(m_pTarget, indexPath.section, indexPath.row);
                }
            }
            else
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateNormal), 0.05f);
                m_pTarget->m_pSelectedTableCells.erase(indexPath);
                if (m_pTarget->getTableViewDelegate())
                {
                    m_pTarget->getTableViewDelegate()->tableViewDidDeselectRowAtIndexPath(m_pTarget, indexPath.section, indexPath.row);
                }
            }
        }
        else
        {
            if (m_pTarget->m_pSelectedTableCells.count(indexPath) == 0)
            {
                if (!m_pTarget->m_pSelectedTableCells.empty())
                {
                    CAIndexPath2E indexPath2 = *m_pTarget->m_pSelectedTableCells.begin();
                    if (m_pTarget->m_mpUsedTableCells.count(indexPath2) > 0)
                    {
                        if (CATableViewCell* cell = m_pTarget->m_mpUsedTableCells.at(indexPath2))
                        {
                            cell->setControlState(CAControlStateNormal);
                        }
                    }
                    m_pTarget->m_pSelectedTableCells.clear();
                    if (m_pTarget->getTableViewDelegate())
                    {
                        m_pTarget->getTableViewDelegate()->tableViewDidDeselectRowAtIndexPath(m_pTarget, indexPath2.section, indexPath2.row);
                    }
                }
                
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateSelected), 0.05f);
                if (m_bAllowsSelected)
                {
                    m_pTarget->m_pSelectedTableCells.insert(indexPath);
                }
                if (m_pTarget->getTableViewDelegate())
                {
                    m_pTarget->getTableViewDelegate()->tableViewDidSelectRowAtIndexPath(m_pTarget, indexPath.section, indexPath.row);
                }
            }
            else
            {
                if (m_pTarget->getTableViewDelegate())
                {
                    m_pTarget->getTableViewDelegate()->tableViewDidSelectRowAtIndexPath(m_pTarget, indexPath.section, indexPath.row);
                }
            }
        }
    }
    
    if (m_nDraggingLength > 0)
    {
        DLayout layout = m_pContentView->getLayout();
        
        if (((int)layout.horizontal.right) >= ((int)m_nDraggingLength) / 3)
        {
            m_pTarget->m_pDraggingOutCell = this;
            this->dragOutAnimation();
        }
        else
        {
            this->dragInAnimation();
        }
    }
}

void CATableViewCell::ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent)
{
    if (m_pTarget->isAllowsSelection() && this->getControlState() == CAControlStateHighlighted)
    {
        if (m_pTarget->isAllowsMultipleSelection())
        {
            if (m_pTarget->m_pSelectedTableCells.count(CAIndexPath2E(m_nSection, m_nRow)) == 0)
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateNormal), 0.05f);
            }
            else
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateSelected), 0.05f);
            }
        }
        else
        {
            if (m_pTarget->m_pSelectedTableCells.count(CAIndexPath2E(m_nSection, m_nRow)) == 0)
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateNormal), 0.05f);
            }
            else
            {
                this->performSelector(callfunc_selector(CATableViewCell::setControlStateSelected), 0.05f);
            }
        }
    }
}

void CATableViewCell::dragInAnimation()
{
    CAViewAnimation::removeAnimations("dragging" + m_s__StrID);
    CAViewAnimation::beginAnimations("dragging" + m_s__StrID, NULL);
    CAViewAnimation::setAnimationDuration(0.15f);
    CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseOut);
    CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation0_selector(CATableViewCell::dragInAnimationEnd));
    m_pContentView->setLayout(DLayoutFill);
    CAViewAnimation::commitAnimations();
}

void CATableViewCell::dragOutAnimation()
{
    CAViewAnimation::removeAnimations("dragging" + m_s__StrID);
    CAViewAnimation::beginAnimations("dragging" + m_s__StrID, NULL);
    CAViewAnimation::setAnimationDuration(0.15f);
    CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseOut);
    m_pContentView->setLayout(DLayout(DHorizontalLayout_L_R(-(int)m_nDraggingLength, (int)m_nDraggingLength), DVerticalLayoutFill));
    CAViewAnimation::commitAnimations();
}

void CATableViewCell::dragInAnimationEnd()
{
    this->setDragging(false);
}

void CATableViewCell::setDragging(bool var)
{
    if (m_bDragging != var)
    {
        m_bDragging = var;
        if (m_bDragging)
        {
            this->dragOutAtCell();
        }
        else
        {
            this->dragInAtCell();
        }
    }
}

void CATableViewCell::normalCell()
{
    this->normalTableViewCell();
}

void CATableViewCell::highlightedCell()
{
    this->highlightedTableViewCell();
}

void CATableViewCell::selectedCell()
{
    this->selectedTableViewCell();
}

void CATableViewCell::disabledCell()
{
    this->disabledTableViewCell();
}

void CATableViewCell::recoveryCell()
{
    this->recoveryTableViewCell();
}

NS_CC_END
