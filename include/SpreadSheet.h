#ifndef SPREADSHEET_H
#define SPREADSHEET_H
#include "Cell.h"
#include "CellDouble.h"
#include "CellString.h"
#include "Formula.h"
#include <string>
#include <iostream>
#include <fstream>
#include<vector>


class SpreadSheet
{
    public:

        ~SpreadSheet ();
        std:: vector<int> findLongestSizesForCol();

        size_t getRows() const;
        size_t getCols(size_t inRow) const;

        friend std:: istream&  operator >> (std:: istream& in, SpreadSheet& otherSheet);
        double findValueOfCell(size_t row, size_t col);
        int calcMaxRowSize() const;

        void print();
        void edit(int row, int col);
        void load(std:: string filename);
        void save(std:: string filename);

    private:

        void writeWhiteSpaces (int numOfWhiteSpaces, std:: ostream& out);

    private:
        std:: vector< std:: vector <Cell*> > sheet;
};

bool isNumber(std::string text);
bool isValid(std::string text);
bool isCell(std::string text);
bool isFormula(std::string text);

void clearWhiteSpaces(std::string& text);
int castToInt(std::string, int&);
double castTodouble(std::string, int);

#endif // SPREADSHEET_H
