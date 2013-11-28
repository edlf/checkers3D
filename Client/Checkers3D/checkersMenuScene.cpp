/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersMenuScene.hpp"

checkersMenuScene::checkersMenuScene(checkersSettings* settingsObjI) : checkersScene() {
    this->sceneID = 2;
    this->nextSceneID = 3;
    this->currentSelection = MENU_SELECTION_START_GAME;

    /* Settings */
    if (settingsObjI != NULL) {
        this->settingsObj = settingsObjI;
    } else {
        throw geException("Settings not initialized!", true);
    }

    /* Textures */
    m_0 = new geTexture("m_sg.png");
	m_1_mb = new geTexture("m_t_mb.png");
	m_1_pl = new geTexture("m_t.png");
	m_1_wd = new geTexture("m_t_wd.png");
    m_2 = new geTexture("m_o.png");
    m_3 = new geTexture("m_e.png");

	/* Appearances */
	highlight = new geAppearance();
	highlight->setSpecular(0, 0.7, 1, 1);
	highlight->setSpecular(1, 0.6, 0.25, 1);
	highlight->setAmbient(0, 1, 0.25, 1);

	/* Shapes */
    rectangle = new checkersPlane();

    /* Set ambient light color */
    ambientLightColor[0] = 0.0f;
    ambientLightColor[1] = 0.0f;
    ambientLightColor[2] = 0.0f;
    ambientLightColor[3] = 0.0f;

    /* Create light */
    geLight* tempLightPointer;
    gePoint temporaryPoint, temporaryDirection;
    geColor temporaryAmbientColor, temporaryDiffuseColor, temporarySpecularColor;

    temporaryPoint.x = 10;
    temporaryPoint.y = 10;
    temporaryPoint.z = 10;

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

    temporaryDirection.x = 0;
    temporaryDirection.y = 0;
    temporaryDirection.z = 0;

    tempLightPointer = new geSpotLight(true, temporaryPoint, temporaryAmbientColor, temporaryDiffuseColor, temporarySpecularColor, 30, 2, temporaryDirection);
    lightVector.push_back(tempLightPointer);

    tempLightPointer = NULL;
}

void checkersMenuScene::init() {
    applyGlobals();
    initLights();

    /* Textures */
    m_0->loadTexture();
    m_1_mb->loadTexture();
	m_1_pl->loadTexture();
	m_1_wd->loadTexture();
    m_2->loadTexture();
    m_3->loadTexture();

}

void checkersMenuScene::reInit() {
    applyGlobals();
    initLights();

    /* Textures */
    m_0->reloadTexture();
    m_1_mb->reloadTexture();
	m_1_pl->reloadTexture();
	m_1_wd->reloadTexture();
    m_2->reloadTexture();
    m_3->reloadTexture();
}

void checkersMenuScene::draw() {
	switch (settingsObj->getCurrentTheme())
	{
	case 0:
		m_1 = m_1_mb;
		break;

	case 1:
		m_1 = m_1_pl;
		break;

	case 2:
		m_1 = m_1_wd;
		break;

	default:
		throw geException("Invalid theme ID", true);
		break;
	}

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawMenuOptions();
    displayLights();
}

void checkersMenuScene::drawPicking(GLfloat* pickMatrix) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPickingMenuOptions();
}

void checkersMenuScene::drawMenuOptions(){
	/* Override camera */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 00);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Draw all options */

	/* Alpha blending */
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	/* Start */
    glPushMatrix();
	glTranslated(0, -2.0, 0);
	glRotated(90, 1, 0, 0);
    glScaled(5.39, 1.0, 0.62);
    m_0->apply();
    rectangle->draw();
    glPopMatrix();

	/* Theme */
    glPushMatrix();
	glTranslated(0, -4.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(2.94, 1.0, 0.62);
    m_1->apply();
    rectangle->draw();
    glPopMatrix();

	/* Options */
    glPushMatrix();
	glTranslated(0, -6.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(3.57, 1.0, 0.62);
    m_2->apply();
    rectangle->draw();
    glPopMatrix();

	/* Exit */
    glPushMatrix();
	glTranslated(0, -8.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(1.92, 1.0, 0.62);
    m_3->apply();
    rectangle->draw();
    glPopMatrix();

	glDisable(GL_TEXTURE_2D);

    /* Highlight current option */
    switch (currentSelection) {
    case MENU_SELECTION_START_GAME:
		glPushMatrix();
		glTranslated(0, -2.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(5.39, 0.02, 0.02);
		highlight->apply();
		rectangle->draw();
		glPopMatrix();
        break;

    case MENU_SELECTION_THEME:
		glPushMatrix();
		glTranslated(0, -4.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(2.94, 0.02, 0.02);
		highlight->apply();
		rectangle->draw();
		glPopMatrix();
        break;

    case MENU_SELECTION_OPTIONS:
		glPushMatrix();
		glTranslated(0, -6.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(3.57, 0.02, 0.02);
		highlight->apply();
		rectangle->draw();
		glPopMatrix();
        break;

    case MENU_SELECTION_EXIT:
		glPushMatrix();
		glTranslated(0, -8.5, 0);
		glRotated(90, 1, 0, 0);
		glScaled(1.92, 0.02, 0.02);
		highlight->apply();
		rectangle->draw();
		glPopMatrix();
        break;

    default:
        break;
    }
}

void checkersMenuScene::drawPickingMenuOptions(){
	/* Start */
	glLoadName(101);
	glPushMatrix();
	glTranslated(0, -2.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(5.39, 0.62, 1);
	rectangle->draw();
	glPopMatrix();

	/* Theme */
	glLoadName(102);
	glPushMatrix();
	glTranslated(0, -4.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(2.94, 0.62, 1);
	rectangle->draw();
	glPopMatrix();

	/* Options */
	glLoadName(103);
	glPushMatrix();
	glTranslated(0, -6.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(3.57, 0.62, 1);
	rectangle->draw();
	glPopMatrix();

	/* Exit */
	glLoadName(104);
	glPushMatrix();
	glTranslated(0, -8.0, 0);
	glRotated(90, 1, 0, 0);
	glScaled(1.92, 0.62, 1);
	rectangle->draw();
	glPopMatrix();
}

void checkersMenuScene::hooverByID(GLuint ID) {
    switch (ID) {
        case 101:
			currentSelection = MENU_SELECTION_START_GAME;
            break;

        case 102:
			currentSelection = MENU_SELECTION_THEME;
            break;

        case 103:
			currentSelection = MENU_SELECTION_OPTIONS;
            break;

        case 104:
			currentSelection = MENU_SELECTION_EXIT;
            break;

        default:
            break;
    }
}

void checkersMenuScene::pickByID(GLuint ID) {
	switch (ID) {
	case 101:
		startGame();
		break;

	case 102:
		this->settingsObj->changeThemeUp();
		break;

	case 103:

		break;

	case 104:
		exitOption();
		break;

	default:
		break;
	}
}

void checkersMenuScene::update(double dt){
    /* Remove */
    (void) dt;
}

void checkersMenuScene::processKey(int key) {
    /* UP key */
    if (key == GLFW_KEY_UP) {
        switch (currentSelection) {
        case MENU_SELECTION_START_GAME:
            currentSelection = MENU_SELECTION_EXIT;
            break;

        case MENU_SELECTION_THEME:
            currentSelection = MENU_SELECTION_START_GAME;
            break;

        case MENU_SELECTION_OPTIONS:
            currentSelection = MENU_SELECTION_THEME;
            break;

        case MENU_SELECTION_EXIT:
            currentSelection = MENU_SELECTION_OPTIONS;
            break;
        default:
            break;
        }

        return;
    }

    /* DOWN key */
    if (key == GLFW_KEY_DOWN) {
        switch (currentSelection) {
        case MENU_SELECTION_START_GAME:
            currentSelection = MENU_SELECTION_THEME;
            break;

        case MENU_SELECTION_THEME:
            currentSelection = MENU_SELECTION_OPTIONS;
            break;

        case MENU_SELECTION_OPTIONS:
            currentSelection = MENU_SELECTION_EXIT;
            break;

        case MENU_SELECTION_EXIT:
            currentSelection = MENU_SELECTION_START_GAME;
            break;
        default:
            break;
        }

        return;
    }

    /* LEFT key */
    if (key == GLFW_KEY_LEFT && this->currentSelection == MENU_SELECTION_THEME){
        /* Change theme */
		this->settingsObj->changeThemeDown();
        return;
    }

    /* RIGHT key */
    if (key == GLFW_KEY_RIGHT && this->currentSelection == MENU_SELECTION_THEME){
        /* Change theme */
		this->settingsObj->changeThemeUp();
        return;
    }


    /* Start option */
    if (key == GLFW_KEY_ENTER && this->currentSelection == MENU_SELECTION_START_GAME) {
        startGame();
        return;
    }

    /* Theme option */
    if (key == GLFW_KEY_ENTER && this->currentSelection == MENU_SELECTION_THEME) {
        /* Change theme */
		this->settingsObj->changeThemeUp();

    }

    /* Options option */
    if (key == GLFW_KEY_ENTER && this->currentSelection == MENU_SELECTION_OPTIONS) {
        /* Show options */

    }

    /* Exit option */
    if (key == GLFW_KEY_ENTER && this->currentSelection == MENU_SELECTION_EXIT) {
        exitOption();
    }
}

void checkersMenuScene::startGame(){
    /* Save settings and start game */
    settingsObj->saveSettings();
    this->sceneHasEnded = true;
}

void checkersMenuScene::exitOption(){
    /* Save settings and exit game */
    settingsObj->saveSettings();
    exit(0);
}

checkersMenuScene::~checkersMenuScene(){
    delete(rectangle);

    delete(m_0);
    delete(m_1_mb);
	delete(m_1_pl);
	delete(m_1_wd);
    delete(m_2);
    delete(m_3);
}
