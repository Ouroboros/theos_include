#import <spawn.h>

CF_EXTERN_C_BEGIN

const char*** _NSGetEnviron();

#define PROC_PIDPATHINFO 11
#define PROC_PIDPATHINFO_SIZE  (MAXPATHLEN)
#define PROC_PIDPATHINFO_MAXSIZE  (4 * MAXPATHLEN)

int proc_pidpath(int pid, void* buffer, uint32_t buffersize);

CF_EXTERN_C_END

inline int system2(const char* cmd)
{
    int ret;
    int status;
    pid_t pid;
    posix_spawnattr_t attr;

    const char* argv[] =
    {
        "/bin/sh",
        "-c",
        cmd,
        nullptr,
    };

    posix_spawnattr_init(&attr);
    posix_spawnattr_setflags(&attr, POSIX_SPAWN_CLOEXEC_DEFAULT);

    ret = posix_spawnp(&pid, argv[0], nullptr, &attr, (char* const*)argv, (char* const*)*_NSGetEnviron());
    posix_spawnattr_destroy(&attr);

    if (ret != 0)
        return ret;

    ret = waitpid(pid, &status, 0);

    if (ret != 0)
        return ret;

    return status;
}
