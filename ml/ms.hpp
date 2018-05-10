#import <substrate.h>

inline IMP objc_getClassMethod(Class cls, SEL sel)
{
    return method_getImplementation(class_getClassMethod(cls, sel));
}

inline IMP objc_getInstanceMethod(Class cls, SEL sel)
{
    return method_getImplementation(class_getInstanceMethod(cls, sel));
}

inline void MSInlineHookMessageEx(Class _class, SEL message, IMP hook, IMP *old)
{
    IMP p;

    p = objc_getInstanceMethod(_class, message);
    // if (p == NULL)
    //     p = objc_getClassMethod(_class, message);

    if (p == NULL)
        return;

    MSHookFunction((void *)p, (void *)hook, (void **)old);
}

inline void MSInlineHookInstanceMethod(Class cls, SEL cmd, void* hook, void** stub)
{
    IMP method;

    method = objc_getInstanceMethod(cls, cmd);
    MSHookFunction((void *)method, hook, stub);
}

inline void MSInlineHookClassMethod(Class cls, SEL cmd, void* hook, void** stub)
{
    IMP method;

    method = objc_getClassMethod(cls, cmd);
    MSHookFunction((void *)method, hook, stub);
}