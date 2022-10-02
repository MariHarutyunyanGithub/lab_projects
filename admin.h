//Implement a program, that allows to register a contact information 
//(name, surname, phone number, address).
//The program should provide an interface (can be used postman) ,
//where the user is able to add a new contact , edit the contact 
//information of the already existing one and remove one of the contacts.


#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <vector>
#include <fstream>
#include "contact.h"

class Admin
{
public:
    Contact create_contact();
    void start();
    void show_all_contacts();
    void show_main_menu(); 
    void exit_from_program();     
    void menu_functions(short);
    void edit_contact(std::string&);
    void edit_name(std::string&);
    void edit_surname(std::string&);
    void edit_phone_number(std::string&);
    void edit_address(std::string&);
    void remove_contact(std::string&);
    void find_to_edit_contact(std::string&);
    void find_to_remove_contact(std::string&);
    void show_by_name() const;
    void show_by_surname() const;
    void show_by_phone_number() const;
    void show_by_address() const;
    void find_to_show_contact();
    void add_new_contact();
    bool check_name(std::string&) const;
    bool check_surname(std::string&) const;
    bool check_phone_number(std::string&) const;
    bool check_address(std::string&) const;
public:
    std::ofstream fout;
    std::ofstream tmpfout;
    std::ifstream fin;
    std::vector<std::string> data;//կոնտակտները պահելու համար
    std::vector<std::string> phone;//հեռախոսահամարները պահելու համար

};

#endif//ADMIN_H