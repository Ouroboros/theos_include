#import "def.h"
#import <libkern/OSCacheControl.h>
#import <sys/mman.h>
#import <mach/mach.h>

CF_EXTERN_C_BEGIN

kern_return_t
mach_vm_allocate(
    task_t              task,
    mach_vm_offset_t*   addr,
    mach_vm_size_t      size,
    int                 flags
);

kern_return_t
mach_vm_deallocate(
    mach_port_t         task,
    mach_vm_address_t   address,
    mach_vm_size_t      size
);

kern_return_t
mach_vm_read(
    vm_map_t                target_task,
    mach_vm_address_t       address,
    mach_vm_size_t          size,
    vm_offset_t*            data,
    mach_msg_type_number_t* dataCnt
);

kern_return_t
mach_vm_protect(
    vm_map_t            target_task,
    mach_vm_address_t   address,
    mach_vm_size_t      size,
    boolean_t           set_maximum,
    vm_prot_t           new_protection
);

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

kern_return_t
mach_vm_remap(
    vm_map_t                target_task,
    mach_vm_address_t*      target_address,
    mach_vm_size_t          size,
    mach_vm_offset_t        mask,
    int                     flags,
    vm_map_t                src_task,
    mach_vm_address_t       src_address,
    boolean_t               copy,
    vm_prot_t*              cur_protection,
    vm_prot_t*              max_protection,
    vm_inherit_t            inheritance
);

CF_EXTERN_C_END

inline
kern_return_t
vm_region_info(
    mach_port_t                     task,
    void*                           address,

#if defined (__arm64__)
    vm_region_submap_short_info_64* info
#else
    vm_region_submap_short_info*    info
#endif
)
{
    mach_vm_address_t               region;
    vm_size_t                       region_len;
    mach_msg_type_number_t          info_count;
    natural_t                       max_depth;
    kern_return_t                   kr;

    region = (mach_vm_address_t)address;
    region_len = 0;
    max_depth = 99999;

#if defined (__arm64__)
    info_count = VM_REGION_SUBMAP_SHORT_INFO_COUNT_64;
    kr = vm_region_recurse_64(
#else
    info_count = VM_REGION_SUBMAP_SHORT_INFO_COUNT_64;
    kr = vm_region_recurse(
#endif
            task,
            (vm_address_t *)&address,
            &region_len,
            &max_depth,
            (vm_region_recurse_info_t)info,
            &info_count
        );

    return kr;
}

inline
kern_return_t
get_page_info(
    mach_port_t         task,
    mach_vm_address_t   address,
    vm_prot_t*          protection,
    vm_inherit_t*       inheritance
)
{
    kern_return_t                   kr;
    vm_region_submap_short_info_64  info;

    kr = vm_region_info(task, (void *)address, &info);
    if (kr != KERN_SUCCESS)
    {
        return kr;
    }

    *protection  = info.protection & (PROT_READ | PROT_WRITE | PROT_EXEC);
    *inheritance = info.inheritance;

    return kr;
}

inline kern_return_t WriteProcessMemory(void* addr, void* data, int size)
{
    kern_return_t       kr;
    vm_prot_t           prot;
    vm_inherit_t        inherit;
    mach_vm_address_t   page_addr;
    mach_vm_address_t   page_base;
    mach_vm_address_t   page_start;
    mach_vm_address_t   page_end;
    mach_vm_address_t   page_offset;
    mach_vm_address_t   new_page;
    mach_vm_size_t      page_size;
    mach_port_t         task;

    task = mach_task_self();

    page_addr   = (mach_vm_address_t)addr;
    page_size   = getpagesize();
    page_base   = page_addr & ~(page_size - 1);
    page_start  = page_base;
    page_end    = (page_start + size + page_size) & ~(page_size - 1);
    page_size   = page_end - page_start;
    page_offset = page_addr - page_start;

    kr = get_page_info(task, page_start, &prot, &inherit);
    if (kr != KERN_SUCCESS)
    {
        DbgLog(@"get_page_info failed: %d", kr);
        return kr;
    }

    DbgLog(@"prot = %X, inherit = %X", prot, inherit);

    new_page = 0;

    do
    {
        kr = mach_vm_allocate(task, &new_page, page_size, VM_FLAGS_ANYWHERE);
        if (kr != KERN_SUCCESS)
        {
            DbgLog(@"mach_vm_allocate failed: %d, page_size = %llX", kr, page_size);
            break;
        }

        kr = mach_vm_protect(task, new_page, page_size, FALSE, VM_PROT_DEFAULT | VM_PROT_COPY);
        if (kr != KERN_SUCCESS)
        {
            DbgLog(@"mach_vm_protect failed: %d", kr);
            break;
        }

        kr = vm_copy(task, page_start, page_size, new_page);
        if (kr != KERN_SUCCESS)
        {
            DbgLog(@"vm_copy failed: %d", kr);
            break;
        }

        memcpy((void *)(new_page + page_offset), data, size);

        kr = mach_vm_protect(task, new_page, page_size, FALSE, prot);
        if (kr != KERN_SUCCESS)
        {
            DbgLog(@"mach_vm_protect 2 failed: %d", kr);
            break;
        }

        vm_prot_t c, m;

        kr = mach_vm_remap(
                task,
                &page_base,
                page_size,
                0,
                VM_FLAGS_OVERWRITE,
                task,
                new_page,
                TRUE,
                &c,
                &m,
                inherit
            );

        if (kr != KERN_SUCCESS)
        {
            DbgLog(@"mach_vm_remap failed: %d", kr);
            break;
        }

    } while (0);

    if (new_page != 0)
        mach_vm_deallocate(task, new_page, page_size);

    return kr;
}
