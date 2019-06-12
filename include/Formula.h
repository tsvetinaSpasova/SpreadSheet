#ifndef FORMULA_H
#define FORMULA_H
#include "Cell.h"


class Formula: public Cell
{
    public:
        Formula (std:: string _cell, size_t _numOfRow, size_t _numOfCol);
        std:: string getCell () const;
        virtual size_t getSizeOfCell () const;
        virtual double getValue(SpreadSheet*) const;
        char& operator [] (size_t position);
        virtual void printCell(SpreadSheet* sheet);
        virtual void write(std:: ostream& out, SpreadSheet* sheet) const;
        virtual bool read(std:: istream& in);
        virtual size_t getCellNumOfRow () const;
        virtual size_t  getCellNumOfCol () const;
        virtual Cell* clone() const;
        double calculateFormula(SpreadSheet* sheet) const;

    private:
        bool candidateFormula(char symb) const;
        bool correctOperation (char symb) const;
        //double castToDoubleCell(Cell* cell);
        int castToInt(int& startIndex) const;
        double castToDouble(int& startIndex) const;
        void clearWhiteSpaces ();
        double doCalculate(double first, double second, char symb) const;
        Cell* convertCoordToCell (size_t row, size_t col);


    private:
        std:: string cell;

};


#endif // FORMULA_H
