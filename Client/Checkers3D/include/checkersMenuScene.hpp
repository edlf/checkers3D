/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#ifndef CHECKERSMENUSCENE_HPP_
#define CHECKERSMENUSCENE_HPP_

#include "checkersScene.hpp"

#define MENU_SELECTION_START_GAME 0
#define MENU_SELECTION_THEME      1
#define MENU_SELECTION_OPTIONS    2
#define MENU_SELECTION_EXIT       3


class checkersMenuScene: public checkersScene{
private:
    /* Settings pointer */
    checkersSettings* settingsObj;

    /* UI */
    geTexture* m_0;
    geTexture* m_1;
	geTexture* m_1_pl;
	geTexture* m_1_mb;
	geTexture* m_1_wd;
    geTexture* m_2;
    geTexture* m_3;

	geAppearance* highlight;

    checkersPlane* rectangle;
    unsigned short int currentSelection;

public:
    checkersMenuScene(checkersSettings* settingsObjI);

    void init();
    void reInit();
    void draw();
    void drawMenuOptions();
	void drawPicking(GLfloat* pickMatrix);
    void drawPickingMenuOptions();
    void pickByID(GLuint ID);
	void hooverByID(GLuint ID);
    void processKey(int key);

    void update(double dt);

    void startGame();
    void exitOption();

    ~checkersMenuScene();
};

#endif /* CHECKERSMENUSCENE_HPP_ */
