//
// Created by alla on 21/08/23.
//

#ifndef MYPROJECT_ERROR_H
#define MYPROJECT_ERROR_H

#include <exception>
#include <stdexcept>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
};
#endif //MYPROJECT_ERROR_H
