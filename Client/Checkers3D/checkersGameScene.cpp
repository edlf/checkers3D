/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Scene class methods.
 */

#include "include/checkersGameScene.hpp"

checkersGameScene::checkersGameScene(checkersSettings* settingsObjI) :
checkersScene() {
	this->sceneID = 3;
	this->nextSceneID = 2;

	/* Settings */
	if (settingsObjI != NULL) {
		this->settingsObj = settingsObjI;
	}
	else {
		throw geException("Settings not initialized!", true);
	}

	/* Create lights */
	geLight* tempLightPointer;
	gePoint temporaryPoint, temporaryDirection;
	geColor temporaryAmbientColor, temporaryDiffuseColor, temporarySpecularColor;

	temporaryPoint.x = 5;
	temporaryPoint.y = 10;
	temporaryPoint.z = 5;

	temporaryAmbientColor.r = 1;
	temporaryAmbientColor.g = 1;
	temporaryAmbientColor.b = 1;
	temporaryAmbientColor.a = 1;

	temporaryDiffuseColor.r = 1;
	temporaryDiffuseColor.g = 1;
	temporaryDiffuseColor.b = 1;
	temporaryDiffuseColor.a = 1;

	temporarySpecularColor.r = 1;
	temporarySpecularColor.g = 1;
	temporarySpecularColor.b = 1;
	temporarySpecularColor.a = 1;

	//tempLightPointer = new geOmniLight(true, temporaryPoint, temporaryAmbientColor, temporaryDiffuseColor, temporarySpecularColor);
	//lightVector.push_back(tempLightPointer);
	tempLightPointer = NULL;

	temporaryPoint.x = 0;
	temporaryPoint.y = 5;
	temporaryPoint.z = 0;

	temporaryDirection.x = 0;
	temporaryDirection.y = 0;
	temporaryDirection.z = 0;

	tempLightPointer = new geSpotLight(true, temporaryPoint, temporaryAmbientColor, temporaryDiffuseColor, temporarySpecularColor, 30, 2, temporaryDirection);

	lightVector.push_back(tempLightPointer);

	tempLightPointer = NULL;

	background = new checkersBackground();

	/* Create game objects */
	gameBoard = new checkersBoard(settingsObj->getCurrentTheme());

	/* Textures */
	uiUndo = new geTexture("ui_undo.png");
	uiRedo = new geTexture("ui_redo.png");

	uiMovie = new geTexture("ui_movie.png");
	uiExit = new geTexture("ui_exit.png");

	/* UI */
	rectangle = new checkersPlane();
	gameHasEnded = false;
	movieMode = false;

	/* Time */
	gameMinutes = 0;
	gameSeconds = 0;
	this->moveSeconds = 30;
	this->lastPlayer = 1;
	timeSinceLastDelta = 0.0;

	/* Sockets */
	socketsIsConnected = false;

	initSockets();
}

void checkersGameScene::init() {
	applyGlobals();
	initLights();

	uiUndo->loadTexture();
	uiRedo->loadTexture();

	uiMovie->loadTexture();
	uiExit->loadTexture();

	gameBoard->loadTextures();
	background->loadTextures();

}

/* Reload stuff after context change */
void checkersGameScene::reInit() {
	applyGlobals();
	initLights();

	uiUndo->reloadTexture();
	uiRedo->reloadTexture();

	uiMovie->reloadTexture();
	uiExit->reloadTexture();

	gameBoard->reloadTextures();
	background->reloadTextures();
}

/* Draw everything here */
void checkersGameScene::draw() {
	if (currentCameraPointer != NULL)
		currentCameraPointer->setPlayerCamera(gameBoard->getCurrentPlayer());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// background->draw();
	glColor3d(1.0, 1.0, 1.0);
	gameBoard->draw();

	displayLights();

	drawUI();
}

void checkersGameScene::drawUI(){
	/* Override camera */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(-10, 10, -10, 00);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* Draw all options */

	/* Movie */
	if (gameHasEnded) {
		glPushMatrix();
		glTranslated(-9, -1.3, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		uiMovie->apply();
		rectangle->draw();
		glPopMatrix();
	}
	else {
		/* Undo */
		glPushMatrix();
		glTranslated(-9, -0.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		uiUndo->apply();
		rectangle->draw();
		glPopMatrix();

		/* Redo */
		glPushMatrix();
		glTranslated(-8, -0.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		uiRedo->apply();
		rectangle->draw();
		glPopMatrix();
	}

	/* Exit */
	glPushMatrix();
	glTranslated(-9, -2.1, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.5, 1.0, 0.5);
	uiExit->apply();
	rectangle->draw();
	glPopMatrix();

	/* Draw text info */
	glDisable(GL_TEXTURE_2D);

	if (!gameHasEnded){
		/* Nasty hack */
		std::string temp;
		if (gameMinutes < 10 && gameSeconds < 10) {
			temp = "Time Passed: 0" + convertUIntToStr(gameMinutes) + ":0" + convertUIntToStr(gameSeconds);
		}
		else if (gameMinutes < 10) {
			temp = "Time Passed: 0" + convertUIntToStr(gameMinutes) + ":" + convertUIntToStr(gameSeconds);
		}
		else if (gameSeconds < 10) {
			temp = "Time Passed: " + convertUIntToStr(gameMinutes) + ":0" + convertUIntToStr(gameSeconds);
		}
		else {
			temp = "Time Passed: " + convertUIntToStr(gameMinutes) + ":" + convertUIntToStr(gameSeconds);
		}

		/* Current time */
		glPushMatrix();
		glTranslated(-2.4, -0.5, 0);
		glScaled(0.0025, 0.0025, 0.0025);
		glColor3f(0.8f, 0.8f, 0.8f);
		for (unsigned int i = 0; i < temp.size(); i++){
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, temp[i]);
		}
		glPopMatrix();

		/* Time left */
		glPushMatrix();
		glTranslated(-1.8, -1.0, 0);
		glScaled(0.0025, 0.0025, 0.0025);
		if (moveSeconds < 10) {
			temp = "Time left: 0" + convertUIntToStr(moveSeconds);
			glColor3f(0.8f, 0.0f, 0.0f);
		}
		else {
			temp = "Time left: " + convertUIntToStr(moveSeconds);
			glColor3f(0.8f, 0.8f, 0.8f);
		}
		for (unsigned int i = 0; i < temp.size(); i++){
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, temp[i]);
		}
		glPopMatrix();


		/* Current player */
		switch (gameBoard->getCurrentPlayer())
		{
		case BOARD_WHITE:
			temp = "Whites turn";
			break;

		case BOARD_BLACK:
			temp = "Blacks turn";
			break;

		default:
			temp = "SERVER ERROR";
			break;
		}

		glPushMatrix();
		glTranslated(-1.5, -1.5, 0);
		glScaled(0.0025, 0.0025, 0.0035);
		glColor3f(0.8f, 0.8f, 0.8f);
		for (unsigned int i = 0; i < temp.size(); i++){
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, temp[i]);
		}
		glPopMatrix();
	}
	else {

		string temp = "Game has ended";

		glPushMatrix();
		glTranslated(-1.5, -1.5, 0);
		glScaled(0.0025, 0.0025, 0.0035);
		glColor3f(0.8f, 0.8f, 0.8f);
		for (unsigned int i = 0; i < temp.size(); i++){
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, temp[i]);
		}
		glPopMatrix();

	}




	/* Return everything to the old state */
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

/* Draw only stuff needed for picking here */
void checkersGameScene::drawPicking(GLfloat* pickMatrix){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gameBoard->drawPicking();

	drawPickingUI(pickMatrix);

}

void checkersGameScene::drawPickingUI(GLfloat* pickMatrix){
	/* Override camera */
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMultMatrixf(pickMatrix);
	gluOrtho2D(-10, 10, -10, 00);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	/* Movie */
	if (gameHasEnded) {
		glLoadName(503);
		glPushMatrix();
		glTranslated(-9, -1.3, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		rectangle->draw();
		glPopMatrix();
	}
	else {
		/* Undo */
		glLoadName(501);
		glPushMatrix();
		glTranslated(-9, -0.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		rectangle->draw();
		glPopMatrix();

		/* Redo */
		glLoadName(502);
		glPushMatrix();
		glTranslated(-8, -0.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.5, 1.0, 0.5);
		rectangle->draw();
		glPopMatrix();
	}

	/* Exit */
	glLoadName(504);
	glPushMatrix();
	glTranslated(-9, -2.1, 0);
	glRotated(90, 1, 0, 0);
	glScaled(0.5, 1.0, 0.5);
	rectangle->draw();
	glPopMatrix();

	/* Return everything to the old state */
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void checkersGameScene::update(double dt) {
	/* Game timer */
	timeSinceLastDelta = timeSinceLastDelta + dt;

	if (gameBoard != NULL) {
		gameBoard->update();
	}

	if (timeSinceLastDelta >= 1.0) {
		timeSinceLastDelta = 0.0;

		if (!gameHasEnded){
			gameSeconds++;
			moveSeconds--;
			if (gameSeconds == 60) {
				gameMinutes++;
				gameSeconds = 0;
			}

			if (moveSeconds == 0) {
				moveSeconds = 30;
				skipMove();
				refreshBoard();
			}

			if (gameMinutes == 10){
				/*End game here*/
				sendStringToServer("TIMEUP.");
			}
		}

		if (movieMode) {
			cout << "Movie next" << endl;
			movieModeSecs++;
			if (movieModeSecs == 5) {
				movieModeSecs = 0;
				sendStringToServer("MOVIE_NEXT.");
				refreshBoard();
			}
		}
	}

	/* Player changes reset timer */
	if (gameBoard->getCurrentPlayer() != lastPlayer){
		this->moveSeconds = 30;
	}

	lastPlayer = gameBoard->getCurrentPlayer();

	/* Call the shader update */
	//if (!this->waterLineVector.empty()) {
	//    for (vector<geWaterLine*>::iterator it = this->waterLineVector.begin(); it != this->waterLineVector.end(); ++it) {
	//        (*it)->update(millis);
	//    }
	//}
}

/* Sockets here */
void checkersGameScene::initSockets() {
	using boost::asio::ip::tcp;

	try {
		socketStream = new tcp::iostream(settingsObj->getSocketHost(), settingsObj->getSocketPort());

		if (!socketStream) {
			cout << "Unable to connect: " << socketStream->error().message() << endl;
			this->socketsIsConnected = false;
		}
		else {
			this->socketsIsConnected = true;
			communicationThread = new boost::thread(boost::bind(&checkersGameScene::threadSockets, this));
		}

	}
	catch (std::exception& e) {
		cerr << "Sockets exception: " << e.what() << endl;
	}

}

void checkersGameScene::threadSockets() {
	cout << "Communication thread begin" << endl;

	checkIfServerIsAlive();

	if (socketsIsConnected) {
		cout << "Server is alive!" << endl;
	}
	else {
		cout << "Could not reach server.." << endl;
		return;
	}

	refreshBoard();

	cout << "Communication thread end" << endl;
}

void checkersGameScene::closeServer() {
	sendStringToServer("EXIT.");
}

void checkersGameScene::endSockets() {
	/* Close the communication thread */
	communicationThread->join();

	/* Close sockets stream */
	(*socketStream).close();

	cout << "Disconnected from server" << endl;
}

void checkersGameScene::refreshBoard(){
	string checkGame = sendStringToServer("ISGAMEON.");

	if (checkGame == "YES."){
		/* Board refresh */
		string boardServer = sendStringToServer("GET_BOARD.");
		this->gameBoard->decodeBoard(boardServer);

		string highlightPieceServer = sendStringToServer("GET_PIECE_HIGHLIGHT.");
		this->gameBoard->decodeHighlights(highlightPieceServer);

		string highlightMoveServer = sendStringToServer("GET_SEL_MOVES_HIGHLIGHT.");
		this->gameBoard->decodeValidMoveHighlights(highlightMoveServer);

		string highlightSelectedServer = sendStringToServer("GET_SELECTED.");
		this->gameBoard->decodeSelectedHighlight(highlightSelectedServer);
	}
	else {
		string boardServer = sendStringToServer("GET_BOARD.");
		this->gameBoard->decodeBoard(boardServer);

		gameHasEnded = true;
	}
}

string checkersGameScene::sendStringToServer(string input) {
	string response = "";

	(*socketStream) << (input + "\n");

	/* Receive string */
	getline((*socketStream), response);
	/* Trim response, since boost adds some character under windows */
	boost::trim(response);

	return (response);
}

void checkersGameScene::checkIfServerIsAlive() {
	if ((*socketStream).good()) {

		/* The socket is good, check response */
		if (boost::iequals(sendStringToServer("HELLO."), "MINE_TURTLE.")) {
			socketsIsConnected = true;
			return;
		}
	}
	/* Something failed */
	socketsIsConnected = false;
}
/* Sockets section end*/

void checkersGameScene::pickByID(GLuint id){
	unsigned int kind = id / 100;

	switch (kind) {
		/* A piece or highlight as picked up */
	case 1:
	case 2:
	case 3:
		sendStringToServer(gameBoard->pickPieceByID(id));
		refreshBoard();
		break;

		/* An UI element has been picked up */
	case 5:
		processUIEvent(id);
		break;

	default:
		break;
	}
}

void checkersGameScene::hooverByID(GLuint id) {
	(void)id;
}

void checkersGameScene::processEndScene() {
}

void checkersGameScene::processUIEvent(GLuint id) {
	switch (id)
	{
	case 501:
		/* Undo */
		sendStringToServer("UNDO.");
		refreshBoard();
		break;

	case 502:
		/* Redo */
		sendStringToServer("REDO.");
		refreshBoard();
		break;

	case 503:
		/* Movie */
		movieMode = true;
		sendStringToServer("MOVIE.");
		break;

	case 504:
		/* Exit */
		sendStringToServer("RESET.");
		sceneHasEnded = true;
		break;

	default:
		break;
	}
}

void checkersGameScene::skipMove(){
	sendStringToServer("FORFEIT.");
}

/* Scene destructor */
checkersGameScene::~checkersGameScene() {
	/* Disconnect from server and close communication threads */
	endSockets();

	currentCameraPointer = NULL;

	/* Clear cameras */
	for (unsigned int i = 0; i < cameraVector.size(); i++) {
		if (cameraVector[i] != NULL) {
			delete (cameraVector[i]);

		}
	}
	cameraVector.clear();

	/* Clear lights */
	for (unsigned int i = 0; i < lightVector.size(); i++) {
		if (lightVector[i] != NULL) {
			delete (lightVector[i]);

		}
	}
	lightVector.clear();

	if (background != NULL) {
		delete (background);
	}
	background = NULL;

	if (gameBoard) {
		delete (gameBoard);
	}
	gameBoard = NULL;

	if (rectangle) {
		delete (rectangle);
	}
	rectangle = NULL;

	if (uiUndo) {
		delete (uiUndo);
	}
	uiUndo = NULL;

	if (uiRedo) {
		delete (uiRedo);
	}
	uiRedo = NULL;

	if (uiMovie) {
		delete (uiMovie);
	}
	uiMovie = NULL;

	if (uiExit) {
		delete (uiExit);
	}
	uiExit = NULL;
}
