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
#include <string.h>
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

void BoatMonitor::BoatReady(int k)
{
    MonitorBegin();
    char buf[100];

    sprintf(buf, "***** The boat is ready\n");
    printWrap(buf);

    // let riders waiting get on board
    releaseThree(k);


    // if didn't fill the boat with people waiting,
    // let someone new come along
    if (onBoat < 3)
    {
        boatState = READY;
        BoatWaiting->Wait();
    }

    sprintf(buf, "***** Boat load(%d): Passenger list (%c%d, %c%d, %c%d)\n",
                    k, types[0], numbers[0], types[1], numbers[1], types[2],
                    numbers[2]);
    printWrap(buf);

    boatState = NOTREADY;

    MonitorEnd();
}

void BoatMonitor::BoatDone()
{
    MonitorBegin();

    int i;
    for (i = 0; i < 3; i++)
    {
        Riding->Signal();
    }

    MonitorEnd();
}

void BoatMonitor::CannibalArrives(int cNum)
{
    MonitorBegin();

    char space = ' ';
    char buf[100];

    sprintf(buf, "%*c Cannibal %d arrives\n", cNum - 1, space, cNum);
    printWrap(buf);

    if(!canBoard(CANNIBAL))
    {
        // Can't get on so wait
        waiting = waiting + 1;
        canWaiting = canWaiting + 1;
    //    printf("Cannibal %d is waiting to get on\n", cNum);
        CannibalHere->Wait();
        waiting = waiting - 1;
        canWaiting = canWaiting - 1;
    }
    // Can get on the boat
    onBoat = onBoat + 1;
    if (onBoat == 1)
    {
        types[0] = 'c';
        numbers[0] = cNum;
    }
    if (onBoat == 2)
    {
        types[1] = 'c';
        numbers[1] = cNum;

    }
    // if 3rd on boat, signal the boat to go
    if (onBoat == 3)
    {
        types[2] = 'c';
        numbers[2] = cNum;
        BoatWaiting->Signal();
    }
    Riding->Wait();
    onBoat = onBoat - 1;

    MonitorEnd();
}

void BoatMonitor::MissionaryArrives(int mNum)
{
    MonitorBegin();

    char space = ' ';
    char buf[100];

    sprintf(buf, "%*c Missionary %d arrives\n", mNum - 1, space, mNum);
    printWrap(buf);

    if(!canBoard(MISSIONARY))
    {
        // Can't get on so wait
        waiting = waiting + 1;
        missWaiting = missWaiting + 1;
      //  printf("Missionary %d is waiting to get on\n", mNum);
        MissionaryHere->Wait();
        missWaiting = missWaiting - 1;
        waiting = waiting - 1;
    }
    // Can get on the boat
    onBoat = onBoat + 1;
    if (onBoat == 1)
    {
        types[0] = 'm';
        numbers[0] = mNum;
    }
    if (onBoat == 2)
    {
        types[1] = 'm';
        numbers[1] = mNum;

    }
    // if 3rd on boat, signal the boat to go
    if (onBoat == 3)
    {
        types[2] = 'm';
        numbers[2] = mNum;
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

void BoatMonitor::releaseThree(int l)
{
    // create random sequence for checking
    int array[] = {0, 1, 2};
    char buf[100];
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
                sprintf(buf, "MONITOR(%d): two missionaries and"
                             " one cannibal are selected\n", l);
                printWrap(buf);
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
                 sprintf(buf, "MONITOR(%d): 3 missionaries"
                              " are selected\n", l);
                 printWrap(buf);
                 return;
             }
        }
        else if (array[i] == 2)
        {
            if (canWaiting > 2) {
                CannibalHere->Signal();
                CannibalHere->Signal();
                CannibalHere->Signal();
                sprintf(buf, "MONITOR(%d): 3 cannibals"
                             " are selected\n", l);
                printWrap(buf);
                return;
            }
        }
    }
    return;
}

void BoatMonitor::printWrap(char buf[100])
{
    write(1, buf, strlen(buf));
}
