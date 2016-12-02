// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : boat-monitor.h
// PROGRAM PURPOSE :
//     Contains definitions for the boat-monitor class
// -----------------------------------------------------------

#include "ThreadClass.h"

class BoatMonitor : public Monitor
{
    public:
        BoatMonitor(int k);

        void BoatReady();
        void BoatDone();
        void CannibalArrives(int cNum);
        void MissionaryArrives(int mNum);

    private:
        Condition *Riding;
        Condition *CannibalHere;
        Condition *MissionaryHere;
        Condition *BoatLoading;
        Condition *BoatWaiting;
        int boatLoads;
        int waiting;
        int onBoat;
        int boatState;
        int canWaiting;
        int missWaiting;
        char buf[100];
        void ThreadFunc();
        void printWrap(char*);
        int canBoard(int type);
        void releaseThree();
};
