#include <cs50.h>
#include <stdio.h>
#include <assert.h>

void tests(void);
void bowlGameInit(void);
void bowlGameRoll(int pints);
int bowlGameScore(void);

int main(void)
{
    tests();
}

void rollMany(int rolls, int pins)
{
    for (int i = 0; i < rolls; i++)
    {
        bowlGameRoll(pins);
    }
}


void testGutterGame(void)
{
    bowlGameInit();
    rollMany(20, 0);
    assert(bowlGameScore() == 0 && "Gutter game should result in 0");
}

void testAllOnes(void)
{
    bowlGameInit();
    rollMany(20, 1);
    assert(bowlGameScore() == 20 && "All one game should result in 20");
}

void testOneSpare(void)
{
    bowlGameInit();
    bowlGameRoll(5);
    bowlGameRoll(5);
    bowlGameRoll(3);
    rollMany(17, 0);
    assert(bowlGameScore() == 16 && "One spare with 3 bonus should result in 16");
}

void testOneStrike()
{
    bowlGameInit();
    bowlGameRoll(10);
    bowlGameRoll(3);
    bowlGameRoll(4);
    rollMany(16, 0);
    assert(bowlGameScore() == 24 && "One strike with 3 and 4 should result in 24");
}

void testPerfectGame()
{
    bowlGameInit();
    rollMany(12, 10);
    assert(bowlGameScore() == 300 && "A perfect game is 300 points");
}

void testGiven()
{
    bowlGameInit();
    int bowlGame[21] = {1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 0, 1, 7, 3, 6, 4, 10, 0, 2, 8, 6};
    int frameIndex = 0;
    for (int frame = 0; frame < 10; frame++)
    {
        if (bowlGame[frameIndex] == 10)
        {
            bowlGameRoll(10);
            frameIndex += 2;
        }
        else
        {
            bowlGameRoll(bowlGame[frameIndex++]);
            bowlGameRoll(bowlGame[frameIndex++]);
        }
    }
    bowlGameRoll(bowlGame[frameIndex]);
    assert(bowlGameScore() == 133 && "given game");
}

void tests(void)
{
    testGutterGame();
    testAllOnes();
    testOneSpare();
    testOneStrike();
    testPerfectGame();
    testGiven();
}

int MAXROLLS = 21;
int rolls[21];
int currentRoll;

void bowlGameInit(void)
{
    for (int i = 0; i < MAXROLLS; i++)
    {
        rolls[i] = 0;
    }
    currentRoll = 0;
}

void bowlGameRoll(int pins)
{
    rolls[currentRoll++] = pins;
}

bool isSpare(int frameIndex)
{
    return rolls[frameIndex] + rolls[frameIndex + 1] == 10;
}

bool isStrike(int frameIndex)
{
    return rolls[frameIndex] == 10;
}

int bowlGameScore(void)
{
    int score = 0;
    int frameIndex = 0;
    for (int frame = 0; frame < 10; frame++)
    {
        if (isStrike(frameIndex))
        {
            score += 10 + rolls[frameIndex + 1] + rolls[frameIndex + 2];
            frameIndex += 1;
        }
        else if (isSpare(frameIndex))
        {
            score += 10 + rolls[frameIndex + 2];
            frameIndex += 2;
        }
        else
        {
            score += rolls[frameIndex] + rolls[frameIndex + 1];
            frameIndex += 2;
        }
    }
    return score;
}
