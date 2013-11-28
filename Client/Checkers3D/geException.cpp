/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/geException.hpp"

geException::geException() {
    errorMessage = "Unknown error.";
}

geException::geException(std::string str) {
    errorMessage = str;
}

geException::geException(std::string str, bool fatal) {
    errorMessage = str;

    if (fatal) {
        std::cerr << "Fatal exception caught: " << errorMessage.c_str() << std::endl << std::flush;
        std::cerr << "\"And on that bombshell it is time to end. Good night!\"" << std::endl << std::flush;
        exit(-1);
    }

}

void geException::printerErrorMessage() {
    std::cerr << "Exception caught: " << errorMessage.c_str() << std::endl;
}
