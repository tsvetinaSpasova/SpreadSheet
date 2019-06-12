#include "CellDouble.h"
#include "SpreadSheet.h"

CellDouble:: CellDouble(double _cell, size_t _numOfRow, size_t _numOfCol)
{
    cell = _cell;
    numOfRow = _numOfRow;
    numOfCol = _numOfCol;
}

Cell* CellDouble::clone() const
{
    CellDouble* newCell = new CellDouble(cell, numOfRow, numOfCol);
    return newCell;
}

size_t CellDouble:: getSizeOfCell () const
{
    ///stack overflow;
    std:: ostringstream strs;
    strs << cell;
    std:: string str = strs.str();
    return str.size();
}

double CellDouble:: getValue(SpreadSheet* sheet) const
{
    return cell;
}

size_t CellDouble:: getCellNumOfRow () const
{
    return numOfRow;
}

size_t CellDouble:: getCellNumOfCol () const
{
    return numOfCol;
}

void CellDouble:: write(std:: ostream& out, SpreadSheet* sheet) const
{
    out << cell;
}

bool CellDouble:: read(std:: istream& in)
{
        in >> cell;
        in.ignore();
        return true;
}

void CellDouble:: printCell(SpreadSheet* sheet)
{
    std:: cout << cell;
}

