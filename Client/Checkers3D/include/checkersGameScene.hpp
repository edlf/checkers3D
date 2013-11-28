/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Scene class.
 */

#ifndef CHECKERSGAMESCENE_HPP_
#define CHECKERSGAMESCENE_HPP_

#include "checkersScene.hpp"

class checkersGameScene : public checkersScene {
private:
    /* Checkers 3D */
    checkersBackground* background;
    checkersBoard* gameBoard;
    checkersSettings* settingsObj;

    /* Sockets */
    bool socketsIsConnected;
    boost::thread* communicationThread;
    boost::asio::ip::tcp::iostream* socketStream;

    void initSockets();
    void threadSockets();
    void closeServer();
    void endSockets();

    std::string sendStringToServer(std::string input);
    void checkIfServerIsAlive();
    void refreshBoard();

	/* UI */
	checkersPlane* rectangle;

	geTexture* uiUndo;
	geTexture* uiRedo;
	geTexture* uiMovie;
	geTexture* uiExit;

	bool gameHasEnded, movieMode;
	unsigned short int lastPlayer;

	/* Time */
	unsigned short int gameMinutes, gameSeconds, moveSeconds, movieModeSecs;
	double timeSinceLastDelta;

public:
    checkersGameScene(checkersSettings* settingsObjI);

    void init();
    void reInit();
    void draw();
	void drawUI();
	void drawPicking(GLfloat* pickMatrix);
	void drawPickingUI(GLfloat* pickMatrix);
    void update(double dt);
	void pickByID(GLuint id);
	void hooverByID(GLuint id);
	void processEndScene();

	void processUIEvent(GLuint id);

	void skipMove();
    /*  */
    virtual ~checkersGameScene();
};

#endif
