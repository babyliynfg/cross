#include "CAQrencode.h"
#include "images/qrencode/qrencode.h"
#include "platform/CADensityDpi.h"

NS_CC_BEGIN

CAImage* CAQrencode::createWithQRString(const std::string& string, unsigned int sideLength)
{
    return CAQrencode::createWithQRString(string, sideLength, CAColor4B::WHITE, CAColor4B::BLACK);
}

CAImage* CAQrencode::createWithQRString(const std::string& string, unsigned int sideLength, const CAColor4B& backgroundColor)
{
    return CAQrencode::createWithQRString(string, sideLength, backgroundColor, CAColor4B::BLACK);
}

CAImage* CAQrencode::createWithQRString(const std::string& string, unsigned int sideLength, const CAColor4B& backgroundColor, const CAColor4B& qrColor)
{
    QRcode *code = QRcode_encodeString(string.c_str(), 0, QR_ECLEVEL_L, QR_MODE_8, 1);
    
    float side = CrossApp::s_dip_to_px(1) > 1 ? CrossApp::s_dip_to_px(sideLength) : sideLength;
    int scale = std::ceil(side / code->width);
    int off = 0;
    int width = (code->width + off * 2) * scale;
    
    ssize_t length = width * width * 4;
    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * (length + 1));
    for (ssize_t i = 0; i < length / 4; ++i)
    {
        data[i * 4 + 0] = backgroundColor.r;        //R
        data[i * 4 + 1] = backgroundColor.g;        //G
        data[i * 4 + 2] = backgroundColor.b;        //B
        data[i * 4 + 3] = backgroundColor.a;        //A
    }
    data[length] = '\0';
    
    if (qrColor.a != backgroundColor.a)
    {
        for(int i = 0; i < code->width; ++i)
        {
            for(int j = 0; j < code->width; ++j)
            {
                if ((code->data[j + i * code->width] & 1))
                {
                    for(int h = 0; h < scale; ++h)
                    {
                        for(int w = 0; w < scale; ++w)
                        {
                            unsigned long index = (w + (j + off) * scale) + (h + (i + off) * scale) * width;
                            data[index * 4 + 0] = qrColor.r;        //R
                            data[index * 4 + 1] = qrColor.g;        //G
                            data[index * 4 + 2] = qrColor.b;        //B
                            data[index * 4 + 3] = qrColor.a;        //A
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < code->width; ++i)
        {
            for(int j = 0; j < code->width; ++j)
            {
                if ((code->data[j + i * code->width] & 1))
                {
                    for(int h = 0; h < scale; ++h)
                    {
                        for(int w = 0; w < scale; ++w)
                        {
                            unsigned long index = (w + (j + off) * scale) + (h + (i + off) * scale) * width;
                            data[index * 4 + 0] = qrColor.r;        //R
                            data[index * 4 + 1] = qrColor.g;        //G
                            data[index * 4 + 2] = qrColor.b;        //B
                        }
                    }
                }
            }
        }
    }
    
    QRcode_free(code);

    CrossApp::CAData* ca_data = CrossApp::CAData::create();
    ca_data->fastSet(data, length);

    return CAImage::createWithRawDataNoCache(ca_data, CAImage::PixelFormat::RGBA8888, width, width);
}

NS_CC_END
