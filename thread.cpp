// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
//     Contains implementations of the missionary and cannibal
//     thread classes.
// -----------------------------------------------------------

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "thread.h"
#include "boat-monitor.h"

static BoatMonitor * Boat = new BoatMonitor(3);

Cannibal::Cannibal(int cNum)
{
    canNum = cNum;
}

Missionary::Missionary(int mNum)
{
    missNum = mNum;
}

BoatThread::BoatThread(int b)
{
    loads = b;
}

void Cannibal::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        r = rand() % 15;
        for (j = 0; j < r; j++)
        {
            Delay();
        }
        Boat->CannibalArrives(canNum);
    }
}

void Missionary::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        r = rand() % 15;
        for (j = 0; j < r; j++)
        {
            Delay();
        }
        Boat->MissionaryArrives(missNum);
    }
}

void BoatThread::ThreadFunc()
{
    Thread::ThreadFunc();

    for (k = 1; k <= loads; k++)
    {
        printf("Boat load #%d\n", k);
        Delay();
        Boat->BoatReady();
        Delay();
        Boat->BoatDone();
    }
    printf("Boat finished running\n");
    exit(0);
}
