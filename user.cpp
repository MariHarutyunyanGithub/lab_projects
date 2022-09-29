#ifndef USER_HPP
#define USER_HPP

#include <iostream>

#include "user.h"

//ֆունկցիան վերցնում է user֊ի կողմից նոր ստեղծված
//Contact տիպի օբյեկտը, վերածում է string֊ի,ավելացնում է data վեկտորի մեջ,
//բացում է tmp.txt ֆայլը, վեկտորի թարմացված տվյալները գրում է այդ ֆայլի մեջ,
//հին ֆայլը ջնջում է, նորի անունը փոխարինում է հնով

User::~User() { }
void User::add_new_contact()
{
    Contact new_contact = create_contact();
    std::string string_contact = Contact_to_string(new_contact);
    data.push_back(string_contact);

    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error" <<std::endl;
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
        tmpfout.close();
        std::cout << "\nthe contact  \""<< string_contact 
        << "\" has  created and saved successfuly!\n\n";	
    }
    show_main_menu();
}

//ֆունկցիան հնարավորություն է տալիս user֊ին համապատասխան պարամետրեր տալով
// գտնել կոնտակտը
void User::find_to_edit_contact(std::string& name)
{
    std::vector<std::string> same_name_vec{};//նույն անունով կոնտակտների համար
    std::vector<std::string> same_surname_vec{};//նույն անուն֊ազգանունով կոնտակտների համար
    int contact_count{};
    std::string contact_name{};
    int current_index{};
    for (int i{}; i < data.size(); ++i) { //անցնում ենք data֊ի բոլոր էլեմենտների վրայով
        for (int j{8}; data[i][j] != '|'; ++j) {//գտնում ենք անունները
            contact_name += data[i][j];
            current_index = j;
        }
        if (contact_name == name) {//համեմատում ենք մուտքագրված անվան հետ
            contact_count++;//համընկումների քանակը
            same_name_vec.push_back(data[i]);
            std::cout << data[i] << std::endl;
        }
    }
    if (!contact_count) {
        std::cout << "No contact found with that name!!" << std::endl;
        show_main_menu();
    }
    else if (contact_count == 1) { //եթե ունենք ուղիղ մեկ համընկում
        edit_contact(same_name_vec[0]);
    }
    else {//if (contact_count > 1)
        std::cout << "It is not clear which contact you want to change.\nPLease, input the surname  :  ";
        std::string surname;
        do {
            std::getline(std::cin, surname);
            std::string contact_surname{};
            contact_count = 0;
            for (int i{}; i < same_name_vec.size(); ++i) {
                for (int j{current_index + 12}; j != '|'; ++j) {
                    contact_surname += same_name_vec[i][j];//գտնում ենք ազգանունը
                    current_index = j;
                }
                if (contact_surname == surname) {
                    contact_count++;//համընկումների քանակը
                    same_surname_vec.push_back(same_name_vec[i]);
                    std::cout << same_name_vec[i] << std::endl;
                }
            }
            if (!contact_count) {
                std::cout << "No contact found with that surname!!" << std::endl;
                for (int i{}; i < same_name_vec.size(); ++i) {
                    std::cout << same_name_vec[i] << std::endl;
                }
                std::cout << "choose and input surname again to edit the correct conact." << std::endl;
            }
        } while (!contact_count);
        if (contact_count == 1) {
            edit_contact(same_surname_vec[0]);
        }
        else { //  if (contact_count > 1)
            int contact_index; //same_surname_vec վեկտորի մեջ փնտրվող կոնտակտի ինդեքսը 
            std::cout << "again it is not clear which contact you want to change.\nPLease, input the phone_number  :  ";
            std::string phone_number{};
            do {
                std::cin >> phone_number;
                std::string contact_phone_number{};
                contact_count = 0;
                for (int i{}; i < same_surname_vec.size(); ++i) {
                    for (int j{current_index + 17}; j != '|'; ++j) {
                        contact_phone_number += same_surname_vec[i][j];
                        current_index = j;
                    }
                    if (contact_phone_number == phone_number) {
                        contact_count++;
                        std::cout << same_surname_vec[i] << std::endl;
                        contact_index = i; //կոնտակտը գտանք
                    }
                }
                if (!contact_count) {
                    std::cout << "No contact found with that phone_number!!" << std::endl;
                    for (int i{}; i < same_surname_vec.size(); ++i) {
                        std::cout << same_surname_vec[i] << std::endl;
                    }
                    std::cout << "choose and input phone_number again to edit the correct conact." << std::endl;
                }
            }while (!contact_count);
            if (contact_count == 1) {
                edit_contact(same_surname_vec[contact_index]);
            }
            //մեկից ավել համընկումը հեռախոսահամարի դեպքում բացառվում է
        }
    }
}

//ֆունկցիան ստեղծում է Contact տիպի օբյեկտ և user֊ի կողմից տրված համապատասխան
//պարամետրերը ստուգելուց հետո set է անում
Contact User::create_contact()
{
    Contact contact;    
    //մուտքագրված անունը և ազգանունը պիտի բաղկացած լինեն բացառապես տառերից
    //(թույլատրվում է նաև բացատ)
    bool is_valid_name;
    std::string name;
    do {
        is_valid_name = true;
        std::cout << "Enter the name of contact  :  ";
        std::getline(std::cin, name);
        for (int i{}; i < name.length(); ++i) {
            if (!(name[i] >= 'a' && name[i] <= 'z') 
            && !(name[i] >= 'A' && name[i] <= 'Z') 
            && name[i] != ' ')
            {
                is_valid_name = false;
                std::cout << "Your input is not valid. Please, input the correct name or input '0' to go to main menu." << std::endl;
                break;
            }
        }
        if (name == "0") {
            show_main_menu();
        }
    } while (!is_valid_name);
    contact.set_name(name);
    
    bool is_valid_surname;
    std::string surname;
    do {
        is_valid_surname =true;
        std::cout << "Enter the surname of contact  :  ";
        std::getline(std::cin, surname);
        for (int i{}; i < surname.length(); ++i) {
            if (!(surname[i] >= 'a' && surname[i] <= 'z') && !(surname[i] >= 'A' && surname[i] <= 'Z') && surname[i] != ' ')
            {
                is_valid_surname = false;
                std::cout << "Your input is not valid. Please, input the correct surname or input '0' to go to main menu." << std::endl;
                break;
            }
        }
        if (surname == "0") {
            show_main_menu();
        }
    } while (!is_valid_surname);
    contact.set_surname(surname);    
    //մուտքագրված համարը պիտի բաղկացած լինի միայն թվանշաններից և չպիտի կրկնվի
    bool is_valid_phone_number;
    std::string phone_number;
    do {
        is_valid_phone_number = true;
        std::cout << "Enter the phone_number of contact  :  ";
        std::cin >> phone_number;
        for (int i{}; i < phone_number.length(); ++i) {
            if (!(phone_number[i] >= '0' && phone_number[i] <= '9'))
            {
                is_valid_phone_number = false;
                std::cout << "Your input is not valid. Please, input the correct phone number or input '0' to go to main menu." << std::endl;
                break;
            }
        }
        if (phone_number == "0") {
            show_main_menu();
        }
    } while (!is_valid_phone_number);
    bool is_unique{true};
    for (int i{}; i < phone.size(); ++i) {
        if (phone[i] == phone_number) {
            is_unique = false;
            std::cout << "that phone_numer already exists. Please, input another number" << std::endl;
        }
    }
    if (is_unique) {
        phone.push_back(phone_number);
        contact.set_phone_number(phone_number); 
    }   
    //հասցեն պիտի պարունակի տառեր, թվեր, ու մի քանի հատուկ սիմվոլներ
    bool is_valid_address;
    std::string address;
    do {
        is_valid_address = true;
        std::cout << "Enter the address of contact  :  ";
        std::getline(std::cin, address);
        for (int i{}; i < address.length(); ++i) {
            if (!(address[i] >= 'a' && address[i] <= 'z') 
            && !(address[i] >= 'A' && address[i] <= 'Z') 
            && !(address[i] >= '0' && address[i] <= '9') 
            && address[i] != '/' && address[i] != '-' 
            && address[i] != '_' && address[i] != ' ')
            {
                is_valid_address = false;
                std::cout << "Your input is not valid. Please, input the correct address or input '0' to go to main menu." << std::endl;
                break;
            }
        }
        if (address == "0") {
            show_main_menu();
        }
    } while (!is_valid_address);
    contact.set_address(address);
    return contact;
}

//հնարավորություն է տալիս user֊ին ընտրել, թե ինչն է ուզում փոխել տվյալ 
//կոնտակտի մեջ և կանչում է համապատասխան ֆունկցիան
void User::edit_contact(std::string& str)
{
    std::cout   << "What do you want to change?\n\n";
    std::cout   << "'n'_____edit name" << std::endl
                << "'s'_____edit surname" << std::endl
                << "'p'_____edit phone_number" << std::endl
                << "'a'_____edit address" << std::endl
                << "'x'_____main menu" << std::endl <<
    std::endl   << "your choice  ։  ";
    char symbol;
    std::cin >> symbol;
    switch (symbol) {
        case 'n': { edit_name(str); }
            break;                
        case 's' : { edit_surname(str); }
            break;
        case 'p' : { edit_phone_number(str); }
            break;
        case 'a' : { edit_address(str); }
            break;
        case 'x' : { show_main_menu(); }
            break;
        default : { 
            std::cout << "your input is not correct.";
            show_main_menu();
        }
    }
}

//փոխում է կոնտակտի անունը, փոփոխությունը ֆիքսում է ֆայլի մեջ
void User::edit_name(std::string& str)
{
    bool is_valid_name;
    std::string new_name;
    do {
        is_valid_name = true;
        std::cout << "please, input new name :  ";
        std::getline(std::cin, new_name);
        for (int i{}; i < new_name.length(); ++i) {
            if (!(new_name[i] >= 'a' && new_name[i] <= 'z') 
            && !(new_name[i] >= 'A' && new_name[i] <= 'Z') 
            && new_name[i] != ' ') {
                is_valid_name = false;
                std::cout << "Your input is not valid. Please, input the correct name․" << std::endl;
                break;
            }
        }
    } while (!is_valid_name);
    //նոր անվան վալիդացիան ստոգելուց հետո string֊ը վերածում ենք օբյեկտի,
    //անունը փոխում ենք
    Contact contact = string_to_Contact(str);
    contact.set_name(new_name);
    std::string str_contact = Contact_to_string(contact);//նորից վերածում ենք string֊ի
    //data֊ից ջնջում ենք հին կոնտակտը
    for (int i{}; i < data.size(); ++i) {
        if (str == data[i]) {
            data.erase(data.begin() + i);
        }
    }
    //թարմացվածը գցում ենք data վեկտորի մեջ
    data.push_back(str_contact);

    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << "name updated." << std::endl << std::endl;
    edit_contact(str);//էլի պարամետր փոխելու հնարավորություն ենք տալիս
}

//փոխում է կոնտակտի ազգանունը, փոփոխությունը ֆիքսում է ֆայլի մեջ
void User::edit_surname(std::string& str)
{
    bool is_valid_surname;
    std::string new_surname;
    do {
        is_valid_surname = true;
        std::cout << "please, input new surname :  ";
        std::getline(std::cin, new_surname);
        for (int i{}; i < new_surname.length(); ++i) {
            if (!(new_surname[i] >= 'a' && new_surname[i] <= 'z') 
            && !(new_surname[i] >= 'A' && new_surname[i] <= 'Z') 
            && new_surname[i] != ' ') {
                is_valid_surname = false;
                std::cout << "Your input is not valid. Please, input the correct surname․" << std::endl;
                break;
            }
        }
    } while (!is_valid_surname);
    Contact contact = string_to_Contact(str);
    contact.set_surname(new_surname);
    std::string str_contact = Contact_to_string(contact);//նորից վերածում ենք string֊ի
    //data֊ից ջնջում ենք հին կոնտակտը
    for (int i{}; i < data.size(); ++i) {
        if (str == data[i]) {
            data.erase(data.begin() + i);
        }
    }
    //թարմացվածը գցում ենք data վեկտորի մեջ
    data.push_back(str_contact);

    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << "surname updated." << std::endl << std::endl;
    edit_contact(str);//էլի պարամետր փոխելու հնարավորություն ենք տալիս
}

//փոխում է phone_number֊ը, փոփոխությունը ֆիքսում է ֆայլի մեջ
void User::edit_phone_number(std::string& str)
{
    bool is_valid_phone_number;
    std::string new_phone_number;
    do {
        is_valid_phone_number = true;
        std::cout << "please, input new phone_number :  ";
        std::cin >> new_phone_number;
        for (int i{}; i < new_phone_number.length(); ++i) {
            if (!(new_phone_number[i] >= '0' && new_phone_number[i] <= '9')) {
                is_valid_phone_number = false;
                std::cout << "Your input is not valid. Please, input the correct phone_number." << std::endl;
                break;
            }
        }
    } while (!is_valid_phone_number);
    Contact contact = string_to_Contact(str);
    //ստուգում ենք՝ արդյո՞ք տվյալ համարից արդեն գոյություն ունի, թե ոչ
    bool is_unique{true};
    for (int i{}; i < phone.size(); ++i) {
        if (phone[i] == new_phone_number) {
            is_unique = false;
            std::cout << "that phone_number already exists. Please, input another number" << std::endl;
        }
    }
    if (is_unique) {
        //ջնջում ենք հին համարը վեկտորի միջից
        for (int i{}; i < phone.size(); ++i) {
            if (contact.get_phone_number() == phone[i]) {
                phone.erase(phone.begin() + i);
            }
        } 
        phone.push_back(new_phone_number);
        contact.set_phone_number(new_phone_number); 
    }  
    std::string str_contact = Contact_to_string(contact);//նորից վերածում ենք string֊ի
    //data֊ից ջնջում ենք հին կոնտակտը
    for (int i{}; i < data.size(); ++i) {
        if (str == data[i]) {
            data.erase(data.begin() + i);
        }
    }
    //թարմացված կոնտակտի string֊ը գցում ենք data վեկտորի մեջ
    data.push_back(str_contact);
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << "phone_number updated." << std::endl << std::endl;
    edit_contact(str);//էլի պարամետր փոխելու հնարավորություն ենք տալիս
}

//փոխում է կոնտակտի հասցեն, փոփոխությունը ֆիքսում է ֆայլի մեջ
void User::edit_address(std::string& str)
{
    bool is_valid_address;
    std::string new_address;
    do {
        is_valid_address = true;
        std::cout << "Enter the new address for contact  :  ";
        std::getline(std::cin, new_address);
        for (int i{}; i < new_address.length(); ++i) {
            if (!(new_address[i] >= 'a' && new_address[i] <= 'z') 
            && !(new_address[i] >= 'A' && new_address[i] <= 'Z') 
            && !(new_address[i] >= '0' && new_address[i] <= '9') 
            && new_address[i] != '/' && new_address[i] != '-' 
            && new_address[i] != '_' && new_address[i] != ' ')
            {
                is_valid_address = false;
                std::cout << "Your input is not valid. Please, input the correct address." << std::endl;
                break;
            }
        }
    } while (!is_valid_address);
    Contact contact = string_to_Contact(str);
    contact.set_address(new_address);
    std::string str_contact = Contact_to_string(contact);//նորից վերածում ենք string֊ի
    //data֊ից ջնջում ենք հին կոնտակտը
    for (int i{}; i < data.size(); ++i) {
        if (str == data[i]) {
            data.erase(data.begin() + i);
        }
    }
    //թարմացվածը գցում ենք data վեկտորի մեջ
    data.push_back(str_contact);
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        edit_contact(str);
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << "address updated." << std::endl << std::endl;
    edit_contact(str);//էլի պարամետր փոխելու հնարավորություն ենք տալիս
}

//ֆունկցիան գտնում է ճիշտ կոնտակտը, ուղարկում ջնջելու
void User::find_to_remove_contact(std::string& name)
{
    std::vector<std::string> same_name_vec{};//նույն անունով կոնտակտների համար
    std::vector<std::string> same_surname_vec{};//նույն անուն֊ազգանունով կոնտակտների համար
    int contact_count{};
    std::string contact_name{};
    int current_index{};
    for (int i{}; i < data.size(); ++i) { //անցնում ենք data֊ի բոլոր էլեմենտների վրայով
        for (int j{8}; data[i][j] != '|'; ++j) {//գտնում ենք անունները
            contact_name += data[i][j];
            current_index = j;
        }
        if (contact_name == name) {//համեմատում ենք մուտքագրված անվան հետ
            contact_count++;//համընկումների քանակը
            same_name_vec.push_back(data[i]);
            std::cout << data[i] << std::endl;
        }
    }
    if (!contact_count) {
        std::cout << "No contact found with that name!!" << std::endl;
        show_main_menu();
    }
    else if (contact_count == 1) { //եթե ունենք ուղիղ մեկ համընկում
        remove_contact(same_name_vec[0]);
    }
    else {//if (contact_count > 1)
        std::cout << "It is not clear which contact you want to remove.\nPLease, input the surname  :  ";
        std::string surname;
        do {
            std::getline(std::cin, surname);
            std::string contact_surname{};
            contact_count = 0;
            for (int i{}; i < same_name_vec.size(); ++i) {
                for (int j{current_index + 12}; j != '|'; ++j) {
                    contact_surname += same_name_vec[i][j];//գտնում ենք ազգանունը
                    current_index = j;
                }
                if (contact_surname == surname) {
                    contact_count++;//համընկումների քանակը
                    same_surname_vec.push_back(same_name_vec[i]);
                    std::cout << same_name_vec[i] << std::endl;
                }
            }
            if (!contact_count) {
                std::cout << "No contact found with that surname!!" << std::endl;
                for (int i{}; i < same_name_vec.size(); ++i) {
                    std::cout << same_name_vec[i] << std::endl;
                }
                std::cout << "choose and input surname again to remove the correct contact." << std::endl;
            }
        } while (!contact_count);
        if (contact_count == 1) {
            remove_contact(same_surname_vec[0]);
        }
        else { //  if (contact_count > 1)
            int contact_index; //same_surname_vec վեկտորի մեջ փնտրվող կոնտակտի ինդեքսը 
            std::cout << "again it is not clear which contact you want to remove.\nPLease, input the phone_number  :  ";
            std::string phone_number{};
            do {
                std::cin >> phone_number;
                std::string contact_phone_number{};
                contact_count = 0;
                for (int i{}; i < same_surname_vec.size(); ++i) {
                    for (int j{current_index + 17}; j != '|'; ++j) {
                        contact_phone_number += same_surname_vec[i][j];
                        current_index = j;
                    }
                    if (contact_phone_number == phone_number) {
                        contact_count++;
                        std::cout << same_surname_vec[i] << std::endl;
                        contact_index = i; //կոնտակտը գտանք
                    }
                }
                if (!contact_count) {
                    std::cout << "No contact found with that phone_number!!" << std::endl;
                    for (int i{}; i < same_surname_vec.size(); ++i) {
                        std::cout << same_surname_vec[i] << std::endl;
                    }
                    std::cout << "choose and input phone_number again to remove the correct conact." << std::endl;
                }
            }while (!contact_count);
            if (contact_count == 1) {
                remove_contact(same_surname_vec[contact_index]);
            }
            //մեկից ավել համընկումը հեռախոսահամարի դեպքում բացառվում է
        }
    }
}

//ֆունկցիան փոխանցված կոնտակտը ջնջում է data վեկտորի միջից, ջնջում է նաև ֆայլից,
//հեռախոսահամարը ևս ջնջում է phone֊ի միջից
void User::remove_contact(std::string& str)
{
    for (int i{}; i < data.size(); ++i) {
        if (str == data[i]) {
            data.erase(data.begin() + i);
        }
    }
    Contact obj = string_to_Contact(str);
    for (int i{}; i < phone.size(); ++i) {
        if (obj.get_phone_number() == phone[i]) {
            phone.erase(phone.begin() + i);
        }
    }
    tmpfout.open("tmp.txt", std::ios::out | std::ios::app);
    if (!tmpfout.is_open()) {
        std::cout << "file handling error!!!" << std::endl;
        show_main_menu();
    }
    else {
        for (int i{}; i < data.size(); ++i) {
            tmpfout << data[i] << std::endl;
        }
        remove("phone_book.txt");
        rename("tmp.txt", "phone_book.txt");
    }
    tmpfout.close();
    std::cout << "contact removed saccessfully!!" << std::endl << std::endl;
    show_main_menu();
}

//user֊ին հնարավորություն է տալիս ընտրելու թե ըստ ինչ պարամետրի գտնի կոնտակտը
void User::find_to_show_contact()
{
    std::cout << "\nwhat do you want to find the contact by?" << std::endl << std::endl;
    std::cout << "=========================" << std::endl
              << "'n'_______________by name" << std::endl
              << "'s'____________by surname" << std::endl
              << "'p'_______by phone_number" << std::endl
              << "'a'____________by address" << std::endl
              << "'x'_______go to main menu" << std::endl
              << "=========================" << std::endl <<
    std::endl << "your choise  :  ";
    char symbol;
    std::cin >> symbol;
    switch (symbol) {
        case 'n': { show_by_name(); }
            break;                
        case 's' : { show_by_surname(); }
            break;
        case 'p' : { show_by_phone_number(); }
            break;
        case 'a' : { show_by_address(); }
            break;
        case 'x' : { show_main_menu(); }
            break;
        default : {
            std::cout << "your input is not correct." << std::endl;
            show_main_menu();
        }
    }
}

//ֆունկցիան ցուցադրում է բոլոր այն կոնտակտները, որոնց անունը համընկնում է մուտքագրված անվան հետ
void User::show_by_name() const
{
    std::cout << "please, input contact name  :  ";
    std::string name;
    bool find;
    do {
        find = false;
        std::getline(std::cin, name);
        Contact obj;
        for (int i{}; i < data.size(); ++i) {
           obj = string_to_Contact(data[i]);
           if (obj.get_name() == name) {
               find = true;
               std::cout << data[i] << std::endl;
           }
        }
        if (!find) {
            std::cout << "no contact found with that name. Please, input another name  :  ";
        }
    }while(!find); 
}

//ֆունկցիան ցուցադրում է բոլոր այն կոնտակտները, որոնց ազգանունը համընկնում է մուտքագրված ազգանվան հետ
void User::show_by_surname() const
{
    std::cout << "please, input contact surname  :  ";
    std::string surname;
    bool find;
    do {
        find = false;
        std::getline(std::cin, surname);
        Contact obj;
        for (int i{}; i < data.size(); ++i) {
           obj = string_to_Contact(data[i]);
           if (obj.get_surname() == surname) {
               find = true;
               std::cout << data[i] << std::endl;
           }
        }
        if (!find) {
            std::cout << "no contact found with that surname. Please, input the another surname  :  ";
        }
    }while(!find); 
}

//ֆունկցիան ցուցադրում է մուտքագրված հեռախոսահամարին համապատասխան կոնտակտը
void User::show_by_phone_number() const
{
    std::cout << "please, input phone_number  :  ";
    std::string phone_number;
    bool find;
    do {
        find = false;
        std::cin >> phone_number;
        Contact obj;
        for (int i{}; i < data.size(); ++i) {
           obj = string_to_Contact(data[i]);
           if (obj.get_phone_number() == phone_number) {
               find = true;
               std::cout << data[i] << std::endl;
               break;
           }
        }
        if (!find) {
            std::cout << "no contact found with that phone_number. Please, input another phone_number  :  ";
        }
    }while(!find); 
}

//ֆունկցիան ցուցադրում է բոլոր այն կոնտակտները, որոնց հասցեն համընկնում է մուտքագրված հասցեի հետ
void User::show_by_address() const
{
    std::cout << "please, input contact address  :  ";
    std::string address;
    bool find;
    do {
        find = false;
        std::getline(std::cin, address);
        Contact obj;
        for (int i{}; i < data.size(); ++i) {
           obj = string_to_Contact(data[i]);
           if (obj.get_address() == address) {
               find = true;
               std::cout << data[i] << std::endl;
           }
        }
        if (!find) {
            std::cout << "no contact found in that address. Please, input another address  :  ";
        }
    }while(!find); 
}
#endif//USER_HPP