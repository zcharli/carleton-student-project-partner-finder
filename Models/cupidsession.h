#ifndef CUPIDSESSION_H
#define CUPIDSESSION_H

#include "user.h"

class CupidSession
{
public:
    static CupidSession* getInstance();
    static User* currentUser;
    static bool isInstance;
    ~CupidSession();
private:
  CupidSession() {};
  static CupidSession *singleton;
};

#endif // CUPIDSESSION_H
