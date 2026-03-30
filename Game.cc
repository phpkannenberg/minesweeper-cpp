#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <limits>

void Game::play()
{
    while (status == GameStatus::InProgress)
    {
        // print board
        board.print();
        
        // read and perform action
        PlayerAction action;
        std::size_t row, col;
        read_action(action, row, col);
        perform_action(action, row, col);
                    
        // analyze if game ended after last action
        if (status == GameStatus::Lost)
        {
            board.reveal_all_cells();
            board.print();
            std::cout << "OOPS, there was a bomb in there. GAME OVER!\n";
        }
        else if (status == GameStatus::Won)
        {
            board.reveal_all_cells();
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
        
        // check if input is valid (number and types)
        if (!(std::cin >> act >> char_r >> c))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input format! Use \"[r/t] [row] [col]\".\n";
            continue;
        }
        
        // set action to be taken (asks for another input if wrong format)
        if (act == 'r') action = PlayerAction::Reveal;
        else if (act == 't') action = PlayerAction::ToggleFlag;
        else 
        {
            std::cout << "Invalid input format! Use 'r' (reveal) or 't' (toggle flag) "
                          "followed by row and column numbers.\n";
            continue;
        }
        
        // set cell row and column (asks for another input if row/col out of bounds)
        std::size_t r = char_r - 'a';
        if (!board.within_range(r, c)) 
        {
            std::cout << "Invalid input format! Row/column out of bounds.\n";
            continue;
        }
        row = r;
        col = c;
        
        // end loop if no problems occurred
        break;
    }
}

void Game::perform_action(const PlayerAction& action, const std::size_t row, const std::size_t col)
{
    if (action == PlayerAction::Reveal)
        status = board.reveal_cell(row, col);  // changes game status according to cell content
    else if (action == PlayerAction::ToggleFlag) 
        board.toggle_flag(row, col);
}
