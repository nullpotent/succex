#pragma once

#include <sstream>
#include <string>
#include <iomanip>

/*
    Convert a type to a string
*/
template <class T>
inline std::string ttos(const T& t, int precision = 2)
{
    std::ostringstream buffer;
    buffer << std::fixed << std::setprecision(precision) << t;
    return buffer.str();
}

/*
    Convert a bool to a string
*/
inline std::string btos(bool b)
{
    if(b) return "true";
    return "false";
}

/*
    Grabs a value of the specified type from an input
*/
//template <typename T>
//inline T GetValueFromStream(std::ifstream& stream)
//{
//    T val;
//    stream >> val;
//
//    if(!stream.)
//    {
//        throw std::runtime_error("Attempting to retrieve wrong type from stream.");
//    }
//
//    return val;
//}

