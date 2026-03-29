#include "Board.h"
#include "Cell.h"
#include "Game.h"
#include <random>
#include <cstdlib>
#include <iostream>

Board::Board(std::size_t h, std::size_t w):
    height(h), width(w), n_bombs((h * w) / 8), board(h * w)
{
    // place mines on random cells
    std::random_device rd;
    std::uniform_int_distribution<std::size_t> uid(0, board.size() - 1);
    std::size_t bombs_placed = 0;
    while (bombs_placed != n_bombs)
    {
        std::size_t idx = uid(rd);
        if (board[idx].get_content() == CellContent::Empty)
        {
            board[idx].set_content(CellContent::Mine);
            ++bombs_placed;
        }
    }
}

void Board::print()
{
    // print header
    std::cout << "\n    ";
    for (std::size_t col = 0; col < width; ++col)
        std::cout << col << " ";
    std::cout << '\n';
    std::cout << "   ";
    for (std::size_t col = 0; col < width; ++col)
        std::cout << "__";
    std::cout << "_\n";

    // print rows
    for (std::size_t row = 0; row < height; ++row)
    {
        char curr_row = 'a' + row;
        std::cout << curr_row << " | ";
        for (std::size_t col = 0; col < width; ++col)
        {
            const Cell &c = board[row * width + col];
            std::cout << (c.get_content() == CellContent::Empty ? "-" : "*") << " ";
        }
        std::cout << "|\n";
    }
    
    // print last line (overline characters)
    std::cout << "   ";
    for (std::size_t col = 0; col < width; ++col)
        std::cout << "\u203E\u203E";
    std::cout << "\u203E\n";
}

const GameStatus Board::reveal_cell(const std::size_t& row, const std::size_t& col)
{
    Cell &cell = board[row * width + col];
    
    if (cell.get_status() == CellStatus::Revealed)
    {
        std::cout << "Cell already revealed.\n";
        return GameStatus::InProgress;
    }
    
    cell.set_status(CellStatus::Revealed);
    
    if (cell.get_content() == CellContent::Empty)
    {
        ++revealed_cells;
        if (fully_revealed()) return GameStatus::Won;
        return GameStatus::InProgress;
    }
    return GameStatus::Lost;
}

void Board::toggle_flag(const std::size_t& row, const std::size_t& col)
{
    Cell &cell = board[row * width + col];
    
    switch (cell.get_status())
    {
        case CellStatus::Hidden:
            cell.set_status(CellStatus::Marked);
            break;
        case CellStatus::Marked:
            cell.set_status(CellStatus::Hidden);
            break;
        case CellStatus::Revealed:
            std::cout << "Cell already revealed.\n";
            break;
      }
}
