#pragma once

#include <vector>

template <class T>
class Smoother
{
private:

    //this holds the history
    std::vector<T>  history_;

    int           nextUpdate_;

    //an example of the 'zero' value of the type to be smoothed. This
    //would be something like Vector2D(0,0)
    T             zeroValue_;

public:

    //to instantiate a Smoother pass it the number of samples you want
    //to use in the smoothing, and an exampe of a 'zero' type
    Smoother(int SampleSize, T ZeroValue):history_(SampleSize, ZeroValue),
        zeroValue_(ZeroValue),
        nextUpdate_(0)
    {}

    //each time you want to get a new average, feed it the most recent value
    //and this method will return an average over the last SampleSize updates

    T Update(const T& MostRecentValue)
    {
        //overwrite the oldest value with the newest
        history_[nextUpdate_++] = MostRecentValue;

        //make sure nextUpdate_ wraps around.
        if (nextUpdate_ == history_.size()) nextUpdate_ = 0;

        //now to calculate the average of the history list
        T sum = zeroValue_;

        typename std::vector<T>::iterator it = history_.begin();

        for (it; it != history_.end(); ++it)
        {
            sum += *it;
        }

        return sum / (double)history_.size();
    }
};
