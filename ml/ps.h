#import <spawn.h>

#define PT_TRACE_ME 0 /* child declares it's being traced */
#define PT_READ_I 1 /* read word in child's I space */
#define PT_READ_D 2 /* read word in child's D space */
#define PT_READ_U 3 /* read word in child's user structure */
#define PT_WRITE_I 4 /* write word in child's I space */
#define PT_WRITE_D 5 /* write word in child's D space */
#define PT_WRITE_U 6 /* write word in child's user structure */
#define PT_CONTINUE 7 /* continue the child */
#define PT_KILL 8 /* kill the child process */
#define PT_STEP 9 /* single step the child */
#define PT_ATTACH 10 /* trace some running process */
#define PT_DETACH 11 /* stop tracing a process */
#define PT_SIGEXC 12 /* signals as exceptions for current_proc */
#define PT_THUPDATE 13 /* signal for thread# */
#define PT_ATTACHEXC 14 /* attach to running process with signal exception */
#define PT_FORCEQUOTA 30 /* Enforce quota for root */
#define PT_DENY_ATTACH 31
#define PT_FIRSTMACH 32 /* for machine-specific requests */

#if !defined(MAXPATHLEN)
    #define MAXPATHLEN PATH_MAX
#endif

CF_EXTERN_C_BEGIN

const char*** _NSGetEnviron();

#define PROC_PIDREGIONPATHINFO      8
#define PROC_PIDREGIONPATHINFO_SIZE (sizeof(struct proc_regionwithpathinfo))

#define PROC_PIDPATHINFO 11
#define PROC_PIDPATHINFO_SIZE  (MAXPATHLEN)
#define PROC_PIDPATHINFO_MAXSIZE  (4 * MAXPATHLEN)

int proc_pidpath(int pid, void* buffer, uint32_t buffersize);
int proc_regionfilename(int pid, uint64_t address, void* buffer, uint32_t bufferSize);
int proc_pidinfo(int pid, int flavor, uint64_t arg,  void *buffer, int buffersize);

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
