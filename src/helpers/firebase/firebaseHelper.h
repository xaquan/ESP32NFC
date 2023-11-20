#if !defined(FIREBASE_HELPER_H)
#define FIREBASE_HELPER_H

#include <Firebase_ESP_Client.h>
#include <Arduino.h>


class FirebaseHelper
{
private:
    /* data */
public:
    void begin();
    ~FirebaseHelper();
};

void FirebaseHelper::begin(){
}

FirebaseHelper::FirebaseHelper(/* args */)
{
}

FirebaseHelper::~FirebaseHelper()
{
}


#endif // FIREBASE_HELPER_H
