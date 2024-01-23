#if !defined(FIREBASE_MODEL_H)
#define FIREBASE_MODEL_H

#include "firebaseConfig.h"
#include "../../global.h"
#include <Firebase_ESP_Client.h>
#include "../scanLogObj.h"
#include "../cardObj.h"

class FirebaseModel
{
private:

public:
    FirebaseModel(/* args */);
    ~FirebaseModel();
    void begin();
    void refreshToken();
    CardObj getUserByCardId(String uuid); 
    void addActivity(struct ScanLogObj scanLog);
    void updateDoc(struct ScanLogObj scanLog);
    void deleteDoc(String uuid);
};


#endif // FIREBASE_MODEL_H



