CF_EXTERN_C_BEGIN

int __open_nocancel(const char* path, int oflag, int mode);
int __open_dprotected_np(const char* path, int flags, int _class, int dpflags, int mode);
int __open(const char *name, int oflag, int mode);
int __rename(const char *from, const char* to);
int __unlink(const char *path);
int stat64(const char *, struct stat64 *);
int lstat64(const char *, struct stat64 *);
int ptrace(int request, pid_t pid, caddr_t addr, int data);

CF_EXTERN_C_END
