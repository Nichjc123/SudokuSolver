#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <map>
#include "./helpers/helpers.h"

// Type alias for nested vector representing board
using Board_Type = std::vector<std::vector<char>>;

// constant value of board width/height
constexpr int boardSize = 9;

class Sudoku {
    private:
        Board_Type Board{};
        //Checking presence of value in column
        bool inCol(const int col, const char value) {
            for (int row{0}; row < boardSize; ++row) 
            {
                if (Board[row][col] == value) {
                    return true;
                }
            }
            return false;
        };
        //Checking presence of value in row
        bool inRow(int row, char value) {
            for (int col{0}; col < boardSize; ++col) 
            {
                if (Board[row][col] == value) {
                    return true;
                }
            }
            return false;
        };
        //Checking value in 3x3 block
        bool inBlock(const int col_in, const int row_in, const char value) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (Board[row+row_in][col+col_in] == value)
                        return true;
                }
            }
            return false;
        };
    public:
        Sudoku() {
            // Have user create their own board? 9x9 board
            Board_Type temp(boardSize, std::vector<char>(boardSize));

            //Array of possible cell values
            const std::array<char, 10> possibleVals{'0','1','2','3','4','5','6','7','8','9'};

            std::cout << "Create your board now! When prompted please only enter values between 0 - 9." << std::endl;

            //Gather user input for sudoku board
            for (std::size_t row{0}; row < boardSize; ++row) 
            {
                for (std::size_t col{0}; col < boardSize; ++col)
                {
                    char cellValue{};
                    // Loop w/ input validation
                    do {
                        std::cout << "Please enter value for column " << col + 1 << " row " << row + 1 << std::endl;
                        std::cin >> cellValue;
                        if (!arrayContains(possibleVals, cellValue)) {
                            std::cout << "Invalid entry please try again" << std::endl;
                        }
                    }
                    while (!arrayContains(possibleVals, cellValue));
                    temp.at(row).at(col) = cellValue;
                }
            }
            Board = temp;

            // Medium difficulty solvable Board for testing
            // Board = {
            //     {'0','0','0','2','6','0','7','0','1'},
            //     {'6','8','0','0','7','0','0','9','0'},
            //     {'1','9','0','0','0','4','5','0','0'},
            //     {'8','2','0','1','0','0','0','4','0'},
            //     {'0','0','4','6','0','2','9','0','0'},
            //     {'0','5','0','0','0','3','0','2','8'},
            //     {'0','0','9','3','0','0','0','7','4'},
            //     {'0','4','0','0','5','0','0','3','6'},
            //     {'7','0','3','0','1','8','0','0','0'},
            // };
        }
        
        void print_Board(){
            for (std::size_t row{0}; row < boardSize; ++row) 
            {
                std::cout << "[";
                for (std::size_t col{0}; col < boardSize; ++col)
                {
                    std::cout << Board[row][col] << ", ";
                }
                std::cout << "]" << std::endl;
            }
        }
        
        // Check if placing value at col,row is a valid move
        bool isValidMove(const int col, const int row, const char value) {
            //Verify presence in column, row, and 3x3 grid
            if (!inCol(col, value) && !inRow(row, value) && !inBlock(col - col%3, row - row%3, value)) {
                return true;
            } else {
                return false;
            }
        };

        // Given row,col coordinates locate next exmpty cell and update row,colw
        bool findNextEmptyCell(int& row, int& col) {
            for (row = 0; row < boardSize; ++row)
                for (col = 0; col < boardSize; ++col)
                    if (Board[row][col] == '0') 
                        return true;
            return false;
        };

        bool solveBoard() {
            int curr_Row{};
            int curr_Col{};
            
            // Find next empty cell and update current row and column
            if (!findNextEmptyCell(curr_Row, curr_Col))
                return true;
            
            // Iterate over all possible cell values 
            for (int value{1}; value <= boardSize; ++value) {
                char charVal = '0' + value;
                //Verify validMove for current value
                if (isValidMove(curr_Col, curr_Row, charVal)) {
                    // Updating cell in board and recursively calling solveBoard
                    Board[curr_Row][curr_Col] = charVal;
                    if (solveBoard())
                        return true;
                    //If code is reached the assumed value was wrong and should be reset
                    Board[curr_Row][curr_Col] = '0';
                };
            };
            return false;
        };
};

int main() {
    Sudoku mySudoku{};
    mySudoku.solveBoard();
    mySudoku.print_Board();
    return 0;
};