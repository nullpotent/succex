#pragma once
//------------------------------------------------------------------------
//
//  Name:   Regulator.h
//
//  Desc:   Use this class to regulate code flow (for an update function say)
//          Instantiate the class with the frequency you would like your code
//          section to flow (like 10 times per second) and then only allow
//          the program flow to continue if Ready() returns true
//
//------------------------------------------------------------------------
//#pragma comment(lib,"winmm.lib") //if you don't use MSVC make sure this library is included in your project

#include "mmsystem.h"
#include "../Utils.h"


class Regulator
{
private:

    //the time period between updates
    double updatePeriod_;

    //the next time the regulator allows code flow
    DWORD nextUpdateTime_;


public:


    Regulator(double NumUpdatesPerSecondRqd)
    {
        nextUpdateTime_ = (DWORD)(timeGetTime()+RandFloat()*1000);

        if (NumUpdatesPerSecondRqd > 0)
        {
            updatePeriod_ = 1000.0 / NumUpdatesPerSecondRqd;
        }

        else if (IsEqual(0.0, NumUpdatesPerSecondRqd))
        {
            updatePeriod_ = 0.0;
        }

        else if (NumUpdatesPerSecondRqd < 0)
        {
            updatePeriod_ = -1;
        }
    }


    //returns true if the current time exceeds nextUpdateTime_
    bool IsReady()
    {
        //if a regulator is instantiated with a zero freq then it goes into
        //stealth mode (doesn't regulate)
        if (IsEqual(0.0, updatePeriod_)) return true;

        //if the regulator is instantiated with a negative freq then it will
        //never allow the code to flow
        if (updatePeriod_ < 0) return false;

        DWORD CurrentTime = timeGetTime();

        //the number of milliseconds the update period can vary per required
        //update-step. This is here to make sure any multiple clients of this class
        //have their updates spread evenly
        static const double UpdatePeriodVariator = 10.0;

        if (CurrentTime >= nextUpdateTime_)
        {
            nextUpdateTime_ = (DWORD)(CurrentTime + updatePeriod_ + RandInRange(-UpdatePeriodVariator, UpdatePeriodVariator));

            return true;
        }

        return false;
    }
};
