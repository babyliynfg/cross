

#include "platform/CADensityDpi.h"
#include "CCEGLView.h"
NS_CC_BEGIN

float CADensityDpi::getDensityDpi()
{
    return DPI_SIMULATOR;
}

CADeviceIdiom CADensityDpi::getIdiom()
{
    return CADeviceIdiomPhone;
}

NS_CC_END