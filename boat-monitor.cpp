// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : boat-monitor.cpp
// PROGRAM PURPOSE :
//     Contains implementation of boat-monitor class,
//     functionality for the boat in the River Crossing prob
// -----------------------------------------------------------


#include <iostream>
#include <stdio.h>
#include "thread.h"
#include "boat-monitor.h"

#define CANNIBAL   1
#define MISSIONARY 0
#define READY      1
#define NOTREADY   0

BoatMonitor::BoatMonitor(int k)
      : Monitor("Boat", HOARE)
{
    boatLoads = k;
    waiting = 0;
    onBoat = 0;
    boatState = NOTREADY;

    Riding = new Condition("riding");
    CannibalHere = new Condition("cWait");
    BoatWaiting = new Condition("bWait");
    BoatLoading = new Condition("bLoad");
}

void BoatMonitor::BoatReady()
{
    MonitorBegin();


    printf("Boat is ready for loading\n");

    // Signal Cannibals to get on
    int i;
    for (i = 0; i < 3; i++)
    {
        CannibalHere->Signal();
    }

    // if didn't fill the boat with people waiting,
    // let someone new come along
    if (onBoat < 3)
    {
        printf("waiting for someone to get on\n");
        boatState = READY;
        BoatWaiting->Wait();
    }

    boatState = NOTREADY;
    printf("Boat going\n");

    MonitorEnd();
}

void BoatMonitor::BoatDone()
{
    MonitorBegin();

    int i;
    printf("Ride done, releasing riders\n");
    for (i = 0; i < 3; i++)
    {
        Riding->Signal();
    }

    MonitorEnd();
}

void BoatMonitor::CannibalArrives(int cNum)
{
    MonitorBegin();

    if(!canBoard(CANNIBAL))
    {
        // Can't get on so wait
        waiting = waiting + 1;
        printf("Cannibal %d is waiting to get on\n", cNum);
        CannibalHere->Wait();
        waiting = waiting - 1;
    }
    // Can get on the boat
    onBoat = onBoat + 1;
    printf("Cannibal %d is on the boat\n", cNum);
    // if 3rd on boat, signal the boat to go
    if (onBoat == 3)
    {
        printf("Cannibal %d is 3rd to get on\n", cNum);
        BoatWaiting->Signal();
    }
    Riding->Wait();
    onBoat = onBoat - 1;

    MonitorEnd();
}

void BoatMonitor::MissionaryArrives(int mNum)
{
    MonitorBegin();

    MonitorEnd();
}

int BoatMonitor::canBoard(int type)
{
    if (onBoat < 3 && boatState == READY)
    {
        // you can board
        return 1;
    }
    else
    {
        return 0;
    }
}

