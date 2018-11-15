#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" android::status_t  _ZN7android19GraphicBufferMapper4lockEPK13native_handleiRKNS_4RectEPPv(android::GraphicBufferMapper *_this ,buffer_handle_t handle, int usage, const android::Rect& bounds, void** vaddr)
{
    return _this->lock(handle, usage, bounds, vaddr);
}

extern "C" pid_t androidGetTid()
{
#ifdef HAVE_GETTID
    return gettid();
#else
    return getpid();
#endif
}
