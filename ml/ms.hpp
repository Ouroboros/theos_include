#import <substrate.h>

inline void MSInlineHookInstanceMethod(Class cls, SEL cmd, void* hook, void** stub)
{
    IMP method;

    method = method_getImplementation(class_getInstanceMethod(cls, cmd));
    MSHookFunction((void *)method, hook, stub);
}

inline void MSInlineHookClassMethod(Class cls, SEL cmd, void* hook, void** stub)
{
    IMP method;

    method = method_getImplementation(class_getClassMethod(cls, cmd));
    MSHookFunction((void *)method, hook, stub);
}