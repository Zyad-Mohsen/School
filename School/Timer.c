#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

clock_t startTime, endTime;

void startTimer(void)
{
    startTime = clock();
}

void stopTimer(void)
{
    endTime = clock();
}

void getElapsedTime(void)
{
    double elapsedTime=(double)(endTime - startTime)/CLOCKS_PER_SEC;
    int minutes = (int)(elapsedTime/60);
    int seconds = (int)elapsedTime % 60;
    printf(COLOR_GREEN"TIME TAKEN: %02d:%02d\n\n"COLOR_RESET,minutes,seconds);

}
