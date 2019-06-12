#ifndef CELLINT_H
#define CELLINT_H
#include "Cell.h"

class CellInt : public Cell
{
   public:
        CellInt(int cell, size_t _numOfRow, size_t _numOfCol);
        virtual void write(std:: ostream& out, size_t numOfWhiteSpaces) const;
        virtual bool read(std:: istream& in);
        size_t getSizeOfCell () const;
        virtual double getValue() const;
        virtual size_t getCellsNumOfRow () const;
        virtual size_t  getCellsNumOfCol () const;

    private:
        int cell;
};

#endif // CELLINT_H
