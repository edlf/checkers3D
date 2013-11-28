/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 */

#include "include/checkersBoard.hpp"

void checkersBoard::addDefaultPieces() {
    /* Add default pieces */
    checkersPiece* temp = NULL;

    for (unsigned short int i = 0; i < BOARD_PIECES_BY_PLAYER; i++) {
        /* White ones (Player1) */
        temp = new checkersPiece(BOARD_WHITE);
        whitePlayerPieces.push_back(temp);

        /* Black ones (Player2) */
        temp = new checkersPiece(BOARD_BLACK);
        blackPlayerPieces.push_back(temp);
    }
    temp = NULL;

    /* Create highlights */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            this->validChoiceOverlay[i][j] = new checkersBoardOverlay(i + 1, j + 1);
            this->validChoiceOverlay[i][j]->disable();
        }
    }
}

checkersBoard::checkersBoard(unsigned short int itheme) {
	this->theme = itheme;

    /* Create an empty board (for input / output) */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            this->IOboard.boardContentsIO[i][j] = BOARD_EMPTY;
            this->IOboard.boardContentsIoHighlights[i][j] = 0;
        }
    }

    addDefaultPieces();

    /* Default player is white */
    this->IOboard.currentPlayer = BOARD_WHITE;

    /* Appearances */
    this->defaultAppearance = new geAppearance();

    this->defaultAppearance->setAmbient(0.5, 0.5, 0.5, 1);
    this->defaultAppearance->setEmissive(0, 0, 0, 1);
    this->defaultAppearance->setDiffuse(0.5, 0.5, 0.5, 1);
    this->defaultAppearance->setSpecular(1, 1, 1, 0);
    this->defaultAppearance->setShininess(128);

    /* End appearances */

    /* Textures */
    this->defaultTexture = new geTexture("defaultBoard.png");
    this->graniteTexture = new geTexture("marbleBoard.png");
	this->woodTexture = new geTexture("woodBoard.png");
    /* End textures */

    mainGameBoard = new checkersPlane(30);

    setDefaultTexture();

    /* Redo & Undo */
    this->gameStatusVectorPosition = 0;
}

void checkersBoard::loadTextures() {
    this->defaultTexture->loadTexture();
    this->graniteTexture->loadTexture();
	this->woodTexture->loadTexture();
	if (blackPlayerPieces.size() > 0){
		blackPlayerPieces[0]->loadTextures();
	}
}

void checkersBoard::reloadTextures() {
    this->defaultTexture->reloadTexture();
    this->graniteTexture->reloadTexture();
	this->woodTexture->reloadTexture();
	if (blackPlayerPieces.size() > 0){
		blackPlayerPieces[0]->reloadTextures();
	}
}

void checkersBoard::draw() {
    /* Regular draw (GL_RENDER) */

    /* Board */
    glPushMatrix();

    /* Draw board */
    glScalef(BOARD_LAYOUT_SIZE, 1, BOARD_LAYOUT_SIZE);
    defaultAppearance->apply();

    /* Apply board texture */
    currentTexture->apply();
    mainGameBoard->draw();

    glPopMatrix();
    /* End board */

    /* Draw tile overlays */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            this->validChoiceOverlay[i][j]->draw();
        }
    }

    /* Draw pieces */
    for (unsigned short int i = 0; i < whitePlayerPieces.size(); i++) {
        whitePlayerPieces[i]->draw();
    }

    for (unsigned short int i = 0; i < blackPlayerPieces.size(); i++) {
        blackPlayerPieces[i]->draw();
    }

}

/* Picking only */
void checkersBoard::drawPicking() {
    /* Draw tile overlays */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            this->validChoiceOverlay[i][j]->drawPicking();
        }
    }

    /* Draw pieces */
    for (unsigned short int i = 0; i < blackPlayerPieces.size(); i++) {
        blackPlayerPieces[i]->drawPicking(BOARD_PICKING_ID_BLACK_PIECE + (GLuint) i);
    }

    for (unsigned short int i = 0; i < whitePlayerPieces.size(); i++) {
        whitePlayerPieces[i]->drawPicking(BOARD_PICKING_ID_WHITE_PIECE + (GLuint) i);
    }
}

void checkersBoard::setDefaultTexture() {
    /* Set current texture to default */
    if (defaultTexture != NULL) {
		switch (theme)
		{
		case 0:
			currentTexture = graniteTexture;
			break;

		case 1:
			currentTexture = defaultTexture;
			break;

		case 2:
			currentTexture = woodTexture;
			break;

		default:
			break;
		}
    } else {
        throw geException("Invalid default texture set!", true);
    }
}

void checkersBoard::update() {
    /* Call the update method, changes are in static members so there is only need to call once */
    if (validChoiceOverlay[0][0] != NULL) {
        validChoiceOverlay[0][0]->update();
    }
}

void checkersBoard::updateFromIO() {
    unsigned short int currentBoardPlace = 0, blackPieces = 0, whitePieces = 0;

    /************ Read board ************/
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            currentBoardPlace = this->IOboard.boardContentsIO[i][j];

            switch (currentBoardPlace) {
            case BOARD_EMPTY:
                break;

            case BOARD_WHITE:
                whitePlayerPieces[whitePieces]->setPosition(i + 1, j + 1);
                whitePlayerPieces[whitePieces]->setCapturedFlag(false);
                whitePieces++;

                break;

            case BOARD_WHITE_KING:
                whitePlayerPieces[whitePieces]->setPosition(i + 1, j + 1);
                whitePlayerPieces[whitePieces]->setCapturedFlag(false);
                whitePieces++;

                break;

            case BOARD_BLACK:
                blackPlayerPieces[blackPieces]->setPosition(i + 1, j + 1);
                blackPlayerPieces[blackPieces]->setCapturedFlag(false);
                blackPieces++;

                break;

            case BOARD_BLACK_KING:
                blackPlayerPieces[blackPieces]->setPosition(i + 1, j + 1);
                blackPlayerPieces[blackPieces]->setCapturedFlag(false);
                blackPieces++;

                break;

            default:
                cout << "Invalid piece!" << endl;
                break;
            }
        }
    }

    /* Pieces not found in the board, are captured */
    for (unsigned short int i = whitePieces; i < whitePlayerPieces.size(); i++) {
        whitePlayerPieces[i]->setCapturedFlag(true);
    }

    for (unsigned short int i = blackPieces; i < blackPlayerPieces.size(); i++) {
        blackPlayerPieces[i]->setCapturedFlag(true);
    }

    /************ Update overlays ************/
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            switch (IOboard.boardContentsIoHighlights[i][j]) {
            case 1:
                validChoiceOverlay[i][j]->setNormal();
                break;
            case 2:
                validChoiceOverlay[i][j]->setDestination();
                break;
            case 3:
                validChoiceOverlay[i][j]->setSelected();
                break;
            default:
                validChoiceOverlay[i][j]->disable();
                break;
            }
        }
    }
}

void checkersBoard::decodeBoard(string input) {
    /* Decode input into an vector of strings */
    vector<string> boardLines;
    boost::split(boardLines, input, boost::is_any_of(";"));

    if (boardLines.size() != 10) {
        cout << boardLines.size() << endl;
        cout << "Invalid board sent, ignoring..." << endl;
        return;
    }

    if (boardLines[9] != ".") {
        cout << "Termination dot not found, ignoring..." << endl;
        return;
    }

    /* Decode lines */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            char currentChar = boardLines[i][j];
            this->IOboard.boardContentsIO[i][j] = (unsigned short int) atoi(&currentChar);
        }
    }

    char currentChar = boardLines[8][0];
    this->IOboard.currentPlayer = (unsigned short int) atoi(&currentChar);
}

void checkersBoard::decodeHighlights(string input) {
    /* Decode input into an vector of strings */
    vector<string> boardLines;
    boost::split(boardLines, input, boost::is_any_of(";"));

    /* Clean up old highlights */
    for (unsigned short int i = 0; i < 8; i++) {
        for (unsigned short int j = 0; j < 8; j++) {
            this->IOboard.boardContentsIoHighlights[i][j] = 0;
        }
    }

    /* Decode lines */
    for (unsigned short int i = 0; i < (boardLines.size() - 1); i++) {
        char temp = boardLines[i][0];
        unsigned short int x = (unsigned short int) atoi(&temp);
        unsigned short int y = (unsigned short int) atoi(&boardLines[i][1]);
        this->IOboard.boardContentsIoHighlights[x][y] = 1;
    }

    updateFromIO();
}

void checkersBoard::decodeValidMoveHighlights(string input) {
    /* Decode input into an vector of strings */
    vector<string> boardLines;
    boost::split(boardLines, input, boost::is_any_of(";"));

    /* Decode lines */
    for (unsigned short int i = 0; i < (boardLines.size() - 1); i++) {
        char temp = boardLines[i][0];

        unsigned short int x = (unsigned short int) atoi(&temp);
        unsigned short int y = (unsigned short int) atoi(&boardLines[i][1]);

        this->IOboard.boardContentsIoHighlights[x][y] = 2;
    }

    updateFromIO();
}

void checkersBoard::decodeSelectedHighlight(string input){
    /* Decode input into an vector of strings */
    vector<string> boardLines;
    boost::split(boardLines, input, boost::is_any_of(";"));

    /* Decode lines */
    for (unsigned short int i = 0; i < (boardLines.size() - 1); i++) {
        char temp = boardLines[i][0];

        unsigned short int x = (unsigned short int) atoi(&temp);
        unsigned short int y = (unsigned short int) atoi(&boardLines[i][1]);

        /* Check if highlight is valid */
        if (x < 8 && y < 8) {
            this->IOboard.boardContentsIoHighlights[x][y] = 3;
        }
    }

    updateFromIO();
}

/* Picking response */
string checkersBoard::pickPieceByID(unsigned int id) {
    unsigned short int kind = (unsigned short int) id / 100;
    unsigned short int pickedPieceID = id % 100;
    unsigned short int pieceX, pieceY;

    switch (kind) {
    case 1:
        pieceX = whitePlayerPieces[pickedPieceID]->getPositionX();
        pieceY = whitePlayerPieces[pickedPieceID]->getPositionY();
        return (selectSquare(pieceX, pieceY));
        break;

    case 2:
        pieceX = blackPlayerPieces[pickedPieceID]->getPositionX();
        pieceY = blackPlayerPieces[pickedPieceID]->getPositionY();
        return (selectSquare(pieceX, pieceY));
        break;

        /* Destination */
    case 3:
        pieceX = pickedPieceID / 10;
        pieceY = pickedPieceID % 10;
        return (selectSquare(pieceX, pieceY));
        break;

    default:
        throw geException("Invalid ID in checkersBoard!", true);
        break;
    }

    return ("");
}

string checkersBoard::selectSquare(unsigned short int x, unsigned short int y) {
    /* Send selected piece to server */
    string send = "SELECT_SQUARE.&&" + convertUIntToStr(x) + ";" + convertUIntToStr(y) + ";.";
    return (send);
}

unsigned short int checkersBoard::getCurrentPlayer(){
	return (this->IOboard.currentPlayer);
}

bool checkersBoard::checkUndoAvailability(){
    if (gameStatusVectorPosition > 0) {
        return (true);
    } else {
        return (false);
    }
}

bool checkersBoard::checkRedoAvailability(){
    if ((gameStatusVectorPosition + 1) < gameStatusVector.size()) {
        return (true);
    } else {
        return (false);
    }
}

checkersBoard::~checkersBoard() {
    currentTexture = NULL;

    if (defaultTexture != NULL) {
        delete (defaultTexture);
    }

    if (graniteTexture != NULL) {
        delete (graniteTexture);
    }

	if (woodTexture != NULL) {
		delete (woodTexture);
	}

	if (blackPlayerPieces.size() > 0){
		if (blackPlayerPieces[0] != NULL) {
			blackPlayerPieces[0]->deleteSharedData();
		}
	}



	blackPlayerPieces.clear();
	whitePlayerPieces.clear();
}
