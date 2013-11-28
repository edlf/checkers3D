/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersIntroScene.hpp"

void checkersIntroScene::createFade(){
    // ln(x+1)
    // 0 to 1.5

    deltaTime = 3.0 / 60.0;

    double steps = 1.5 / 60.0;
    double currentStep = 0;
    currentPos = 0;

    for (unsigned short int i = 0; i < 60; i++){
        fadeIn[i] = std::log (currentStep + 1.0) * 0.4;
        currentStep = currentStep + steps;
    }
}

checkersIntroScene::checkersIntroScene(checkersSettings* settingsObjI) : checkersScene() {
    this->sceneID = 1;
    this->nextSceneID = 2;

    if (settingsObjI != NULL) {
        this->settingsObj = settingsObjI;
    } else {
        throw geException("Settings not initialized!", true);
    }

    if (settingsObj->getSkipIntro()) {
        this->sceneHasEnded = true;
        return;
    }

    this->stage = 0;
    this->ct = 0;

    createFade();
    this->ball = new geSphere(4.0, 50, 50);
    this->appearance = new geAppearance();

    emissive.r = 0;
    emissive.g = 0;
    emissive.b = 0;
    emissive.a = 0;

    appearance->setShininess(128);

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

void checkersIntroScene::init() {
    applyGlobals();
    initLights();
}

void checkersIntroScene::reInit() {
    applyGlobals();
    initLights();
}

void checkersIntroScene::draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    displayLights();

    appearance->apply();
    ball->draw(1,1);
}

void checkersIntroScene::drawPicking(GLfloat* pickMatrix) {
	(void)pickMatrix;
}

void checkersIntroScene::pickByID(GLuint ID) {
    std::cout << "Picked id: " << ID << std::endl;
}

void checkersIntroScene::update(double dt){
    timeSinceLastDelta = timeSinceLastDelta + dt;

    /* (3 secs) Fade In */
    if (stage == 0) {

        if (timeSinceLastDelta > deltaTime){
            timeSinceLastDelta = 0.0;

            emissive.r = fadeIn[currentPos];
            // emissive.g = 0;
            // emissive.b = 0;

            currentPos++;

            if (currentPos == 60){
                currentPos--;
                stage=1;
            }
        }

    } else

    /* (2 secs) Still */
    if (stage == 1) {

        if (timeSinceLastDelta > deltaTime){
            timeSinceLastDelta = 0.0;

            ct++;

            if (ct == 30){
                stage = 2;
            }
        }

    } else

    /* (3 secs)Fade Out */
    if (stage == 2) {
        if (currentPos == 0){
            stage=3;
            return;
        }

        if (timeSinceLastDelta > deltaTime){
            emissive.r = fadeIn[currentPos];
            // emissive.g = 0;
            // emissive.b = 0;
            timeSinceLastDelta = 0.0;
            currentPos--;
        }
    }

    if (stage == 3){
        this->sceneHasEnded = true;
        return;
    }

    appearance->setEmissive(emissive);
    appearance->setAmbient(emissive);
    appearance->setDiffuse(emissive);
    appearance->setSpecular(emissive);
}

checkersIntroScene::~checkersIntroScene(){
    if (!lightVector.empty()){

        for (unsigned int i = lightVector.size(); i > 0; i--) {
            delete(lightVector[i-1]);
        }

        lightVector.clear();
    }
}
