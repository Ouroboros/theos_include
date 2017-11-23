#define DbgLog(args...) { \
        int __en = errno; \
        NSLog(args); \
        errno = __en; \
    }