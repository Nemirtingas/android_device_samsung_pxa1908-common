#include "cameraengine.h"

#include <dlfcn.h>

#define LOAD_FUNC(lib, func)   (*(int*)&func) = (int)dlsym(_lib, #func)

libcameraengine::libcameraengine()
{
    _lib = dlopen("libcameraengine.so", RTLD_NOW);
    LOAD_FUNC(_lib, CAM_GetHandle);
    LOAD_FUNC(_lib, CAM_FreeHandle);
    LOAD_FUNC(_lib, CAM_EnumSensors);
}

libcameraengine& libcameraengine::Inst()
{
    static libcameraengine x;
    return x;
}
