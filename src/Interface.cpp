#include "Interface.h"

Interface::Interface()
{
    //menu();
}


void Interface:: menu ()
{
    std:: cout << "======= Spreadsheet ========" << std:: endl;
    std:: cout << "| | ======= Menu ======= | | " << std:: endl;
    std:: cout << "| |   |print|edit|exit|  | |  " << std:: endl;
    std:: cout << "============================" << std:: endl;

    std:: string command;

    do
    {
        std:: cin >> command;

        if(command == "print")
        {
            print();
        }
        else if(command == "edit")
        {
            edit();
        }
        else
        {
            std:: cout << "Wrong command! Try again... " << std:: endl;

        }
    }
    while(command != "exit");
}

void Interface:: print ()
{
    std:: cout << "File: ";
    std:: string filename;
    std:: cin >> filename;
    //std:: cin.ignore();
    sheet.load(filename);
    sheet.print();
    std:: cout << std:: endl;

}

void Interface:: edit ()
{
    std:: cout << "File: ";
    std:: string filename;
    std:: cin >> filename;
    size_t row, col;
    std:: cout<< "Row: ";
    std:: cin >> row;
    std:: cout << "Col: ";
    std:: cin >> col;
    std:: cout << "New cell: ";
    sheet.load(filename);
    sheet.edit(row, col);
    sheet.save(filename);
}
