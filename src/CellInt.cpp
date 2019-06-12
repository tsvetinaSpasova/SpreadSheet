#include "CellInt.h"

CellInt:: CellInt(int _cell, size_t _numOfRow, size_t _numOfCol) : Cell(_numOfRow, _numOfCol)
{
    cell = _cell;
}

size_t CellInt:: getSizeOfCell () const
{
    size_t sizeOfCell = 0;
    do
    {
        sizeOfCell++;
        cell = cell / 10;
    }
    while(cell != 0);
    return sizeOfCell;
}

double CellInt:: getValue() const
{
    return cell;
}

size_t CellInt:: getCellsNumOfRow () const
{
    return numOfRow;
}

size_t CellInt:: getCellsNumOfCol () const
{
    return numOfCol;
}

void CellInt:: write(std:: ostream& out, size_t numOfWhiteSpaces) const
{
    out << cell;
    for(int i = 0; i < numOfWhiteSpaces; i++)
    {
        out <<" ";
    }
    out << '|';
}

bool CellInt:: read(std:: istream& in)
{
    if (Cell::read(in))
    {
        in >> cell;
        in.ignore();
        return true;
    }
    else
    {
        return false;
    }
}

