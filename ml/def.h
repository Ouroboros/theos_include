#define DbgLog(args...) { \
        int __en = errno; \
        NSLog(args); \
        errno = __en; \
    }

#define MSHake2(name) (void *)&$ ## name, (void **) &_ ## name

#define CONST_STRLEN(x) (sizeof(x) - sizeof((x)[0]))

#define IP_ADDRESS(a1, a2, a3, a4) ((a1) | ((a2) << 8) | ((a3) << 16) | ((a4) << 24))

#if !defined(countof)
    #define countof(x) (sizeof((x)) / sizeof(*(x)))
#endif /* countof */
