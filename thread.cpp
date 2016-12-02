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

BoatThread::BoatThread()
{

}

void Cannibal::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay();
        Boat->CannibalArrives(canNum);
    }
}

void Missionary::ThreadFunc()
{
    Thread::ThreadFunc();

    /*while(1)
    {
        Delay();
        Boat->MissionaryArrives(missNum);
    }*/
}

void BoatThread::ThreadFunc()
{
    Thread::ThreadFunc();

    while(1)
    {
        Delay();
        Boat->BoatReady();
        Delay();
        Boat->BoatDone();
    }
}
