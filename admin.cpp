#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <iostream>

#include "admin.h"

//Ֆունկցիան բացում է ֆայլը, պարունակությունը տող առ տող գցում data վեկտորի մեջ,
//փակում է ֆայլը, ողջունում է user֊ին, վերջում կանչում է admin.show_main_menu() ֆունկցիան
void Admin::start()
{
	fin.open("phone_book.txt", std::ios::in);
    if (!fin.is_open()) {
        std::cout << "The file \"phone_book.txt\" is not opened, please, try again.";
        exit(0);
    }
    else {
		std::string line{};
        while (std::getline(fin, line)) {
			data.push_back(line);// global vector in file user.h
		}
		fout.close();
		std::cout << "========== WELLCOME ==========" << std::endl;
		show_main_menu();
    }
}

#endif //ADMIN_HPP