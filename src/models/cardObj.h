#include <WString.h>
#if !defined(CARDOBJ_H)
#define CARDOBJ_H

struct CardObj
{
    String cardId;
    String userId;
    String userName;
    bool isActive;
    String lastScanned;
};


#endif // CARDOBJ_H
