#include "CellString.h"
#include "SpreadSheet.h"


CellString::CellString (std:: string _cell, size_t _numOfRow, size_t _numOfCol)
{
    cell = _cell;
    numOfRow = _numOfRow;
    numOfCol = _numOfCol;
}

size_t CellString:: getCellNumOfRow () const
{
    return numOfRow;
}

double CellString:: getValue(SpreadSheet* sheet) const
{
    return 0;
}

size_t CellString:: getCellNumOfCol () const
{
    return numOfCol;
}

Cell* CellString::clone() const
{
    CellString* copyCell = new CellString(cell, numOfRow, numOfCol);
    return copyCell;
}

void CellString:: write(std::ostream& out,SpreadSheet* sheet) const
{
    if(cell[0] == '=')
    {
        out<< "ERROR";
        return;
    }
    out << cell;
}

void CellString:: printCell(SpreadSheet* sheet)
{
    if(cell[0] == '=')
    {
        std:: cout <<"ERROR";
        return;
    }
    std:: cout << cell;
}

std:: string CellString:: getCell () const
{
    return cell;
}

size_t CellString:: getSizeOfCell () const
{
    return cell.size();
}

char& CellString:: operator [] (size_t position)
{
    return cell[position];
}

bool CellString:: read(std:: istream& in)
{
        getline(in, cell, ',');
        return true;
}
