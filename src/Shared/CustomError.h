//
// Created by alro on 21‏/11‏/2020.
//

#ifndef MYPROJECT_CUSTOMERROR_H
#define MYPROJECT_CUSTOMERROR_H

#include <stdexcept>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException () : std::logic_error{"Function not yet implemented."} {}
};

#endif //MYPROJECT_CUSTOMERROR_H
