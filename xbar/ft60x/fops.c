#include "fops.h"

int ft60x_open(ftdev_t *fd, const char *path)
{
#ifdef __linux__
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    *fd = open(path, O_RDWR, mode);
    return *fd;
#else
    FT_STATUS ftStatus = FT_OK;

    // XXX pass index as argument ?
    ftStatus = FT_Create(0, FT_OPEN_BY_INDEX, fd);
    if (FT_FAILED(ftStatus))
    {
        return -1;
    }
    return 0;
#endif
}

int ft60x_close(ftdev_t fd)
{
#ifdef __linux__
    return close(fd);
#else
    FT_STATUS ftStatus = FT_OK;

    ftStatus = FT_Close(fd);
    if (FT_FAILED(ftStatus))
    {
        return -1;
    }
    return 0;
#endif
}

ssize_t ft60x_read(ftdev_t fd, void *buf, size_t len)
{
#ifdef __linux__
    return read(fd, buf, len);
#else
    FT_STATUS ftStatus = FT_OK;
    unsigned long ulBytesRead = 0;
    unsigned char pipeID = 0x82;

    ftStatus = FT_ReadPipe(fd, pipeID, buf, len, &ulBytesRead, NULL);
    if (FT_FAILED(ftStatus))
    {
        FT_AbortPipe(fd, pipeID);
        return -1;
    }
    return ulBytesRead;
#endif
}

ssize_t ft60x_write(ftdev_t fd, const void *buf, size_t len)
{
#ifdef __linux__
    return write(fd, buf, len);
#else
    FT_STATUS ftStatus = FT_OK;
    unsigned long ulBytesWritten = 0;
    unsigned char pipeID = 0x02;

    ftStatus = FT_WritePipe(fd, pipeID, buf, len, &ulBytesWritten, NULL);
    if (FT_FAILED(ftStatus))
    {
        FT_AbortPipe(fd, pipeID);
        return -1;
    }
    return ulBytesWritten;
#endif
}
