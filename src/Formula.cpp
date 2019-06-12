#include "Formula.h"
#include "SpreadSheet.h"

bool correctFormula = false;


bool Formula:: candidateFormula(char symb) const
{
    return symb == '=';
}


double Formula:: doCalculate(double first, double second, char symb) const
{
    switch(symb)
    {
        case '+': return first + second; break;
        case '-': return first - second; break;
        case '*': return first * second; break;
        case '/': return first / second; break;

    }
    return 0;


}

Cell* Formula::clone() const
{
    Formula* newCell = new Formula(cell, numOfRow, numOfCol);
    return newCell;
}


void Formula:: clearWhiteSpaces ()
{

    int index = 0;
    for(size_t i = 0; i < cell.size(); i++)
    {
        if(cell[i] == ' ')
            continue;
        cell[index] = cell[i];
        index ++;
    }

    cell.resize(index);
}

bool Formula:: correctOperation (char symb) const
{
    return (symb == '+' || symb == '-' || symb == '*' || symb == '/');
}

int Formula:: castToInt(int &startIndex) const
{
    int finalInt = 0;
    int length = cell.size();
    for( ; startIndex < length; startIndex++)
    {
        if(cell[startIndex] < '0' || cell[startIndex] > '9')
        {
            return finalInt;
        }
        finalInt *= 10;
        finalInt += cell[startIndex] - '0';
    }
    return finalInt;
}

double Formula:: castToDouble(int &startIndex) const
{
    double finalDouble = 0;
    int integerPart = castToInt(startIndex);
    int doublePart = 0;
    if(cell[startIndex] == '.')
    {
        startIndex++;
        doublePart = castToInt(startIndex);
    }
    finalDouble = integerPart;
    double curDouble = 0;
    while(doublePart)
    {
        curDouble += doublePart%10;
        curDouble /= 10;
        doublePart /= 10;
    }
    finalDouble += curDouble;
    return finalDouble;
}


double Formula:: calculateFormula (SpreadSheet* sheet) const
{

    int length = cell.size();
    double first, second;
    char symb;
    int row, col, startIndex = 1;

    if(cell[startIndex] == 'R')
    {
        row = castToInt(++startIndex);
        col = castToInt(++startIndex);

        first = sheet -> findValueOfCell(row, col);

    }
    else if(cell[startIndex] >= '0' &&  cell[startIndex] <= '9')
    {
        first = castToDouble(startIndex);
    }

    symb = cell[startIndex++];

    if(cell[startIndex] == 'R')
    {
        row = castToInt(++startIndex);
        col = castToInt(++startIndex);

        second = sheet -> findValueOfCell(row, col);

    }
    else if(cell[startIndex] >= '0' &&  cell[startIndex] <= '9')
    {

        second = castToDouble(startIndex);

    }

    if (symb == '/' && second == 0)
    {
        correctFormula = false;
    }

    double newValueOfCell = doCalculate(first, second, symb);

    return newValueOfCell;
}

Formula:: Formula (std:: string _cell, size_t _numOfRow, size_t _numOfCol)
{
    cell = _cell;
    numOfRow = _numOfRow;
    numOfCol = _numOfCol;
    correctFormula = true;
}

size_t Formula:: getCellNumOfRow () const
{
    return numOfRow;
}

double Formula:: getValue(SpreadSheet* sheet) const
{
    return calculateFormula(sheet);
}
void Formula:: printCell(SpreadSheet* sheet)
{
    double value = calculateFormula(sheet);
    std:: cout << "yes";
    if(correctFormula)
    {
        std:: cout << value;
        return;
    }
    std:: cout << "ERROR";
}

size_t Formula:: getCellNumOfCol () const
{
    return numOfCol;
}

void Formula:: write(std::ostream& out, SpreadSheet* sheet) const
{
    double value = calculateFormula(sheet);
    std:: cout << "yes";
    if(correctFormula)
    {
        out << value;
        return;
    }
    out<< "ERROR";
}

std:: string Formula:: getCell () const
{
    return cell;
}

size_t Formula:: getSizeOfCell () const
{
    return cell.size();
}

char& Formula:: operator [] (size_t position)
{
    return cell.at(position);
}

bool Formula:: read(std:: istream& in)
{
        getline(in, cell, ',');
        return true;
}
