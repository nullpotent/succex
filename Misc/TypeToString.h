#pragma once

#include <string>

class TypeToString
{
    public:
        virtual std::string Convert(int enumeration) = 0;
};
