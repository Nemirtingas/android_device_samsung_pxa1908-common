#ifndef __MVMEM_H__
#define __MVMEM_H__

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int mvmem_alloc(size_t len, unsigned int _flags, size_t align);
int mvmem_free(int handle_fd);
int mvmem_set_name(int handle_fd, const char *name);
int mvmem_get_phys(int handle_fd, int *phys);
int mvmem_get_dma_addr(int handle_fd, int *dma);
int mvmem_sync(int handle_fd, int fd);
int mvmem_sync_range(int handle_fd, int offset, int size, int note);
void* mvmem_mmap(int fd, size_t length, off_t offset);
int mvmem_munmap(void *addr, size_t length);
int mvmem_notify(int handle_fd, int note);
int mvmem_set_usage(int fd, int note);
int mvmem_get_usage(int fd, int *note);

#ifdef __cplusplus
}
#endif

#endif
