#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <fstream>

class SpreadSheet;

class Cell
{
    public:
       /// Cell clone () const;
        virtual void write(std:: ostream& out, SpreadSheet* sheet) const = 0;
        virtual bool read(std:: istream& in) = 0;
        virtual void printCell(SpreadSheet* sheet) = 0;
        virtual size_t getSizeOfCell () const = 0;
        virtual double getValue(SpreadSheet*) const = 0;
        virtual size_t getCellNumOfRow () const = 0;
        virtual size_t getCellNumOfCol () const = 0;
        virtual Cell* clone() const = 0;

    protected:
        size_t numOfRow;
        size_t numOfCol;
};

#endif // CELL_H
