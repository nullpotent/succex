#pragma once
//-----------------------------------------------------------------------
//
//  Name: PrecisionTimer.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Windows timer class.
//
//        nb. this only uses the high performance timer. There is no
//        support for ancient computers. I know, I know, I should add
//        support, but hey, I have shares in AMD and Intel... Go upgrade ;o)
//
//-----------------------------------------------------------------------
#include <windows.h>
#include "Misc/Assert.h"


class PrecisionTimer
{

private:

    LONGLONG  currentTime_,
    lastTime_,
    lastTimeInTimeElapsed_,
    nextTime_,
    startTime_,
    frameTime_,
    perfCountFreq_;

    double      timeElapsed_,
    lastTimeElapsed_,
    timeScale_;

    double    normalFPS_;
    double    slowFPS_;

    bool      started_;

    //if true a call to TimeElapsed() will return 0 if the current
    //time elapsed is much smaller than the previous. Used to counter
    //the problems associated with the user using menus/resizing/moving
    //a window etc
    bool      smoothUpdates_;


public:

    //ctors
    PrecisionTimer();
    PrecisionTimer(double fps);


    //whatdayaknow, this starts the timer
    void Start();

    //determines if enough time has passed to move onto next frame
    inline bool ReadyForNextFrame();

    //only use this after a call to the above.
    //double  GetTimeElapsed(){return m_TimeElapsed;}

    inline double TimeElapsed();

    double CurrentTime()
    {
        QueryPerformanceCounter( (LARGE_INTEGER*) &currentTime_);

        return (currentTime_ - startTime_) * timeScale_;
    }

    bool Started() const
    {
        return started_;
    }

    void SmoothUpdatesOn()
    {
        smoothUpdates_ = true;
    }

    void SmoothUpdatesOff()
    {
        smoothUpdates_ = false;
    }

};


//-------------------------ReadyForNextFrame()-------------------------------
//
//  returns true if it is time to move on to the next frame step. To be used if
//  FPS is set.
//
//----------------------------------------------------------------------------
inline bool PrecisionTimer::ReadyForNextFrame()
{
    Assert(normalFPS_ && "PrecisionTimer::ReadyForNextFrame<No FPS set in timer>");

    QueryPerformanceCounter( (LARGE_INTEGER*) &currentTime_);

    if (currentTime_ > nextTime_)
    {

        timeElapsed_ = (currentTime_ - lastTime_) * timeScale_;
        lastTime_    = currentTime_;

        //update time to render next frame
        nextTime_ = currentTime_ + frameTime_;

        return true;
    }

    return false;
}

//--------------------------- TimeElapsed --------------------------------
//
//  returns time elapsed since last call to this function.
//-------------------------------------------------------------------------
inline double PrecisionTimer::TimeElapsed()
{
    lastTimeElapsed_ = timeElapsed_;

    QueryPerformanceCounter( (LARGE_INTEGER*) &currentTime_);

    timeElapsed_ = (currentTime_ - lastTimeInTimeElapsed_) * timeScale_;

    lastTimeInTimeElapsed_    = currentTime_;

    const double smoothness = 5.0;

    if (smoothUpdates_)
    {
        if (timeElapsed_ < (lastTimeElapsed_ * smoothness))
        {
            return timeElapsed_;
        }

        else
        {
            return 0.0;
        }
    }

    else
    {
        return timeElapsed_;
    }

}
