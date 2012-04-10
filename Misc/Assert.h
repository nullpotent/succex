#pragma once

#define DEBUG
#include <iostream>

#ifndef DEBUG   //Ako DEBUG nije definisan prilikom kompajliranja
#define Assert(x)
#else
#define Assert(x) \
                if(!(x)) \
                { \
                    std::cout<<"ERROR - ASSERTION "<<#x<<" FAILED"<<std::endl; \
                    std::cout<<" on line "<<__LINE__<<std::endl; \
                    std::cout<<" in file "<<__FILE__<<std::endl; \
                }
#endif
