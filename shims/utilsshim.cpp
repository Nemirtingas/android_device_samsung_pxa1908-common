#include <utils/String16.h>

extern "C" android::String16* _ZN7android8String16C1EPKt(const char16_t *o)
{
    return new android::String16(o);
}

extern "C" android::String16* _ZN7android8String16C1EPKtj(const char16_t *o, size_t len)
{
    return new android::String16(o,len);
}
