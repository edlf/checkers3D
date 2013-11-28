/*
 * checkersSettings.cpp
 *
 */

#include "include/checkersSettings.hpp"

void checkersSettings::markAsChanged() {
    this->needsToBeSaved = true;
}

checkersSettings::checkersSettings() {
    /* Load default settings here */
    this->currentTheme = 0;
    this->fullScreen = false;
    this->skipIntro = true;

    this->socketRO = false;
    this->needsToBeSaved = false;

    this->socketPort = "1200";
    this->socketHost = "localhost";

    this->isTimed = false;
    this->maxGameTime = 600;
    this->maxMoveTime = 60;
}

void checkersSettings::loadSettings() {
    try {
        /* create and open an archive for input */
        std::ifstream ifs(SETTINGS_FILE_NAME);
        boost::archive::text_iarchive ia(ifs);
        /* read class state from archive */
        ia >> (*this);
        /* archive and stream closed when destructors are called */
        ifs.close();
    } catch (boost::archive::archive_exception &e) {
        this->needsToBeSaved = true;
		std::cerr << "Error while loading settings: " << e.what() << std::endl;
        std::cout << "No settings file loaded, using defaults." << std::endl;
    }
}

void checkersSettings::saveSettings() {
    /* Only save if the settings has been altered */
    if (needsToBeSaved) {
        try {
            std::ofstream ofs(SETTINGS_FILE_NAME);

            // save data to archive
            boost::archive::text_oarchive oa(ofs);
            // write class instance to archive
            oa << (*this);
            // archive and stream closed when destructors are called
            ofs.flush();
            ofs.close();
        } catch (boost::archive::archive_exception &e) {
            std::cout << "Could not save settings file: " << e.what() << std::endl;
        }
    }
}

void checkersSettings::lockSocketsConfig() {
    socketRO = true;
}

void checkersSettings::unlockSocketsConfig(){
    socketRO = false;
}

void checkersSettings::setSocketPort(std::string in) {
    if (!socketRO) {
        this->socketPort = in;
        markAsChanged();
    } else {
        throw geException("Cannot change socket port after the connection has begun!", true);
    }
}

void checkersSettings::setSocketHost(std::string in) {
    if (!socketRO) {
        this->socketHost = in;
        markAsChanged();
    } else {
        throw geException("Cannot change socket host after the connection has begun!", true);
    }
}

bool checkersSettings::getFullScreenBool() {
    return (this->fullScreen);
}

bool checkersSettings::getSkipIntro() {
    return (this->skipIntro);
}

std::string checkersSettings::getSocketPort() {
    return (this->socketPort);
}

std::string checkersSettings::getSocketHost() {
    return (this->socketHost);
}

unsigned short int checkersSettings::getCurrentTheme(){
	return (this->currentTheme);
}

void checkersSettings::changeThemeUp(){
	if (this->currentTheme == 2) {
		this->currentTheme = 0;
		return;
	}

	this->currentTheme++;
}

void checkersSettings::changeThemeDown(){
	if (this->currentTheme == 0) {
		this->currentTheme = 2;
		return;
	}

	if (this->currentTheme > 0) {
		this->currentTheme--;
		return;
	}
}