#import <CoreFoundation/CFBase.h>

CF_EXTERN_C_BEGIN

extern CFStringRef IDSKeychainServiceName;

BOOL
IMShouldLog(
    CFStringRef service,
    int         level
);

void
IMLogString(
    int,
    CFStringRef service,
    CFStringRef module,
    int,
    CFStringRef format,
    ...
);

BOOL
IMRemoveKeychainData(
    CFStringRef service,
    CFStringRef account,
    int32_t*    error
);

CF_EXTERN_C_END
