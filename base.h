#ifndef __BASE__
#define __BASE__

#include <iostream>
#include <vector>
#include <fstream>

class Base
{
public:
    virtual ~Base() = default;
    void show_main_menu(); 
    void exit_from_program();     
    void menu_functions(short);
public:
    virtual void add_new_contact();
    virtual void find_to_edit_contact(std::string&);
    virtual void find_to_remove_contact(std::string&);
    virtual void find_to_show_contact();
public:
    std::ofstream fout;
    std::ofstream tmpfout;
    std::ifstream fin;
    std::vector<std::string> data;//կոնտակտները պահելու համար
    std::vector<std::string> phone;//հեռախոսահամարները պահելու համար

};

#endif