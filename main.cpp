#include <iostream>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"

void intro()
{
    std::cout << "============\n";
    std::cout << "Filip 258950\n";
    std::cout << "============\n\n";
}

int main() {
        intro();

        MinesweeperBoard board (20, 10, GameMode::EASY);
        MSBoardTextView view ( board );
        board.debug_display(board);
        MSTextController ctrl (view,board);


        while(board.getGameState() != FINISHED_LOSS){
            ctrl.play();
            if(board.getGameState() == FINISHED_WIN){
                std::cout << "Congrats you win!" << std::endl;
            }
        }

    return 0;
}
