#include <iostream>
#include <random>
#include <string>
#include <chrono>
#include <thread>
#include "BlackJack.h"

void BlackJack::instructions() {
    std::cout << "------------欢迎来到21点游戏------------" << std::endl;
    std::cout << "游戏规则如下：" << std::endl;
    std::cout << "  1.本游戏共一副牌无大小王52张，为人机对战；" << std::endl;
    std::cout << "  2.首先由电脑随机派两张不同的牌给玩家，然后通过玩家自己判断再选择是否继续要牌，要牌输入y，否则输入n。"
              << "如果要，则继续随机派给玩家一张牌，若此时所有牌的点数之和大于21，则玩家输，"
              << "如果不是，则玩家可以继续选择要牌与否，如果不要牌则玩家阶段结束，轮到电脑，"
              << "电脑阶段与玩家阶段基本相同。若电脑点数超过21则玩家胜利，若未超过则结束后点数较大的一方胜利。"
              << "若点数相同，则取牌数量更多的一方胜利。若牌数也一样，则不分胜负。" << std::endl;
    std::cout << "  3.点数的计算方式为：不论花色（红桃，黑桃，梅花，方块），数字牌（2到10）按照数字算，A按照1来算，J，Q，K均算成0.5点。"
              << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void BlackJack::freshCard() {
    for (int i = 0; i < 52; ++i) {
        cardState[i] = true;
    }
    cardNum = 52;
}

void BlackJack::freshGame() {
    score1 = 0;
    score2 = 0;
    cardCount1 = 0;
    cardCount2 = 0;
    freshCard();
}

void BlackJack::displayCard(int card) const {
    switch (card / 13) {
        case 0:
            std::cout << "方片\t";
            break;
        case 1:
            std::cout << "梅花\t";
            break;
        case 2:
            std::cout << "红桃\t";
            break;
        case 3:
            std::cout << "黑桃\t";
            break;
    }

    switch (card % 13) {
        case 0:
            std::cout << "A\t";
            break;
        case 10:
            std::cout << "J\t";
            break;
        case 11:
            std::cout << "Q\t";
            break;
        case 12:
            std::cout << "K\t";
            break;
        default:
            std::cout << card % 13 + 1 << '\t';
    }
}

int BlackJack::drawCard() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 52);

    if (cardNum == 0) {
        freshCard();
    }

    int randomCard;

    do {
        randomCard = dist(mt);
    } while (!cardState[randomCard]);

    cardState[randomCard] = false;
    cardNum--;
    return randomCard;
}

void BlackJack::recordSore(int card, double &score) {
    int point = card % 13;
    if (point >= 10)
        score += 0.5;
    else
        score += ++point;
}

int BlackJack::judgeWinner() const {
    if (score1 > score2)
        return 1;
    if (score1 < score2)
        return 2;
    if (cardCount1 > cardCount2)
        return 1;
    if (cardCount1 < cardCount2)
        return 2;
    return 0;
}


bool BlackJack::playerStage() {
    std::cout << "玩家阶段" << std::endl;

    int card1, card2;
    std::string judge;

    while (true) {
        card1 = drawCard();
        card2 = drawCard();
        if (card1 != card2)
            break;
        else
            cardState[card1] = true;
    }

    std::cout << "玩家获得牌" << '\t';
    displayCard(card1);
    displayCard(card2);
    recordSore(card1, score1);
    recordSore(card2, score1);
    cardCount1 += 2;

    do {
        std::cout << std::endl << "是否继续要牌(y/n): ";
        std::cin >> judge;
        while (judge != "y" && judge != "n") {
            std::cout << "输入错误，请重新输入:";
            std::cin >> judge;
        }

        if (judge == "y") {
            card1 = drawCard();

            std::cout << "继续要一张牌" << '\t';
            displayCard(card1);
            recordSore(card1, score1);
            cardCount1++;
        }

        if (score1 > 21) {
            std::cout << "分数超过21!" << std::endl;
            return false;
        }

        if (judge == "n") {
            std::cout << "玩家分数:" << score1 << "\t玩家牌数:" << cardCount1 << std::endl;
            return true;
        }
    } while (judge == "y");
}

bool BlackJack::computerStage() {
    std::cout << "电脑阶段" << std::endl;

    int card1, card2;
    while (true) {
        card1 = drawCard();
        card2 = drawCard();
        if (card1 != card2)
            break;
        else
            cardState[card1] = true;
    }
    std::cout << "电脑获得牌" << '\t';
    displayCard(card1);
    displayCard(card2);
    recordSore(card1, score2);
    recordSore(card2, score2);
    cardCount2 += 2;

    while (score2 < score1 || (score2 == score1 && cardCount2 > cardCount1)) {
        card1 = drawCard();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << std::endl << "电脑获得牌" << '\t';
        displayCard(card1);
        recordSore(card1, score2);
        cardCount2++;

        if (score2 > 21) {
            std::cout << "分数超过21!" << std::endl;
            return false;
        }
    }

    std::cout << std::endl << "电脑分数:" << score2 << "\t电脑牌数:" << cardCount2 << std::endl;
    return true;
}