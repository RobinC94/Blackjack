#pragma once

class BlackJack {
private:
    bool cardState[52];
    int cardNum = 52;
    double score1, score2;
    int cardCount1, cardCount2;

public:
    BlackJack() { freshGame(); }

    static void instructions();

    bool playerStage();

    bool computerStage();

    int judgeWinner() const;

private:
    void freshCard();

    void freshGame();

    void displayCard(int card) const;

    void recordSore(int card, double &score);

    int drawCard();
};
