template<typename RET_TYPE = id, typename ...ARGS>
inline __attribute__((always_inline)) RET_TYPE objc_msgSendT(id obj, SEL cmd, ARGS... args)
{
    return ((RET_TYPE(*)(id, SEL, ARGS...))objc_msgSend)(obj, cmd, args...);
}

template<typename RET_TYPE = id, typename ...ARGS>
inline __attribute__((always_inline)) RET_TYPE objc_msgSendT(const char* className, SEL cmd, ARGS... args)
{
    return ((RET_TYPE(*)(id, SEL, ARGS...))objc_msgSend)(objc_getClass(className), cmd, args...);
}
