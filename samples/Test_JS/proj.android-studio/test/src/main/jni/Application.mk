APP_STL := gnustl_static
#NDK_TOOLCHAIN_VERSION := 4.8
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -std=c++11 -fsigned-char
APP_LDFLAGS := -latomic
APP_ABI := armeabi-v7a
#armeabi-v7a
APP_SHORT_COMMANDS := true
USE_ARM_MODE := 1
APP_ALLOW_MISSING_DEPS=true
ifeq ($(NDK_DEBUG),1)
  APP_CPPFLAGS += -DCOCOS2D_DEBUG=1
  APP_OPTIM := debug
else
  APP_CPPFLAGS += -DNDEBUG
  APP_OPTIM := release
endif