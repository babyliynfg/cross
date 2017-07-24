#ifndef __Test__FirstViewController__
#define __Test__FirstViewController__

#include "RootWindow.h"

class FirstViewController : public CAViewController, CAAutoCollectionViewDataSource, CAAutoCollectionViewDelegate, CAScrollViewDelegate
{
    
public:
    
    FirstViewController();
    
    virtual ~FirstViewController();
    
    CREATE_FUNC(FirstViewController);
    
protected:
    
    void viewDidLoad();
    
    void viewDidUnload();
    
public:
    
    CAAutoCollectionView* p_AutoCollection;
    
    int showImageViewNavigationBar;
    CANavigationBarItem* ImageViewNavigationBar;
    
    int showActivityIndicatorNavigationBar;
    CANavigationBarItem* ActivityIndicatorNavigationBar;
    
    int showSliderNavigationBar;
    CANavigationBarItem* SliderNavigationBar;
    
    int showStepperNavigationBar;
    CANavigationBarItem* StepperNavigationBar;
    
    int showLabelNavigationBar;
    CANavigationBarItem* LabelNavigationBar;
    
    int showTabBarNavigationBar;
    CANavigationBarItem* TabBarNavigationBar;
    
    int showPickerViewNavigationBar;
    CANavigationBarItem* PickerViewNavigationBar;
    
    int showViewAnimationNavigationBar;
    CANavigationBarItem* ViewAnimationNavigationBar;
    
    int showAutoCollectionVerticalNavigationBar;
    CANavigationBarItem* AutoCollectionVerticalNavigationBar;
    
    int showAutoCollectionHorizontalNavigationBar;
    CANavigationBarItem* AutoCollectionHorizontalNavigationBar;
    
public:
    
    void SliderRightBtnRightcallback(CAButton* btn);
    
    void StepperRightBtnRightcallback(CAButton* btn);
    
    void LabelRightBtnRightcallback(CAButton* btn);
    
    void ImageViewRightBtnRightcallback(CAButton* btn);
    
    void ActivityIndicatorRightBtnRightcallback(CAButton* btn);
    
    void TabBarRightBtnRightcallback(CAButton* btn);
    
    void PickerViewRightBtnRightcallback(CAButton* btn);
    
    void ViewAnimationRightBtnRightcallback(CAButton* btn);
    
    void AutoCollectionVerticalRightBtnRightcallback(CAButton* btn);
    
    void AutoCollectionHorizontalRightBtnRightcallback(CAButton* btn);
    
    void refreshData(float interval);
    
    virtual void collectionViewDidSelectCellAtIndexPath(CAAutoCollectionView *collectionView, unsigned int section, unsigned int item);
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CAAutoCollectionView *collectionView, unsigned int section, unsigned int item);
    
    virtual CACollectionViewCell* collectionCellAtIndex(CAAutoCollectionView *collectionView, const DSize& cellSize, unsigned int section, unsigned int item);
    
    virtual DSize collectionViewCellSizeAtIndexPath(CAAutoCollectionView* collectionView, unsigned int section, unsigned int item);
    
    virtual unsigned int numberOfItemsInSection(CAAutoCollectionView *collectionView, unsigned int section);
    
    virtual unsigned int numberOfSections(CAAutoCollectionView *collectionView);
    
private:
    
    std::vector<CAColor4B> colorArr;
    
    std::vector<std::string> m_vTitle;
};
#endif /* defined(__Test__CDUIShowCollectionView__) */
