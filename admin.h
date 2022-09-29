//Implement a program, that allows to register a contact information 
//(name, surname, phone number, address).
//The program should provide an interface (can be used postman) ,
//where the user is able to add a new contact , edit the contact 
//information of the already existing one and remove one of the contacts.

#ifndef ADMIN_H
#define ADMIN_H

#include "base.h"

class Admin : public Base
{
public:
    void start();
    ~Admin() { }
};

#endif //ADMIN_H