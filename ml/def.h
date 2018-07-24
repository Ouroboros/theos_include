#if DEBUG
    #define EnableLog(_name) \
        freopen(_name, "w+", stderr); \
        dup2(fileno(stderr), fileno(stdout)); \
        setbuf(stdout, NULL); \
        setbuf(stderr, NULL);

    #define DbgLog(args...) { \
            int __en = errno; \
            NSLog(args); \
            errno = __en; \
        }

#else

    #define EnableLog(_name)
    #define DbgLog(args...)

#endif // DEBUG

#define MSHake2(name) (void *)&$ ## name, (void **) &_ ## name

#define CONST_STRLEN(x) (sizeof(x) - sizeof((x)[0]))

#define IP_ADDRESS(a1, a2, a3, a4) ((a1) | ((a2) << 8) | ((a3) << 16) | ((a4) << 24))

#if !defined(countof)
    #define countof(x) (sizeof((x)) / sizeof(*(x)))
#endif /* countof */

#define kNSBooleanTrue (__bridge id)kCFBooleanTrue
#define kNSBooleanFalse (__bridge id)kCFBooleanFalse

#define GetReturnAddress() ((uintptr_t)__builtin_return_address(0))
