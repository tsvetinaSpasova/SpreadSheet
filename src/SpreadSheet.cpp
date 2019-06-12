#include "SpreadSheet.h"
#include "Formula.h"

SpreadSheet:: ~SpreadSheet ()
{
    int rows = getRows();
    for (int row = 0; row < rows; row++)
    {
        int cols = getCols(row);
        for(int col = 0; col < cols; col++)
        {
           delete sheet[row][col];
        }
    }
}


double SpreadSheet:: findValueOfCell (size_t row, size_t col)
{

    for(int currentRow = 0; currentRow < sheet.size(); currentRow++)
    {

        for(int currentCol = 0; currentCol < sheet[currentRow].size(); currentCol++)
        {
            if (row == sheet[currentRow][currentCol] -> getCellNumOfRow() && col == sheet[currentRow][currentCol] -> getCellNumOfCol())
            {
                return sheet[currentRow][currentCol]->getValue(this);
            }
        }

    }

    return 0;
}



unsigned int SpreadSheet::  getRows() const
{
    return sheet.size();
}

unsigned int SpreadSheet:: getCols(unsigned int inRow) const
{
    if(inRow >= sheet.size())
        return 0;
    return sheet[inRow].size();
}

void SpreadSheet:: writeWhiteSpaces (int numOfWhiteSpaces, std:: ostream& out)
{
    for (int i = 0; i < numOfWhiteSpaces; i++)
    {
        out << " ";
    }
    out << '|';
}

int SpreadSheet:: calcMaxRowSize() const
{
    int maxRowSize = 0;
    for(int i = 0; i < sheet.size(); i++)
    {
        maxRowSize = std:: max(maxRowSize, (int)sheet[i].size());
    }

    return maxRowSize;
}

std:: vector<int> SpreadSheet:: findLongestSizesForCol()
{
    int longestSize;
    std:: vector<int> longestSizeForCol;
    int row = 0;
    int maxRowSize = calcMaxRowSize();
    for(int col = 0; col < maxRowSize; col++)
    {   longestSize = 0;

        for(row = 0; row < sheet.size() ; row++)
        {
            if(col >= sheet[row].size())
                continue;
            if (sheet[row][col] -> getSizeOfCell() > longestSize)
                longestSize = sheet[row][col]-> getSizeOfCell();
        }
        longestSizeForCol.push_back(longestSize);
    }
    return longestSizeForCol;
}

int castToInt(std::string text, int &startIndex)
{
    int finalInt = 0;
    int length = text.size();
    for( ; startIndex < length; startIndex++)
    {
        if(text[startIndex] < '0' || text[startIndex] > '9')
        {
            return finalInt;
        }
        finalInt *= 10;
        finalInt += text[startIndex] - '0';
    }
    return finalInt;
}

double castToDouble(std::string text, int startIndex)
{
    double finalDouble = 0;
    int integerPart = castToInt(text, startIndex);
    int doublePart = 0;
    if(startIndex == '.')
    {
        doublePart = castToInt(text, startIndex);
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


void SpreadSheet:: print()
{

    std:: vector<int> longestSizeForCol;
    longestSizeForCol =  findLongestSizesForCol();

    int maxRowSize = calcMaxRowSize();

    for (int row = 0; row < sheet.size(); row++)
    {
        for (int col = 0; col < maxRowSize; col++)
        {
                if(col < sheet[row].size())
                {
                    int numWhiteSpaces = longestSizeForCol[col] - sheet[row][col] -> getSizeOfCell();
                    sheet[row][col] -> printCell(this);
                    writeWhiteSpaces (numWhiteSpaces, std:: cout); /// and the end of the cell '|'
                }
                else
                {
                    writeWhiteSpaces(longestSizeForCol[col], std:: cout); /// and the end of the cell '|'
                }
        }
        std:: cout << std:: endl;
    }

}



std:: istream&  operator >> (std:: istream& in, SpreadSheet& otherSheet)
{

    otherSheet.sheet.clear();

    int numOfRows;
    std:: cout << "How many rows you want to have your sheet: ";
    in >> numOfRows;
    otherSheet.sheet.resize(numOfRows);

    in.ignore();

    for(int row = 0; row < numOfRows; row++)
    {
        std::cout<< "Row " << row << ". ";
        std::string currRow;

        getline(in, currRow);
        clearWhiteSpaces(currRow);

        int currCol = 0;
        int startIndex = 0;

        for(int i = 0; i < currRow.size(); i++)
        {
            if(currRow[i] == ',' || i == currRow.size() - 1)
            {
                if(currRow[i] != ',' && i == currRow.size() - 1)
                {
                    i++;
                }
                std::string currCell = currRow.substr(startIndex, i - startIndex);
                if(isNumber(currCell))
                {
                    CellDouble toAdd(castToDouble(currCell, 0), row, currCol);
                    otherSheet.sheet[row].push_back(toAdd.clone());
                }
                else if(isFormula(currCell))
                {
                    Formula toAdd(currCell, row, currCol);
                    otherSheet.sheet[row].push_back(toAdd.clone());
                }
                else
                {
                    CellString toAdd(currCell, row, currCol);
                    otherSheet.sheet[row].push_back(toAdd.clone());
                }

                startIndex = i + 1;
                currCol ++;
            }
        }
    }

    return in;
}


void SpreadSheet:: edit (int row, int col)
{
    row--;
    col--;
    size_t sheetRows = getRows();
    size_t sheetCols = getCols(row);



    if(row >= sheetRows || row < 0 || col < 0 || col >= sheetCols)
    {
       std:: cout << "There is no cell on that row or col"<< std:: endl;
        return;
    }

    std::string newCell;
    std::cin.ignore();
    getline(std:: cin, newCell);
    if(isNumber(newCell))
    {
        CellDouble toAdd(castToDouble(newCell, 0), row , col);
        sheet[row][col] = toAdd.clone();
    }
    else if(isFormula(newCell))
    {
        Formula toAdd(newCell, row, col);
        sheet[row][col] = toAdd.clone();
    }
    else
    {
        CellString toAdd(newCell, row, col);
        sheet[row][col] = toAdd.clone();
    }


}


void SpreadSheet::load(std::string filename)
{

    std::ifstream in(filename);
    if(in.fail())
    {
        std:: cout << "file doesn't exist" << std:: endl;
        return;
    }
    sheet.clear();

    int numOfRows;
    in >> numOfRows;

    in.ignore();

    sheet.resize(numOfRows);

    for(int row = 0; row < numOfRows; row++)
    {
        std::string currRow;

        getline(in, currRow);
        clearWhiteSpaces(currRow);

        int currCol = 0;
        int startIndex = 0;

        for(int i = 0; i < currRow.size(); i++)
        {
            if(currRow[i] == ',' || i == currRow.size() - 1)
            {
                if(currRow[i] != ',' && i == currRow.size() - 1)
                {
                    i++;
                }
                std::string currCell = currRow.substr(startIndex, i - startIndex);
                if(isNumber(currCell))
                {
                    CellDouble toAdd(castToDouble(currCell, 0), row, currCol);
                    sheet[row].push_back(toAdd.clone());
                }
                else if(isFormula(currCell))
                {
                    Formula toAdd(currCell, row, currCol);
                    sheet[row].push_back(toAdd.clone());
                }
                else
                {
                    CellString toAdd(currCell, row, currCol);
                    sheet[row].push_back(toAdd.clone());
                }

                startIndex = i + 1;
                currCol ++;
            }
        }

    }
    in.close();
}

void SpreadSheet:: save(std:: string filename)
{
    std:: ofstream out (filename);

    std:: vector<int> longestSizeForCol;
    longestSizeForCol =  findLongestSizesForCol();

    int maxRowSize = calcMaxRowSize();

    out << sheet.size() << std::endl;

    for (int row = 0; row < sheet.size(); row++)
    {
        for (int col = 0; col < maxRowSize; col++)
        {
                if(col < sheet[row].size())
                {

                    sheet[row][col] -> write(out, this);
                    out << ",";

                }
        }
        out << std:: endl;
    }
   // filename.close();
}



void clearWhiteSpaces(std::string& text)
{
    int index = 0;
    for(size_t i = 0; i < text.size(); i++)
    {
        if(text[i] == ' ')
            continue;
        text[index] = text[i];
        index ++;
    }

    text.resize(index);
}

bool isNumber(std::string text)
{
    int cntPoints = 0;
    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] == '.')
        {
            cntPoints ++;
            continue;
        }
        if(text[i] < '0' || text[i] > '9')
        {
            return false;
        }
    }
    return cntPoints <= 1;
}

bool isCell(std::string text)
{
    if(text[0] != 'R')
        return false;
    int index;
    for(index = 1; index < text.size() ; index++)
    {
        if(text[index] == 'C')
            break;
        if(text[index] < '0' || text[index] > '9')
            return false;
    }
    if(index == text.size())
        return false;
    index ++;
    for( ; index < text.size(); index++)
    {
        if(text[index] < '0' || text[index] > '9')
            return false;
    }
    return true;


}



bool isValid(std::string text)
{
    if(isNumber(text))
        return true;
    if(isCell(text))
        return true;
    return false;
}

bool isFormula(std::string text)
{
    if(!text.size())
        return false;
    if(text[0] != '=')
        return false;
    int index = 1;

    int numCells = 0;

    while(index < text.size())
    {
        numCells ++;
        if(numCells >= 3)
        {
            break;
        }
        int curIndex = index;
        for( ; index < text.size(); index ++)
        {
            if(text[index] == '*' || text[index] == '-' || text[index] == '+' || text[index] == '/')
            {
                break;
            }
        }
        if(!isValid(text.substr(curIndex, index - curIndex)))
        {
            return false;
        }
    }



    return numCells == 2;
}
