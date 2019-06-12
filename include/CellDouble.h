#ifndef CELLDOUBLE_H
#define CELLDOUBLE_H
#include <iostream>
#include "Cell.h"
#include <sstream>

class CellDouble: public Cell
{
    public:
        CellDouble(double _cell, size_t _numOfRow, size_t _numOfCol);
        virtual void write(std:: ostream& out, SpreadSheet* sheet) const;
        virtual bool read(std:: istream& in);
        virtual void printCell(SpreadSheet* sheet);
        virtual size_t getSizeOfCell () const;
        virtual double getValue(SpreadSheet*) const;
        virtual size_t getCellNumOfRow () const;
        virtual size_t  getCellNumOfCol () const;
        virtual Cell* clone() const;

    private:
        double cell;
};

#endif // CELLDOUBLE_H
