#include "PrecisionTimer.h"


//---------------------- default constructor ------------------------------
//
//-------------------------------------------------------------------------
PrecisionTimer::PrecisionTimer(): normalFPS_(0.0),
    slowFPS_(1.0),
    timeElapsed_(0.0),
    frameTime_(0),
    lastTime_(0),
    lastTimeInTimeElapsed_(0),
    perfCountFreq_(0),
    started_(false),
    startTime_(0),
    lastTimeElapsed_(0.0),
    smoothUpdates_(false)
{
    //how many ticks per sec do we get
    QueryPerformanceFrequency( (LARGE_INTEGER*) &perfCountFreq_);

    timeScale_ = 1.0 / perfCountFreq_;
}

//---------------------- constructor -------------------------------------
//
//  use to specify FPS
//
//-------------------------------------------------------------------------
PrecisionTimer::PrecisionTimer(double fps): normalFPS_(fps),
    slowFPS_(1.0),
    timeElapsed_(0.0),
    frameTime_(0),
    lastTime_(0),
    lastTimeInTimeElapsed_(0),
    perfCountFreq_(0),
    started_(false),
    startTime_(0),
    lastTimeElapsed_(0.0),
    smoothUpdates_(false)
{

    //how many ticks per sec do we get
    QueryPerformanceFrequency( (LARGE_INTEGER*) &perfCountFreq_);

    timeScale_ = 1.0 / perfCountFreq_;

    //calculate ticks per frame
    frameTime_ = (LONGLONG)(perfCountFreq_ / normalFPS_);
}




//------------------------Start()-----------------------------------------
//
//  call this immediately prior to game loop. Starts the timer (obviously!)
//
//--------------------------------------------------------------------------
void PrecisionTimer::Start()
{
    started_ = true;

    timeElapsed_ = 0.0;

    //get the time
    QueryPerformanceCounter( (LARGE_INTEGER*) &lastTime_);

    //keep a record of when the timer was started
    startTime_ = lastTimeInTimeElapsed_ = lastTime_;

    //update time to render next frame
    nextTime_ = lastTime_ + frameTime_;

    return;
}

