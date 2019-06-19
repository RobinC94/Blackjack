#include<iostream>
#include "BlackJack.h"
/*
void computer_state()                                           //电脑游戏阶段
{   cout << "电脑阶段";
    int a[20], b[20], i, j;                                     //定义数组产生随机数决定卡牌
    string judge;
    srand(time(NULL));

    a[0] = rand() % 4, b[0] = rand() % 13;                      //产生两张不同卡牌
    do {a[1] = rand() % 4, b[1] = rand() % 13;
    } while (a[0] == a[1] && b[0] == b[1]);

    sum2 = record_grade(b[0], sum2);                            //统计得分
    sum2 = record_grade(b[1], sum2);

    cout << '\n' << "电脑获得牌" << '\t';
    output_card(a[0], b[0]);                                    //输出卡牌
    output_card(a[1], b[1]);

    while (sum2 < sum1){                                        //当得分低于玩家时继续抽牌
        do {a[c2] = rand() % 4, b[c2] = rand() % 13;            //产生卡牌并检测与之前的卡牌是否相同
            j = 0;
            for (i = 0; i < c2; ++i){
                while (a[c2] == a[i] && b[c2] == b[i]) ++j;
            }
        } while (j != 0);

        cout << '\n' << "电脑获得牌" << '\t';
        output_card(a[c2],b[c2]);                               //输出卡牌
        sum2 = record_grade(b[c2], sum2);                       //统计得分
        ++c2;                                                   //统计卡牌数

        if (sum2 >= 21) break;                                  //点数过大时游戏结束
    }

    if (sum2 > 21) {                                            //点数过大时玩家胜利
        cout << '\n' << "玩家赢了" << endl;
    }
    else if (sum2 == sum1) {                                    //点数相等时比较卡牌数
        if (c1 > c2) cout << '\n' << "玩家赢了" << endl;
        else if (c1 < c2) cout << '\n' << "玩家输了" << endl;
        else if (c1 == c2) cout << '\n' << "平局" << endl;
    }
    else cout << '\n' << "玩家输了" << endl;                    //除此之外电脑胜利
}*/

int main()                                                      //主函数
{
    BlackJack::instructions();
    std::string state;
    do {
        BlackJack game;
        if (!game.playerStage()) {
            std::cout << "玩家输了" << std::endl;
        } else {
            if (game.computerStage()){
                switch (game.judgeWinner()){
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
            }
            else {
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
