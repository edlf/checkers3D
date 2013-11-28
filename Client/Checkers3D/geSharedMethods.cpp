/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/geSharedMethods.hpp"

std::string convertUIntToStr(unsigned int i) {
    std::string s;
    std::stringstream out;
    out << i;
    s = out.str();
    return (s);
}

std::string convertUIntToStr(unsigned short int i) {
	std::string s;
	std::stringstream out;
	out << i;
	s = out.str();
	return (s);
}

void pressEnterToExit() {
    std::cout << "Press enter to continue..." << std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    exit(-1);
}
