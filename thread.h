// -----------------------------------------------------------
// NAME : Zachary Hill                         User ID: zahill
// DUE DATE : 12/02/2016
// PROGRAM ASSIGNMENT #5
// FILE NAME : thread.h
// PROGRAM PURPOSE :
//     Contains definitions of missionary and cannibal
//     classes.
// -----------------------------------------------------------

#include "ThreadClass.h"

class Cannibal : public Thread
{
    public:
        Cannibal(int cNum);

    private:
        int canNum;
        char buf[100];
        void ThreadFunc();
        void printWrap(char*);

};

class Missionary : public Thread
{
    public:
        Missionary(int mNum);

    private:
        int missNum;
        char buf[100];
        void ThreadFunc();
        void printWrap(char*);

};

class BoatThread : public Thread
{
    public:
        BoatThread();

    private:
        char buf[100];
        void ThreadFunc();
        void printWrap(char*);

};
