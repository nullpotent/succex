#pragma once
#include "Vector2D.h"

template <typename T>
class Point
{
public:
    Point(T x,T y);
    ~Point();
    Point();
    T x_;
    T y_;
};

template <typename T>
Point<T>::Point (T x, T y)
{
    x_ = x;
    y_ = y;
}

template<typename T>
Point<T>::~Point()
{

}

template <typename T>
Point<T>::Point()
{
    x_ = T();
    y_ = T();
}
