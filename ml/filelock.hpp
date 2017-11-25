#import "def.h"

class FileLock
{
public:
    FileLock()
    {
        this->fd = -1;
    }

    ~FileLock()
    {
        if (this->fd == -1)
            return;

        close(this->fd);
    }

public:
    int open(const char* path)
    {
        this->fd = ::open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
        if (this->fd == -1)
            return -1;

        int flags;

        flags = fcntl(this->fd, F_GETFD);
        if (flags == -1)
            return -2;

        flags = fcntl(this->fd, F_SETFD, flags | FD_CLOEXEC);
        if (flags == -1)
            return -3;

        return 0;
    }

    BOOL isLocked()
    {
        int ret;
        struct flock fl;

        fl = this->getFileLock(F_WRLCK);

        ret = fcntl(this->fd, F_GETLK, &fl);
        if (ret != 0)
            return NO;

        if (fl.l_type != F_WRLCK)
            return NO;

        if (fl.l_pid == 0)
            return NO;

        return fl.l_pid != getpid();
    }

    int lock(BOOL wait)
    {
        int ret;
        struct flock fl;

        fl = this->getFileLock(F_WRLCK);
        ret = fcntl(fd, wait ? F_SETLKW : F_SETLK, &fl);
        if (ret != 0)
            return ret;

        return ret;
    }

    int unlock()
    {
        int ret;
        struct flock fl;

        fl = this->getFileLock(F_UNLCK);
        return fcntl(fd, F_SETLK, &fl);
    }

protected:
    struct flock getFileLock(int type)
    {
        struct flock fl;

        fl.l_type = type;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_pid = 0;

        return fl;
    }

protected:
    int fd;
};
