

#include "CAData.h"

// implementation of DPoint
NS_CC_BEGIN

CAData::CAData()
:m_pBytes(nullptr)
,m_iLength(0)
{

}

CAData::~CAData()
{
    this->clear();
}

void CAData::copy(const unsigned char* bytes, const ssize_t length)
{
    this->clear();
    
    if (length > 0)
    {
        m_iLength = length;
        m_pBytes = (unsigned char*)malloc(sizeof(unsigned char) * length);
        memcpy(m_pBytes, bytes, length);
    }
}

void CAData::fastSet(unsigned char* bytes, const ssize_t length)
{
    m_pBytes = bytes;
    m_iLength = length;
}

void CAData::copyString(const std::string& var)
{
    this->copy((const unsigned char*)var.c_str(), var.length());
}

void CAData::copyU16string(const std::u16string& var)
{
    this->clear();
    
    if (!var.empty())
    {
        m_iLength = var.length();
        m_pBytes = (unsigned char*)malloc(sizeof(unsigned char) * m_iLength);
        for (ssize_t i=0; i<m_iLength; i++)
        {
            m_pBytes[i] = var[i];
        }
    }
}

bool CAData::isNull() const
{
    return (m_pBytes == nullptr || m_iLength == 0);
}

unsigned char* CAData::getBytes() const
{
    return m_pBytes;
}

ssize_t CAData::getLength() const
{
    return m_iLength;
}

std::string CAData::toString()
{
    std::string ret;
    ret.resize(m_iLength);
    for (ssize_t i=0; i<m_iLength; i++)
    {
        ret[i] = m_pBytes[i];
    }
    return ret;
}

std::u16string CAData::toU16string()
{
    std::u16string ret;
    ret.resize(m_iLength);
    for (ssize_t i=0; i<m_iLength; i++)
    {
        ret[i] = m_pBytes[i];
    }
    return ret;
}

void CAData::clear()
{
    free(m_pBytes);
    m_pBytes = nullptr;
    m_iLength = 0;
}

NS_CC_END
