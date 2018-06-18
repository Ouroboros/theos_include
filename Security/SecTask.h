#import <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

/*

SecTaskFinalize                     0000000180E3A2B0
SecTaskCopyDebugDescription         0000000180E3A2DC
SecTaskCreateFromSelf               0000000180E3A3F8    P
SecTaskCreateWithAuditToken         0000000180E3A458    P
SecTaskCopySigningIdentifier        0000000180E3A4B4    P
SecTaskCopyValueForEntitlement      0000000180E3A68C    P
SecTaskLoadEntitlements             0000000180E3A714
SecTaskCopyValuesForEntitlements    0000000180E3A9A4    P

*/

typedef CFTypeRef SecTaskRef;

CF_EXPORT
CFTypeID
SecTaskGetTypeID(
    void
);

CF_EXPORT
SecTaskRef
SecTaskCreateFromSelf(
    CFAllocatorRef allocator
);

CF_EXPORT
SecTaskRef
SecTaskCreateWithAuditToken(
    CFAllocatorRef  allocator,
    audit_token_t   token
);

CF_EXPORT
CFTypeRef
SecTaskCopyValueForEntitlement(
    SecTaskRef  task,
    CFStringRef entitlement,
    CFErrorRef* error
);

CF_EXPORT
CFDictionaryRef
SecTaskCopyValuesForEntitlements(
    SecTaskRef  task,
    CFArrayRef  entitlements,
    CFErrorRef* error
);

CF_EXPORT
CFStringRef
SecTaskCopySigningIdentifier(
    SecTaskRef  task,
    CFErrorRef* error
);

CF_EXTERN_C_END