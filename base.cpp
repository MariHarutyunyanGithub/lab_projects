#include <iostream>

#include "base.h"

//ֆունկցիան user֊ին ներկայացնում է այն գործողությունները (համապատասխան կոդերով),
//որոնք support է անում ծրագիրը, ընդունում է user֊ից կոդը, ստուգում է վալիդությունը,
//վերջում կանչում է menu_functions(short) ֆունկցիան
void Base::show_main_menu()
{
    std::cout   << std::endl << std::endl 
                << "==========================" << std::endl;
    std::cout   << "[1]- add new contact\n"  								
                << "[2]- edit contact\n"				
                << "[3]- remove contact\n"				
                << "[4]- show contact\n"
                << "[5]- exit from program\n"
                << "==========================\n\n"
                << "your choise: ___\b\b";
    short key;
    do{
        std::cin >> key;
        if (key < 1 || key > 5){
            std::cout << "your input is not correct, please, input an integer from [1;5].\n";
        }
    }while (key < 1 || key > 5);
    menu_functions(key);
}

void Base::exit_from_program()
{
	std::cout << "are you sure, you really want to exit from program?(y / n) \n";
	std::string key;
	do {
		std::cin >> key;	
		if (key != "y" && key != "n"){
			std::cout << "your input is not correct. Please, input 'y' or 'n'\n";	
		}
	}while(key != "y" && key != "n");				
		if(key == "y"){
			std::cout << "\n\n===========  BYE  ==========\n\n";
			exit(0);
		}else if(key == "n"){
			show_main_menu();					
		}
}

//ստանալով կոդը user֊ից, կանչում է համապատասխան ֆունկցիան
void Base::menu_functions(short key)
{
    switch(key){
        case 1: {add_new_contact();}
            break;		
        case 2: {std::cout << "\nPlease, input the contact name to edit\n";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            find_to_edit_contact(name);}
            break;
        case 3: {std::cout << "\nPlease, input the contact name to remove\n";
            std::string name;
            std::cin.ignore();
            std::getline(std::cin, name);
            find_to_remove_contact(name);}
            break;
        case 4: {find_to_show_contact();}
            break;
        case 5: { exit_from_program(); }
            break;
        default :{std::cout << "\nyour input is not correct. Please, input numbers from diapazone [1;5]";
            show_main_menu();
        }	
    }
}