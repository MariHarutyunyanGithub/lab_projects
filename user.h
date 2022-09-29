#ifndef USER_H
#define USER_H

#include "contact.h"
#include "base.h"

class User : public Base
{
public:
    ~User();
    void add_new_contact() override;
    void find_to_edit_contact(std::string&) override;
    void find_to_remove_contact(std::string&) override;
    void find_to_show_contact() override;
public:
    Contact create_contact();
    void edit_contact(std::string&);
    void edit_name(std::string&);
    void edit_surname(std::string&);
    void edit_phone_number(std::string&);
    void edit_address(std::string&);
    void remove_contact(std::string&);
    void show_by_name() const;
    void show_by_surname() const;
    void show_by_phone_number() const;
    void show_by_address() const;
};

#endif //USER_H