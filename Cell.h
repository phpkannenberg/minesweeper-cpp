#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

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
private:
    CellContent content;
    CellStatus status;
};

#endif
