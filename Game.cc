#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <limits>

void Game::play()
{
    while (status == GameStatus::InProgress)
    {
        board.print();
        
        PlayerAction action;
        std::size_t row, col;
        read_action(action, row, col);
        perform_action(action, row, col);
                
        if (status == GameStatus::Lost)
        {
            board.print();
            std::cout << "Oops, there was a bomb in there. GAME OVER!\n";
        }
        else if (status == GameStatus::Won)
        {
            board.print();
            std::cout << "Congratulations! YOU WON!\n";
        }
    }
}

void Game::read_action(PlayerAction& action, std::size_t& row, std::size_t& col)
{
    while (true)
    {
        std::cout << "\nEnter action: [r/t] [row] [col] ";
        
        char act, char_r;
        std::size_t c;
        if (!(std::cin >> act >> char_r >> c))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input format! Use \"[r/t] [row] [col]\".\n";
            continue;
        }
        
        if (act == 'r') action = PlayerAction::Reveal;
        else if (act == 't') action = PlayerAction::ToggleFlag;
        else 
        {
            std::cout << "Invalid input format! Use 'r' (reveal) or 't' (toggle flag) "
                          "followed by row and column numbers.\n";
            continue;
        }
        
        std::size_t r = char_r - 'a';
        if (!board.within_range(r, c)) 
        {
            std::cout << "Invalid input format! Row/column out of range.\n";
            continue;
        }
        row = r;
        col = c;
        
        break;
    }
}

void Game::perform_action(const PlayerAction& action, const std::size_t row, const std::size_t col)
{
    if (action == PlayerAction::Reveal) 
        status = board.reveal_cell(row, col);
    else if (action == PlayerAction::ToggleFlag) 
        board.toggle_flag(row, col);
}
