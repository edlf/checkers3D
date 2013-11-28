/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Exception class.
 */

#ifndef GEEXCEPTION_HPP_
#define GEEXCEPTION_HPP_

#include "hoIncludes.hpp"

class geException {
private:
    std::string errorMessage;

public:
    geException();
    geException(std::string str);
    geException(std::string str, bool fatal);

    void printerErrorMessage();
};

#endif
