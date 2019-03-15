#ifndef __FT60x_FOPS_H
#define __FT60x_FOPS_H

#ifdef __linux__
    #include <unistd.h>
    #include <sys/stat.h>
    #include <fcntl.h>
#else
    #include "FTD3XXLibrary/FTD3XX.h"
#endif

#ifdef __linux__
typedef int ftdev_t;
#else
typedef FT_HANDLE ftdev_t;
#endif

int ft60x_open(ftdev_t *fd, const char *path);
int ft60x_close(ftdev_t fd);
ssize_t ft60x_read(ftdev_t fd, void *buf, size_t len);
ssize_t ft60x_write(ftdev_t fd, const void *buf, size_t len);

#endif // __FT60x_FOPS_H
