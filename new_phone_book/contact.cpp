#include <iostream>
#include "contact.h"

 std::string Contact::get_name() const
 {
     return m_name;
 }

std::string Contact::get_surname() const
{
    return m_surname;
}

std::string Contact::get_phone_number() const
{
    return m_phone_number;
}

std::string Contact::get_address() const
{
    return m_address;
}

void Contact::set_name(const std::string& name)
{
    m_name = name;    
}

void Contact::set_surname(const std::string& surname)
{
    m_surname = surname;    
}

void Contact::set_phone_number(const std::string& phone_number)
{
    m_phone_number = phone_number; 
}

void Contact::set_address(const std::string& address)
{
    m_address = address; 
}

std::string Contact_to_string(Contact& obj)
{
    std::string str_contact{};
    str_contact += "name : ";
    str_contact += obj.get_name();
    str_contact += "|   surname : ";
    str_contact += obj.get_surname();
    str_contact += "|   phone_number : ";
    str_contact += obj.get_phone_number();
    str_contact += "|   address : ";
    str_contact += obj.get_address();
    str_contact += "|";
    return str_contact;
}

Contact string_to_Contact(std::string str)
{
    Contact new_obj;
    int current_index;
    std::string name{};
    std::string surname{};
    std::string phone_number{};
    std::string address{};
    for (int i{7}; str[i] != '|'; ++i) {
        name += str[i];
        current_index = i + 15;
    }
    new_obj.set_name(name);
    for (int i{current_index}; str[i] != '|'; ++i) {
        surname += str[i];
        current_index = i + 20;
    }
    new_obj.set_surname(surname);
    for (int i{current_index}; str[i] != '|'; ++i) {
        phone_number += str[i];
        current_index = i + 15;
    }
    new_obj.set_phone_number(phone_number);
    for (int i{current_index}; str[i] != '|'; ++i) {
        address += str[i];
    }
    new_obj.set_address(address);
    return new_obj;
}