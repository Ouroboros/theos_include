CF_EXTERN_C_BEGIN

BOOL MGIsQuestionValid(CFStringRef question);

CFTypeRef MGCopyAnswer(CFStringRef question);

class MGAnswerTypes
{
    enum
    {
        Dictionary      = 2,
        Array           = 3,
        Number          = 4,
        NumberSInt32    = 5,
        NumberSInt64    = 6,
        NumberFloat32   = 7,
        NumberFloat64   = 8,
        String          = 9,
        Data            = 10,
        Boolean         = 11,
    };
};

/*++

    encodedQuestion = encoding.base64Encode(encoding.md5('MGCopyAnswer' + question))

++*/

CFTypeRef MGCopyAnswerInternal(CFStringRef question, int32_t* answerType);

CFBooleanRef MGGetBoolAnswer(CFStringRef question);
CFNumberRef MGGetFloat32Answer(CFStringRef question);
CFNumberRef MGGetSInt32Answer(CFStringRef question);
CFNumberRef MGGetSInt64Answer(CFStringRef question);

int MGSetAnswer(CFStringRef question, CFTypeRef answer);

void MGSetLogHandler(void (*handler)(const char* log));

BOOL _MGCacheValid();
void _MGWriteCache();
void _MGClearInProcessCache();

// MGRegisterForBulkUpdates

@interface MGNotificationRegistration : NSObject {
}

- (void) cancel;
- (void) dealloc;
- (BOOL) start;
// - (id) initWithQueue:(id)arg1 block:(^block)arg2;
// - (BOOL) registerForNotification:(int)arg1 argument:(const char*)arg2 question:(id)arg3;

@end

MGNotificationRegistration* MGRegisterForUpdates(CFArrayRef questions, intptr_t zero1, intptr_t zero2, void (^callback)(CFStringRef question));

extern CFStringRef kMGQDiskUsageAmountDataAvailable;
extern CFStringRef kMGQDiskUsageAmountDataReserved;
extern CFStringRef kMGQDiskUsageTotalDataAvailable;
extern CFStringRef kMGQDiskUsageTotalDataCapacity;
extern CFStringRef kMGQDiskUsageTotalDiskCapacity;
extern CFStringRef kMGQDiskUsageTotalSystemAvailable;
extern CFStringRef kMGQDiskUsageTotalSystemCapacity;

CF_EXTERN_C_END
