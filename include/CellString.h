#ifndef CELLSTRING_H
#define CELLSTRING_H
#include "Cell.h"
#include <string>

class CellString : public Cell
{
    public:

        CellString (std:: string _cell, size_t _numOfRow, size_t _numOfCol);
        std:: string getCell () const;
        virtual size_t getSizeOfCell () const;
        virtual double getValue(SpreadSheet*) const;
        char& operator [] (size_t position);
        virtual void printCell(SpreadSheet* sheet);
        virtual void write(std:: ostream& out,SpreadSheet* sheet) const;
        virtual bool read(std:: istream& in);
        virtual size_t getCellNumOfRow () const;
        virtual size_t  getCellNumOfCol () const;
        virtual Cell* clone() const;

    private:
        std:: string cell;
};

#endif // CELLSTRING_H
