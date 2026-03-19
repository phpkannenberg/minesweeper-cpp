#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

class Board;

enum class Content { Empty, Mine };
enum class Status { Hidden, Seen, Marked };

class Cell
{
friend class Board;
public:
    Cell(): content(Content::Empty), status(Status::Hidden) { };
private:
    Content content;
    Status status;
};

#endif
