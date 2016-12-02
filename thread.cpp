// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.cpp
// PROGRAM PURPOSE :
//     Contains implementations of the boat, missionary,
//     and cannibal thread classes.
// -----------------------------------------------------------

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "thread.h"
#include "boat-monitor.h"

static BoatMonitor * Boat = new BoatMonitor(3);

// -----------------------------------------------------------
// FUNCTION Cannibal::Cannibal :
//    Constructor for the cannibal thread
// PARAMETER USAGE :
//    mNum - ID of the cannibal
// FUNCTION CALLED :
//    NA
// -----------------------------------------------------------
Cannibal::Cannibal(int cNum)
{
    canNum = cNum;
}

// -----------------------------------------------------------
// FUNCTION Missionary::Missionary :
//    Constructor for the Missionary thread
// PARAMETER USAGE :
//    mNum - ID of the missionary
// FUNCTION CALLED :
//    NA
// -----------------------------------------------------------
Missionary::Missionary(int mNum)
{
    missNum = mNum;
}

// -----------------------------------------------------------
// FUNCTION BoatThread::BoatThread :
//    Constructor for the BoatThread thread
// PARAMETER USAGE :
//    b - the number of loads to be completed
// FUNCTION CALLED :
//    NA
// -----------------------------------------------------------
BoatThread::BoatThread(int b)
{
    loads = b;
}

// -----------------------------------------------------------
// FUNCTION Cannibal::ThreadFunc :
//    Contains functionality for the cannibal thread
// PARAMETER USAGE :
//    NA
// FUNCTION CALLED :
//    Delay
//    CannibalArrives
// -----------------------------------------------------------
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

// -----------------------------------------------------------
// FUNCTION Missionary::ThreadFunc :
//    Contains functionality for the missionary thread
// PARAMETER USAGE :
//    NA
// FUNCTION CALLED :
//    Delay
//    MissionaryArrives
// -----------------------------------------------------------
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

// -----------------------------------------------------------
// FUNCTION BoatThread::ThreadFunc :
//    Contains functionality for the boat thread
// PARAMETER USAGE :
//    NA
// FUNCTION CALLED :
//    Delay
//    BoatReady
//    BoatDone
// -----------------------------------------------------------
void BoatThread::ThreadFunc()
{
    Thread::ThreadFunc();

    for (k = 1; k <= loads; k++)
    {

        Delay();
        Boat->BoatReady(k);
        Delay();
        Boat->BoatDone();
        sprintf(buf, "***** Boat load (%d): Completed\n", k);
        printWrap(buf);
    }
    sprintf(buf, "MONITOR: %d crosses have been made.\n", loads);
    printWrap(buf);
    sprintf(buf, "MONITOR: This river cross is closed indefinitely"
                 " for renovation.\n");
    printWrap(buf);
    exit(0);
}

// -----------------------------------------------------------
// FUNCTION BoatThread::printWrap :
//    A wrapper method for printing using write()
// PARAMETER USAGE :
//    buf - A character array of size 100 containing
//          the print statement
// FUNCTION CALLED :
//    write()
// -----------------------------------------------------------
void BoatThread::printWrap(char buf[100])
{
    write(1, buf, strlen(buf));
}
