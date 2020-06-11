#import <substrate.h>
#import <mach-o/dyld.h>

inline IMP objc_getClassMethod(Class cls, SEL sel)
{
    return method_getImplementation(class_getClassMethod(cls, sel));
}

inline IMP objc_getInstanceMethod(Class cls, SEL sel)
{
    return method_getImplementation(class_getInstanceMethod(cls, sel));
}

inline void* MSGetJumpTargetArm64(const void* address)
{
    uint32_t inst = *(uint32_t *)address;

    if ((inst >> 24) != 0x14)
        return (void *)address;

    return (void *)((uintptr_t)address + ((inst & 0x00FFFFFF) << 2));
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

inline MSImageRef MSGetImageByAddress(const void* address)
{
    Dl_info info;

    if (dladdr(address, &info) != 0)
    {
        return info.dli_fbase;
    }

    return nullptr;
}

inline MSImageRef MSGetImageByName2(const char* name, int* index = nullptr)
{
    int count, len;

    count = _dyld_image_count();
    if (count == 0)
        return nullptr;

    len = strlen(name);

    for (int i = 0; i != count; i++)
    {
        const char* n = _dyld_get_image_name(i);

        int l = strlen(n);

        if (l < len)
            continue;

        n = &n[l - len];
        if (strcmp(n, name) == 0)
        {
            if (index != nullptr)
                *index = i;

            // return MSGetImageByName(n);
            return _dyld_get_image_header(i);
        }
    }

    return nullptr;
}

#import "find-syms.mm"

inline void* MSFindSymbol2(MSImageRef image, const char* symbol)
{
    if (image == nullptr)
    {
        return MSFindSymbol(image, symbol);
    }

    const char* names[] = { symbol };
    void *syms[countof(names)];
    intptr_t dyld_slide = -1;

    substitute::find_syms_raw(image, &dyld_slide, names, syms, countof(names));

    return syms[0];
}
