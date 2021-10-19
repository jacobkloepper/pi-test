#include <iostream>
#include <vector>
#include <set>

int get_block(unsigned int row, unsigned int col) {
    if (row > 8 || col > 8) {
        std::cout << "error invalid (row,col): (" << row << "," << col << ")" << std::endl;
        return -1;
    }
    // intentional integer division for flooring
    return 3*(row/3) + (col/3);
}

void print_row(std::vector<std::vector<char>>& board, unsigned int row) {
    for (char cell : board.at(row)) {
        if (cell != '.') {
            std::cout << "[" << cell << "] ";
        }
    }
    std::cout << std::endl;
    return;
}

void print_col(std::vector<std::vector<char>>& board, unsigned int col) {
    for (auto row : board) {
        if (row.at(col) != '.') {
            std::cout << "[" << row.at(col) << "] ";
        }
    }
    std::cout << std::endl;
    return;
}

void print_block(std::vector<std::vector<char>>& board, unsigned int blk) {
    // offset to the critical (top left) cell in each block.
    unsigned int row_offset {3*(blk/3)};
    unsigned int col_offset {3*(blk%3)};
    std::cout << "Critical cell: (" << row_offset << "," << col_offset << ")" << std::endl;
    
    for (unsigned int row {0}; row < 3; row++) {
        for (unsigned int col {0}; col < 3; col++) {
            if (board.at(row_offset+row).at(col_offset+col) != '.') {
                std::cout << "[" << board.at(row_offset+row).at(col_offset+col) << "] ";
            }
        }
    }
    std::cout << std::endl;
    return;
}

//TODO: implement following 3 functions
bool check_row(std::vector<std::vector<char>>& board, unsigned int row) {
    std::set<char> buf {};
    for (char cell : board.at(row)) {
        if (cell != '.') {
            if (!buf.insert(cell).second) {
                return false;
            }
        }
    }
    return true;
}

bool check_col(std::vector<std::vector<char>>& board, unsigned int col) {
    std::set<char> buf {};
    for (auto row : board) {
        if (row.at(col) != '.') {
            if (!buf.insert(row.at(col)).second) {
                return false;
            }
        }
    }
    return true;
}

bool check_block(std::vector<std::vector<char>>& board, unsigned int blk) {
    // offset to the critical (top left) cell in each block.
    unsigned int row_offset {3*(blk/3)};
    unsigned int col_offset {3*(blk%3)};
    std::set<char> buf {};
    
    for (unsigned int row {0}; row < 3; row++) {
        for (unsigned int col {0}; col < 3; col++) {
            if (board.at(row_offset+row).at(col_offset+col) != '.') {
                if (!buf.insert(board.at(row_offset+row).at(col_offset+col)).second) {
                    return false;
                }
            }
        }
    }
    return true;
}


bool valid_board(std::vector<std::vector<char>> board) {
    for (unsigned int row {0}; row < 9; row++) {
        for (unsigned int col {0}; col < 9; col++) {
            if (board.at(row).at(col) != '.') {
                if (!check_row(board, row) || !check_col(board, col) || !check_block(board, get_block(row,col))) {
                    return false;
                }
            }
        }
    }
    return true;
}


int main() {
    std::vector<std::vector<char>> board = {    
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}
    };
    
    if (valid_board(board)) {
        std::cout << "VALID" << std::endl;
    } else {
        std::cout << "INVALID" << std::endl;
    }


    return 0;
}

