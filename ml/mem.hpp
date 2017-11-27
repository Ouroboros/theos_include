#import "def.h"
#import <libkern/OSCacheControl.h>
#import <sys/mman.h>
#import <mach/mach.h>

extern "C"
kern_return_t
mach_vm_read(
    vm_map_t                target_task,
    mach_vm_address_t       address,
    mach_vm_size_t          size,
    vm_offset_t*            data,
    mach_msg_type_number_t* dataCnt
);

extern "C"
kern_return_t
mach_vm_protect(
    vm_map_t            target_task,
    mach_vm_address_t   address,
    mach_vm_size_t      size,
    boolean_t           set_maximum,
    vm_prot_t           new_protection
);

extern "C"
kern_return_t
mach_vm_region(
    vm_map_t                target_task,
    mach_vm_address_t*      address,
    mach_vm_size_t*         size,
    vm_region_flavor_t      flavor,
    vm_region_info_t        info,
    mach_msg_type_number_t* infoCnt,
    mach_port_t*            object_name
);

inline int WriteProcessMemory(void* addr, void* data, int size)
{
    int                         protection;
    int                         pagesize;
    kern_return_t               status;
    vm_size_t                   vmsize;
    vm_address_t                address;
    vm_region_basic_info_data_t info;
    mach_msg_type_number_t      infoCount;
    memory_object_name_t        object;
    vm_map_t                    task;

    task = mach_task_self();
    pagesize = getpagesize();
    address = (vm_address_t)addr & ~(pagesize - 1);

#if defined(__arm64__)
    infoCount  = VM_REGION_BASIC_INFO_COUNT_64;
    status = vm_region_64(
#else
    infoCount  = VM_REGION_BASIC_INFO_COUNT;
    status = vm_region(
#endif
                task,
                &address,
                &vmsize,
                VM_REGION_BASIC_INFO,
                (vm_region_info_t)&info,
                &infoCount,
                &object
            );

    if (status != 0)
    {
        DbgLog(@"vm_region failed: %d", status);
        return status;
    }

    protection = info.protection & (PROT_READ | PROT_WRITE | PROT_EXEC);
    address = (vm_address_t)addr & ~(pagesize - 1);

    DbgLog(@"addr = %p, pagesize = %X", (void *)address, pagesize);

    // status = mprotect((void *)address, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC | VM_PROT_COPY);
    status = mach_vm_protect(task, address, pagesize, FALSE, VM_PROT_ALL | VM_PROT_COPY);
    if (status != 0)
    {
        DbgLog(@"mach_vm_protect failed: %d %d", status, errno);
        return status;
    }

    memcpy(addr, data, size);

    sys_dcache_flush(addr, size);
    sys_icache_invalidate(addr, size);

    return mach_vm_protect(task, address, pagesize, FALSE, protection);
    // return mprotect((void *)address, pagesize, protection);
}
