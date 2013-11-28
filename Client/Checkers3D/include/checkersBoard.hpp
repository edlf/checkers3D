/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 */

#ifndef CHECKERSBOARD_HPP_
#define CHECKERSBOARD_HPP_

#include "hoIncludes.hpp"
#include "gePrimitive.hpp"
#include "geAppearance.hpp"
#include "geTexture.hpp"
#include "checkersPiece.hpp"
#include "checkersPlane.hpp"
#include "checkersBoardOverlay.hpp"

class checkersBoard{
private:
    boardStatus IOboard;

	/* Actual board */
	vector<checkersPiece*> whitePlayerPieces;
	vector<checkersPiece*> blackPlayerPieces;
	checkersBoardOverlay* validChoiceOverlay[8][8];

	geAppearance * defaultAppearance;

	geTexture* defaultTexture;
	geTexture* graniteTexture;
	geTexture* woodTexture;

	geTexture* currentTexture;

	checkersPlane* mainGameBoard;

	/* Undo & Redo + Movie mode */
	vector <boardStatus> gameStatusVector;
	unsigned int gameStatusVectorPosition;


	void addDefaultPieces();
	string selectSquare(unsigned short int x, unsigned short int y);
	unsigned short int theme;

public:
	checkersBoard(unsigned short int itheme);

	void loadTextures();
	void reloadTextures();
	void setDefaultTexture();
	void decodeBoard(string input);
	void decodeHighlights(string input);
	void decodeValidMoveHighlights(string input);
	void decodeSelectedHighlight(string input);
	string pickPieceByID(unsigned int id);

	unsigned short int getCurrentPlayer();

	void update();
	void updateFromIO();
	void draw();
	void drawPicking();

	/* Undo & Redo */
	bool checkUndoAvailability();
	bool checkRedoAvailability();

	~checkersBoard();
};

#endif
