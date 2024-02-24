#include <global.h>

MetGlobal::MetGlobal(/* args */)
{
}

MetGlobal::~MetGlobal()
{
}


void MetGlobal::LogInSuccess(){
    loggedIn = true;
}

void MetGlobal::LogOut(){
    loggedIn = false;
}

bool MetGlobal::isLogged(){
    return loggedIn;
}

// NTPClient MetGlobal::getnNTPClient(){
//     return _timeClient;
// }

// void MetGlobal::setNTPClient(NTPClient timeClient){
//     _timeClient = timeClient;
// }
