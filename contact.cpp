#ifndef CONTACT_HPP
#define CONTACT_HPP

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

Contact string_to_Contact(std::string str)
{

    Contact new_obj;
    int current_index{};
    std::string name{};
    int name_index{};
    for (int i{}; i < 15; ++i) {
        if (str[i + 6] != ' ') {
            name_index = i;
            break;
        }
    }
    for (int i{6 + name_index}; str[i] != '|'; ++i) {
        name += str[i];
        //current_index = i + 4;
        current_index = i + 14;
    }
    new_obj.set_name(name);

    std::string surname{};
    int surname_index{};
    for (int i{}; i < 15; ++i) {
        if (str[current_index + i] != ' ') {
            surname_index = i;
            break;
        }
    }
    for (int i{current_index + surname_index}; str[i] != '|'; ++i) {
        surname += str[i];
        current_index = i + 19;
    }
    new_obj.set_surname(surname);

    std::string phone_number{};
    int phone_index{};
    for (int i{}; i < 15; ++i) {
        if (str[current_index + i] != ' ') {
            phone_index = i;
            break;
        }
    }
    for (int i{current_index + phone_index}; str[i] != '|'; ++i) {
        phone_number += str[i];
        current_index = i + 18;
    }
    new_obj.set_phone_number(phone_number);

    std::string address{};
    for (int i{current_index}; i < str.size(); ++i) {
        address += str[i];
    }
    new_obj.set_address(address);
    return new_obj;
}

std::string Contact_to_string(Contact obj)
{
    std::string str_contact{};
    std::string name_section{};
    std::string surname_section{};
    std::string phone_section{};
    for (int i{}; i < 15 - obj.get_name().size(); ++i) {
        name_section += " ";
    }
    for (int i{}; i < 15 - obj.get_surname().size(); ++i) {
        surname_section += " ";
    }
    for (int i{}; i < 15 - obj.get_phone_number().size(); ++i) {
        phone_section += " ";
    }
    str_contact += "name :";
    str_contact += name_section;
    str_contact += obj.get_name();
    str_contact += "|   surname :";
    str_contact += surname_section;
    str_contact += obj.get_surname();
    str_contact += "|   phone_number :";
    str_contact += phone_section;
    str_contact += obj.get_phone_number();
    str_contact += "|   address :    ";
    str_contact += obj.get_address();
    return str_contact;
}

std::string Contact::contact_to_short_string()
{
    std::string str_contact{};
    std::string name_section{};
    std::string surname_section{};
    std::string phone_section{};
    std::string address_section{};
    for (int i{}; i < 15 - get_name().size(); ++i) {
        name_section += " ";
    }
    for (int i{}; i < 15 - get_surname().size(); ++i) {
        surname_section += " ";
    }
    for (int i{}; i < 15 - get_phone_number().size(); ++i) {
        phone_section += " ";
    }  
    for (int i{}; i < 15 - get_address().size(); ++i) {
        address_section += " ";
    }
    str_contact += " "; 
    str_contact += get_name(); 
    for (int i{}; i < name_section.size() - 1; ++i) {
        str_contact += " ";
    }
    str_contact += "| ";
    str_contact += get_surname();
    for (int i{}; i < surname_section.size() - 1; ++i) {
        str_contact += " ";
    }
    str_contact += " | ";
    str_contact += get_phone_number();
    for (int i{}; i < phone_section.size(); ++i) {
        str_contact += " ";
    }
    str_contact += "| ";
    str_contact += get_address();
    for (int i{}; i < address_section.size(); ++i) {
        str_contact += " ";
    }
    str_contact += "  |";
    return str_contact;     
}
#endif //CONTACT_HPP