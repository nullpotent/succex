#pragma once

#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip> //?
#include "Misc/Assert.h"

namespace constants
{

//korisne konstante
const int       MinInt          = (std::numeric_limits<int>::min)();
const int       MaxInt          = (std::numeric_limits<int>::max)();
const double    MaxDouble       = (std::numeric_limits<double>::max)();
const double    MinDouble       = (std::numeric_limits<double>::min)();
const float     MaxFloat        = (std::numeric_limits<float>::max)();
const float     MinFloat        = (std::numeric_limits<float>::min)();

const double    Pi              = 3.14159; //mozda jos da dodam ?
const double    TwoPi           = Pi * 2;
const double    HalfPi          = Pi / 2;
const double    QuarterPi       = Pi / 4;

enum {clockwise = 1, anticlockwise = -1};

};

namespace util
{

using namespace constants;

//swaps two values
template <class T>
inline void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
//vraca true ako je val NaN
template <typename T>
inline bool IsNaN(T val)
{
    return val != val;
}

//konvertuje stepene u radijane
inline double DegsToRads(double degs)
{
    return  TwoPi * (degs / 360.0);
}

inline double RadsToDegs(double rads)
{
    return (360/TwoPi)*rads;
}

//vraca true ako je parametar val jednak nuli
inline bool IsZero(double val)
{
    return ((-MinDouble < val) && (val < MinDouble));
}

//vraca true ako je treci parametar
//unutar granica prvog i drugog
inline bool IsInRange(double start, double end, double val)
{
    if(start < end)
    {
        return ((val > start) && (val < end));
    }
    else
    {
        return ((val < start) && (val > end));
    }
}

//vraca maksimum dva tipa (klase - moram overridovati operatore < i >)
template <class T>
T Maximum(const T& v1, const T& v2)
{
    return v1 > v2 ? v1 : v2;
}

//vraca minimum dva tipa (klase)
template <class T>
T Minimum(const T& v1, const T& v2)
{
    return v1 < v2 ? v1 : v2;
}

//vraca random integer iz domena (x,y)
inline int RandInt(int x, int y)
{
    return rand() % (y-x+1) + x;
}

//vraca random double iz domena (0.0f,1.0f)
inline double RandDouble()
{
    return ((rand())/(RAND_MAX+1.0));
}

//vraca random double iz domena (x,y)
inline double RandInRange(double x, double y)
{
    return x + RandDouble() * (y-x);
}

//vraca random boolean vrednost
inline bool RandBool()
{
    return RandInt(0,1) > 0 ? true : false;
}

//vraca random double iz domena (-1.0,1.0);
inline double RandClamped()
{
    return RandDouble() - RandDouble();
}

//vraca random double brojeve sa normalnom distribucijom
///http://www.taygeta.com/random/gaussian.html
inline double RandGaussian(double mean = 0.0, double stDev = 1.0)
{
    double x1, x2, w, y1;
    static double y2;
    static int useLast = 0;

    if(useLast)
    {
        y1 = y2;
        useLast = 0;
    }
    else
    {
        do
        {
            x1 = 2.0 * RandDouble() - 1.0;
            x2 = 2.0 * RandDouble() - 1.0;
            w = (x1 * x1) + (x2 * x2);
        }
        while (w >= 1.0);

        w = sqrt((-2.0 * log(w)) / w);
        y1 = x1 * w;
        y2 = x2 * w;
        useLast = 1;
    }

    return (mean + y1 * stDev);
}

//kada ne znamo tacno kakva je distribucija a zelimo opisati normalnu
//distribuciju, onda koristimo Sigmoid funkciju
inline double Sigmoid(double input, double response = 1.0)
{
    return (1.0 / (1.0 + exp(-input / response)));
}

//inline verzija Maximum funkcije gore ^
template <class T>
inline T MaxOf(const T& a, const T& b)
{
    return a > b ? a : b;
}

//inline verzija Minimum funkcije gore ^
template <class T>
inline T MinOf(const T& a, const T& b)
{
    return a < b ? a : b;
}

//clampuje prvi argument imedju druga dva
template <class T, class U, class V>
inline void Clamp(T& arg, const U& min, const V& max)
{
    Assert(min < max);

    if(arg < (T)min)
    {
        arg = (T)min;
    }

    if(arg > (T)max)
    {
        arg = (T)max;
    }
}

//zaokruzuje double

inline int Round(double val)
{
    int integral = (int)val;
    double mantisa = val - integral;

    if(mantisa < 0.5)
    {
        return integral;
    }
    else
    {
        return integral + 1;
    }
}

//zaokruzuje val u zavisnosti je li mu mantisa veca ili manja
//od offset-a
inline int RoundOffset(double val, double offset)
{
    int integral = (int)val;
    double mantisa = val - integral;

    if(mantisa < offset)
    {
        return integral;
    }
    else
    {
        return integral + 1;
    }
}

//vraca true ako su dva realna broja a i b jednaki
inline bool IsEqual(float a, float b)
{
    if(fabs(a-b) < 1E-12)
    {
        return true;
    }
    return false;
}

inline bool IsEqual(double a, double b)
{
    if(fabs(a-b) < 1E-12)
    {
        return true;
    }
    return false;
}

//vraca srednju vrednosti iz vektora
template <class T>
inline double Average(const std::vector<T>& vec)
{
    double average = 0.0;

    for(unsigned int i=0; i < vec.size(); ++i)
    {
        average += (double)vec[i];
    }

    return average / (double)vec.size();
}

//izracunava standardnu devijaciju iz vektora
///Vidi na netu zasto se bas tako radi
inline double StandardDeviation(const std::vector<double>& v)
{
    double sd   = 0.0;
    double avg  = Average(v);

    for(unsigned int i=0; i < v.size(); ++i)
    {
        sd += (v[i] - avg) * (v[i] - avg);
    }

    sd = sd / v.size();

    return sqrt(sd);
}

template< typename T >
struct delete_ptr : public std::unary_function<bool,T>
{
   bool operator()(T*pT) const { delete pT; return true; }
};

//brise standardni container (vec,list,queue,etc..)
//        template <class container>
//        inline void DeleteSTLContainer(container& c)
//        {
//            container::iterator it;
//            for(it = c.begin(); it != c.end(); ++it)
//            {
//                delete *it;
//                *it = NULL; //check, check, say what nigger ? !?!??!
//            }
//        }
//
//        //brise STL mapu
//        template <class map>;
//        inline void DeleteSTLMap(map& m)
//        {
//            for(map::iterator it = m.begin(); it != m.end(); ++it)
//            {
//                delete *it->second;
//                *it->second = NULL;
//            }
//        }


};


