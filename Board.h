#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include <cstdlib>
#include <vector>
#include "Cell.h"

class Game;
enum class GameStatus;

class Board
{
public:
    Board(std::size_t h = 10, std::size_t w = 10);
    void print();
    const GameStatus reveal_cell(const std::size_t& row, const std::size_t& col);
    void toggle_flag(const std::size_t& row, const std::size_t& col);
    const bool within_range(const std::size_t row, const std::size_t col)
        { return (row < height) && (col < width); }
    bool fully_revealed() { return (width * height) - n_bombs == revealed_cells; }
private:
    const std::size_t width;
    const std::size_t height;
    const std::size_t n_bombs;
    std::size_t revealed_cells = 0;
    std::vector<Cell> board;
};

#endif
