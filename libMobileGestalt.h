CF_EXTERN_C_BEGIN

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

CFTypeRef MGCopyAnswerInternal(CFStringRef question, int32_t* answerType);

CF_EXTERN_C_END
