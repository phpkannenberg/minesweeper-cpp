#include "Cell.h"
#include <cstdlib>

const char Cell::print() const
{
    char c;
    switch (status)
    {
        case CellStatus::Hidden:
            c = '-';
            break;
        case CellStatus::Marked:
            c = 'X';
            break;
        case CellStatus::Revealed:
            switch (content)
            {
                case CellContent::Mine:
                    c = '*';
                    break;
                case CellContent::Empty:
                    c = '0' + n_nearby_mines;
                    break;
            }
            break;
    }
    return c;
}
