#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include "Cell.h"

class Board
{
friend void print_board(std::ostream&, const Board&);
public:
    Board(std::size_t h = 10, std::size_t w = 10);
    void print(std::ostream& os);
private:
    const std::size_t width;
    const std::size_t height;
    const std::size_t n_bombs;
    std::vector<Cell> board;
};

#endif
