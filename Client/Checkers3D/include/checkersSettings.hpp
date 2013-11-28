/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSSETTINGS_HPP_
#define CHECKERSSETTINGS_HPP_

#include "hoIncludes.hpp"

class checkersSettings{
private:
    friend class boost::serialization::access;

    /* Display settings */
    unsigned short int currentTheme;
    bool fullScreen;
    bool skipIntro;

    /* Internal status */
    bool socketRO;
    bool needsToBeSaved;

    /* Sockets */
    std::string socketPort;
    std::string socketHost;

    /* Time */
    bool isTimed;
    unsigned short int maxGameTime, maxMoveTime;

    void markAsChanged();

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        /* We don't need no stinkin version */
        (void) version;

        /* Display settings */
        ar & currentTheme;
        ar & fullScreen;

        /* Internal status */
        ar & socketRO;
        ar & needsToBeSaved;

        /* Sockets */
        ar & socketPort;
        ar & socketHost;

        /* Time */
        ar & isTimed;
        ar & maxGameTime;
        ar & maxMoveTime;
    }

public:
    checkersSettings();

    void loadSettings();
    void saveSettings();

    void lockSocketsConfig();
    void unlockSocketsConfig();
    void setSocketPort(std::string in);
    void setSocketHost(std::string in);

    bool getFullScreenBool();
    bool getSkipIntro();
    std::string getSocketPort();
    std::string getSocketHost();

	unsigned short int getCurrentTheme();
	void changeThemeUp();
	void changeThemeDown();
};

BOOST_CLASS_VERSION(checkersSettings, 1)

#endif
