#include<iostream>
#include "BlackJack.h"

int main()                                                      //主函数
{
    BlackJack::instructions();
    std::string state;
    do {
        BlackJack game;
        if (!game.playerStage()) {
            std::cout << "玩家输了" << std::endl;
        } else {
            if (game.computerStage()) {
                switch (game.judgeWinner()) {
                    case 1:
                        std::cout << "玩家赢了!";
                        break;
                    case 2:
                        std::cout << "玩家输了!";
                        break;
                    case 0:
                        std::cout << "平局!";
                        break;
                }
                std::cout << std::endl;
            } else {
                std::cout << "玩家赢了!";
            }
        }
        std::cout << std::endl << "按y继续游戏, 其他键退出:";
        std::cin >> state;
    } while (state == "y");

    std::cout << "--------------------------------------" << std::endl;
    std::cout << "感谢游玩！     ————Robin CHEN" << std::endl;

    return 0;
}
