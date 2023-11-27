#if !defined(FIREBASE_MODEL_H)
#define FIREBASE_MODEL_H

#include "firebaseConfig.h"
#include "../../global.h"
#include <Firebase_ESP_Client.h>
#include "../scanLogObj.h"

class FirebaseModel
{
private:

public:
    FirebaseModel(/* args */);
    ~FirebaseModel();
    void begin();
    void refreshToken();
    void getDoc(String uuid); 
    void addDoc(struct scanLogObj scanLog);
    void updateDoc(struct scanLogObj scanLog);
    void deleteDoc(String uuid);
};


#endif // FIREBASE_MODEL_H



