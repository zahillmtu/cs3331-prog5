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
#include <stdlib.h>
#include <time.h>
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
    canWaiting = 0;
    missWaiting = 0;
    onBoat = 0;
    boatState = NOTREADY;

    Riding = new Condition("riding");
    CannibalHere = new Condition("cWait");
    MissionaryHere = new Condition("mWait");
    BoatWaiting = new Condition("bWait");
    BoatLoading = new Condition("bLoad");
    srand( time(NULL));
}

void BoatMonitor::BoatReady()
{
    MonitorBegin();


    printf("Boat is ready for loading\n");

    // let riders waiting get on board
    releaseThree();

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
        canWaiting = canWaiting + 1;
        printf("Cannibal %d is waiting to get on\n", cNum);
        CannibalHere->Wait();
        waiting = waiting - 1;
        canWaiting = canWaiting - 1;
    }
    // Can get on the boat
    onBoat = onBoat + 1;
    printf("\tCannibal %d is on the boat\n", cNum);
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

    if(!canBoard(MISSIONARY))
    {
        // Can't get on so wait
        waiting = waiting + 1;
        missWaiting = missWaiting + 1;
        printf("Missionary %d is waiting to get on\n", mNum);
        MissionaryHere->Wait();
        missWaiting = missWaiting - 1;
        waiting = waiting - 1;
    }
    // Can get on the boat
    onBoat = onBoat + 1;
    printf("\tMissionary %d is on the boat\n", mNum);
    // if 3rd on boat, signal the boat to go
    if (onBoat == 3)
    {
        printf("Missionary %d is 3rd to get on\n", mNum);
        BoatWaiting->Signal();
    }
    Riding->Wait();
    onBoat = onBoat - 1;

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

void BoatMonitor::releaseThree()
{
    // create random sequence for checking
    int array[] = {0, 1, 2};
    int k;
    for (k = 0; k < 3; k++)
    {
        int temp = array[k];
        int randIndex = rand() % 3;

        array[k] = array[randIndex];
        array[randIndex] = temp;
    }

    int i;
    for (i = 0; i < 3; i++)
    {
        if (array[i] == 0)
        {
            if (canWaiting > 0 && missWaiting > 1)
            {
                MissionaryHere->Signal();
                MissionaryHere->Signal();
                CannibalHere->Signal();
                return;
            }
        }
        else if (array[i] == 1)
        {
             if (missWaiting > 2)
             {
                 MissionaryHere->Signal();
                 MissionaryHere->Signal();
                 MissionaryHere->Signal();
                 return;
             }
        }
        else if (array[i] == 2)
        {
            if (canWaiting > 2) {
                CannibalHere->Signal();
                CannibalHere->Signal();
                CannibalHere->Signal();
                return;
            }
        }
    }
    return;
}
