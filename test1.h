#ifndef TEST1_H
#define TEST1_H

#include <iostream>
#include <ctime>
#include <curses.h>
#include <unistd.h>
using namespace std;

class pomodoro {
protected:
    int min;
    float min1;
    int count;

public:
    pomodoro();
    pomodoro(int min);
    void timerP();
    float reTime();
    void timerB();
    string currentT();
};

void sPomo(int n, pomodoro p);
void startpomo();

#endif // TEST1_H