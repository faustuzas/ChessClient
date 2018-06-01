#ifndef NetworkTerminatedException_hpp
#define NetworkTerminatedException_hpp

#include <stdio.h>
#include <exception>
#include <stdexcept>

class NetworkTerminatedException : public std::runtime_error
{
public:
    NetworkTerminatedException() : runtime_error("Connection was terminated...") {}
};

#endif
