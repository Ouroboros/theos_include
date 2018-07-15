CF_EXTERN_C_BEGIN

typedef void (*_dyld_objc_notify_mapped)(unsigned count, const char* const paths[], const struct mach_header* const mh[]);
typedef void (*_dyld_objc_notify_init)(const char* path, const struct mach_header* mh);
typedef void (*_dyld_objc_notify_unmapped)(const char* path, const struct mach_header* mh);

void
_dyld_objc_notify_register(
    _dyld_objc_notify_mapped    mapped,
    _dyld_objc_notify_init      init,
    _dyld_objc_notify_unmapped  unmapped
);

intptr_t _dyld_get_image_slide(const struct mach_header* mh);

int __open_nocancel(const char* path, int oflag, int mode);
int __open_dprotected_np(const char* path, int flags, int _class, int dpflags, int mode);
int __open(const char *name, int oflag, int mode);
int __rename(const char *from, const char* to);
int __unlink(const char *path);
int stat64(const char *, struct stat64 *);
int lstat64(const char *, struct stat64 *);
int ptrace(int request, pid_t pid, caddr_t addr, int data);
int mremap_encrypted(void* addr, size_t len, uint32_t cryptid, uint32_t cputype, uint32_t cpusubtype);

CF_EXTERN_C_END
