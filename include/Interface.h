#ifndef INTERFACE_H
#define INTERFACE_H
#include "SpreadSheet.h"

class Interface
{
    public:
        Interface();
        void menu ();
        void print ();
        void edit ();
    private:
        SpreadSheet sheet;
};

#endif // INTERFACE_H
