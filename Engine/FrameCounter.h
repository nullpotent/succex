#pragma once

class FrameCounter
{

private:

    long count_;
    int  framesElapsed_;

    FrameCounter() : count_(0),
        framesElapsed_(0)
    {
    }

    //copy ctor and assignment should be private
    FrameCounter(const FrameCounter&);
    FrameCounter& operator=(const FrameCounter&);

public:

    static FrameCounter* Instance();

    void Update()
    {
        ++count_;
        ++framesElapsed_;
    }

    long GetCurrentFrame()
    {
        return count_;
    }

    void Reset()
    {
        count_ = 0;
    }

    void Start()
    {
        framesElapsed_ = 0;
    }

    int  FramesElapsedSinceStartCalled() const
    {
        return framesElapsed_;
    }
};
