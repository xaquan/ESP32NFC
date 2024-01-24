#include <WString.h>
#if !defined(CARDOBJ_H)
#define CARDOBJ_H

class CardObj
{
    public:
    String cardId;
    String userId;
    String userName;
    bool isActive = false;
    String lastScanned;
};


#endif // CARDOBJ_H
