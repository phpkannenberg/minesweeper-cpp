#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

#include <cstdlib>
#include <string>

class Board;

enum class CellContent { Empty, Mine };
enum class CellStatus { Hidden, Revealed, Marked };

class Cell
{
public:
    Cell(): content(CellContent::Empty), status(CellStatus::Hidden) { };
    const CellContent get_content() const { return content; }
    void set_content(CellContent c) { content = c; }
    const CellStatus get_status() const { return status; }
    void set_status(CellStatus s) { status = s; }
    const std::string print() const;
    const std::size_t get_n_nearby_mines() const { return n_nearby_mines; } 
    void set_n_nearby_mines(std::size_t n) { n_nearby_mines = n; }
private:
    CellContent content;
    CellStatus status;
    std::size_t n_nearby_mines = 0;  // number of mines in nearby cells (including itself)
};

#endif
