// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread-main.cpp
// PROGRAM PURPOSE :
//     Contains solution to the river crossing problem.
//     Takes input from the command line, sets up environment,
//     creates threads and monitor.
// -----------------------------------------------------------

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "thread.h"
#include "boat-monitor.h"

using namespace std;

// -----------------------------------------------------------
// FUNCTION printWrap :
//    A wrapper method for printing using write()
// PARAMETER USAGE :
//    buf - A character array of size 100 containing
//          the print statement
// FUNCTION CALLED :
//    write()
// -----------------------------------------------------------
void printWrap(char buf[100]) {
    write(1, buf, strlen(buf));
}

// -----------------------------------------------------------
// FUNCTION main :
//    Sets up and starts the river crossing problem. The
//    problem being that a boat crosses a river with 3
//    passengers, 3 cannibals, 3 missionaries, or 1 cannibal
//    and 2 missionaries. 2 cannibals and 1 missionary is
//    NOT allowed.
// PARAMETER USAGE :
//    argv[1] - The number of cannibals
//    argv[2] - The number of missionaries
//    argv[3] - The number of boat loads
// FUNCTION CALLED :
//    BoatThread
//    Missionary
//    Cannibal
//    Begin
//    Join
// -----------------------------------------------------------
int main(int argc, char* argv[])
{
    int m = 0;
    char buf[100];

    // Default values for inputs
    int numCans  = 8;
    int numMiss  = 8;
    int numLoads = 5;

    if (atoi(argv[1]) != 0)
    {
        numCans = atoi(argv[1]);
    }
    if (atoi(argv[2]) != 0)
    {
        numMiss = atoi(argv[2]);
    }
    if (atoi(argv[3]) != 0)
    {
        numLoads = atoi(argv[3]);
    }

    sprintf(buf, "val: %d\n", numCans);
    printWrap(buf);
    sprintf(buf, "val: %d\n", numMiss);
    printWrap(buf);
    sprintf(buf, "val: %d\n", numLoads);
    printWrap(buf);

    printf("Starting crossing\n");

    // start boat thread
    BoatThread *boatT = new BoatThread(numLoads);
    boatT->Begin();

    // Start all cannibal threads
    Cannibal *cannibals[numCans];
    for (m = 1; m <= numCans; m++)
    {
        cannibals[m] = new Cannibal(m);
        cannibals[m]->Begin();
    }

    // Start all missionary threads
    Missionary *missionaries[numMiss];
    for (m = 1; m <= numMiss; m++)
    {
        missionaries[m] = new Missionary(m);
        missionaries[m]->Begin();
    }

    // wait for all child threads to finish
    boatT->Join();
    for (m = 1; m <= numCans; m++)
    {
        cannibals[m]->Join();
    }
    for (m = 1; m <= numMiss; m++)
    {
        missionaries[m]->Join();
    }



    return 0;
}
