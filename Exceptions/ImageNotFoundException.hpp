#ifndef ImageNotFoundException_hpp
#define ImageNotFoundException_hpp

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include <string>

class ImageNotFoundException : public std::runtime_error
{
public:
    std::string filename;
    ImageNotFoundException(const std::string& fn) :
        runtime_error("Images was not found. Check your file system..."),
        filename(fn)
        {}
};

#endif
