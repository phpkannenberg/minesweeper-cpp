#include "Board.h"
#include "Cell.h"
#include "Game.h"
#include <random>
#include <cstdlib>
#include <iostream>
#include <queue>

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
    
    // set number of mines in the surroundings
    for (std::size_t i = 0; i < board.size(); ++i)
    {
        std::size_t n = count_nearby_mines(i);
        board[i].set_n_nearby_mines(n);
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
            std::cout << c.print() << " ";
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
    std::size_t idx = row * width + col;
    Cell &cell = board[idx];
    
    // cell was already previously revealed
    if (cell.get_status() == CellStatus::Revealed)
    {
        std::cout << "Cell already revealed.\n";
        return GameStatus::InProgress;
    }
    
    // cannot reveal a marked cell
    else if (cell.get_status() == CellStatus::Marked)
    {
        std::cout << "Cannot reveal a marked cell! Perform a \"toggle flag\" action first.\n";
        return GameStatus::InProgress;
    }
        
    // if there is no mine in the cell
    if (cell.get_content() == CellContent::Empty)
    {
        reveal_cell_bfs(idx);
        if (fully_revealed()) return GameStatus::Won;
        return GameStatus::InProgress;
    }
    // if there is a mine in the cell
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
            // cannot put a flag on a revealed cell
            std::cout << "Cell already revealed.\n";
            break;
      }
}

const std::size_t Board::count_nearby_mines(const std::size_t idx)
{
    std::size_t mine_count = 0;
    for (int i = -1; i <= 1; ++i)  // rows
    {
        int curr_row = (idx / width) + i;
        if (curr_row < 0 || curr_row >= height) continue;  // check if out of bounds
        for (int j = -1; j <= 1; ++j)  // columns
        {
            int curr_col = (idx % width) + j;
            if (curr_col < 0 || curr_col >= width) continue;  //check if out of bounds
            
            // execution gets here only if within bounds
            Cell &curr_cell = board[idx + (width * i) + j];
            if (curr_cell.get_content() == CellContent::Mine)
                ++mine_count;
        }
    }
    return mine_count;
}

void Board::reveal_cell_bfs(const std::size_t idx)
{
    std::queue<std::size_t> q;
    
    board[idx].set_status(CellStatus::Revealed);
    ++revealed_cells;
    q.push(idx);
    
    while (!q.empty())
    {
        auto curr_idx = q.front();
        q.pop();
        Cell &curr_cell = board[curr_idx];
        
        // only pushes neighbors of cells with no mines in the surrounding
        if (curr_cell.get_n_nearby_mines() == 0)
        {
            for (int i = -1; i <= 1; ++i)  // rows
            {
                int curr_row = (curr_idx / width) + i;
                if (curr_row < 0 || curr_row >= height) continue;  // check if out of bounds
                for (int j = -1; j <= 1; ++j)  // columns
                {
                    int curr_col = (curr_idx % width) + j;
                    if (curr_col < 0 || curr_col >= width) continue;  //check if out of bounds
                    
                    // execution gets here only if within bounds
                    std::size_t neighbor_idx = curr_idx + (width * i) + j;
                    Cell &neighbor_cell = board[neighbor_idx];
                    
                    if (neighbor_cell.get_status() == CellStatus::Hidden)
                    {
                        neighbor_cell.set_status(CellStatus::Revealed);
                        ++revealed_cells;
                        q.push(neighbor_idx);
                    }
                }
            }
        }
    }
}
