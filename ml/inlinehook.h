#import <substrate.h>
#import <mach/mach.h>
#import <sys/mman.h>
#import "ml/mem.hpp"

typedef struct
{
    int64_t x0;
    int64_t x1;
    int64_t x2;
    int64_t x3;
    int64_t x4;
    int64_t x5;
    int64_t x6;
    int64_t x7;
    int64_t x8;
    int64_t x9;
    int64_t x10;
    int64_t x11;
    int64_t x12;
    int64_t x13;
    int64_t x14;
    int64_t x15;
    int64_t x16;
    int64_t x17;
    int64_t x18;
    int64_t x19;
    int64_t x20;
    int64_t x21;
    int64_t x22;
    int64_t x23;
    int64_t x24;
    int64_t x25;
    int64_t x26;
    int64_t x27;
    int64_t x28;
    int64_t x29;
    int64_t x30;
    int64_t returnAddress;

} ARM64_REGISTERS, *PARM64_REGISTERS;

inline int MSInlineHook(void* target, void* hook, int jmpReg)
{
    if (jmpReg < 0 || jmpReg > 30)
        return -1;

    uint8_t insts[] =
    {
        // ptr += 0x15F90
        0x40, 0x00, 0x00, 0x58,     // ldr x0, #0x8
        0x00, 0x00, 0x1F, 0xD6,     // br  x0
        0x00, 0x00, 0x00, 0x00,     // hook
        0x00, 0x00, 0x00, 0x00,     // hook
    };

    insts[0] += jmpReg;
    *(uint16_t *)&insts[4] += jmpReg * 0x20;

    *(void **)&insts[8] = (void *)hook;

    int ret = WriteProcessMemory(target, insts, sizeof(insts));
    if (ret != 0)
    {
        DbgLog(@"WriteProcessMemory failed: %d", ret);
        return ret;
    }

    return 0;
}