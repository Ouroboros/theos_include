CF_EXTERN_C_BEGIN

struct segment_command_64 * macho_get_segment_by_name_64(
    struct mach_header_64      * mach_header,
    const char                 * segname);

struct section_64 * macho_get_section_by_name_64(
    struct mach_header_64     * mach_header,
    const char                * segname,
    const char                * sectname);


CF_EXTERN_C_END