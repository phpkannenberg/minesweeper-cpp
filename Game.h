#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include <cstdlib>
#include "Board.h"

enum class GameStatus { InProgress, Won, Lost };
enum PlayerAction { Reveal, ToggleFlag };

class Game
{
public:
    Game() : board(), status(GameStatus::InProgress) { };
    void play();
private:
    Board board;
    GameStatus status;
    void read_action(PlayerAction& action, std::size_t& row, std::size_t& col);
    void perform_action(const PlayerAction& action, const std::size_t row, const std::size_t col);
};

#endif
