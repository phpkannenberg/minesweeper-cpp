#include "Board.h"
#include "Cell.h"
#include <random>
#include <cstdlib>

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
        if (board[idx].content == Content::Empty)
        {
            board[idx].content = Content::Mine;
            ++bombs_placed;
        }
    }
}

void Board::print(std::ostream& os)
{
    // print header
    os << "   ";
    for (std::size_t col = 0; col < width; ++col)
        os << col << " ";
    os << '\n';
    os << "  ";
    for (std::size_t col = 0; col < width; ++col)
        os << "__";
    os << "_\n";

    // print rows
    for (std::size_t row = 0; row < height; ++row)
    {
        char curr_row = 'A' + row;
        os << curr_row << "| ";
        for (std::size_t col = 0; col < width; ++col)
        {
            const Cell &c = board[row * width + col];
            os << (c.content == Content::Empty ? "_" : "*") << " ";
        }
        os << "|\n";
    }
    
    // print last line
    os << "  ";
    for (std::size_t col = 0; col < width; ++col)
        os << "\u203E\u203E";
    os << "\u203E\n";
}
