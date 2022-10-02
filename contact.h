#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact
{
public:
    std::string get_name() const;
    std::string get_surname() const;
    std::string get_phone_number() const;
    std::string get_address() const;
    std::string contact_to_short_string();
public:
    void set_name(const std::string&);
    void set_surname(const std::string&);
    void set_phone_number(const std::string&);
    void set_address(const std::string&);
private:
    std::string m_name;
    std::string m_surname;
    std::string m_phone_number;
    std::string m_address;
};

Contact string_to_Contact(std::string);
std::string Contact_to_string(Contact);

#endif //CONTACT_H