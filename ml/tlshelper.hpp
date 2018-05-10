class TlsScopeHelper
{
public:
    TlsScopeHelper(id key)
    {
        this->key = key;
        this->tls = TlsScopeHelper::getTls();
        this->tls[key] = (__bridge id)kCFBooleanTrue;
    }

    ~TlsScopeHelper()
    {
        [this->tls removeObjectForKey:this->key];
    }

    static BOOL isSet(id key)
    {
        return TlsScopeHelper::getTls()[key] != nil;
    }

    static NSMutableDictionary* getTls()
    {
        return [[NSThread currentThread] threadDictionary];
    }

protected:
    NSMutableDictionary* tls;
    id key;
};
