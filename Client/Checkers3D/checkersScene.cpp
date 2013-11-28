/*
* TP3 LAIG
*
* Eduardo Fernandes  200803951
*
*/

#include "include/checkersScene.hpp"

checkersScene::checkersScene(){
    sceneID = 0;
    nextSceneID = 0;
    this->sceneHasEnded = false;

    /* Not needed (temporary default values) */
    this->aspectRatio = 1;

    this->lastUpdate = 0;
    this->updatePeriod = 0;

    this->numberOfCameras = 0;
    this->mode = GL_RENDER;

    /* GL_FILL */
    this->drawModeInt = 0;

    currentCameraPointer = NULL;

    /* Create an camera that can be used to override the scene cameras */
    externalGuiCamera = new geCameraPerspective();
    currentCameraPointer = externalGuiCamera;
	currentCameraPointer->setPlayerCamera(1);

    /* Set ambient light color */
    ambientLightColor[0] = 0.2f;
    ambientLightColor[1] = 0.2f;
    ambientLightColor[2] = 0.2f;
    ambientLightColor[3] = 0.0f;

    /* Set background color */
    backgroundColor[0] = 0;
    backgroundColor[1] = 0;
    backgroundColor[2] = 0;
    backgroundColor[3] = 0;

}

/* Set stuff */
void checkersScene::setBackgroundColor(geColor in) {
    backgroundColor[0] = (GLfloat) in.r;
    backgroundColor[1] = (GLfloat) in.g;
    backgroundColor[2] = (GLfloat) in.b;
    backgroundColor[3] = (GLfloat) in.a;
}

void checkersScene::setAmbientLightColor(geColor in) {
    ambientLightColor[0] = (GLfloat) in.r;
    ambientLightColor[1] = (GLfloat) in.g;
    ambientLightColor[2] = (GLfloat) in.b;
    ambientLightColor[3] = (GLfloat) in.a;
}

void checkersScene::reSetPolygonMode(int in) {
    switch (in) {
    case 0:
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
        break;

    case 1:
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
        break;

    case 2:
        glPolygonMode(GL_FRONT, GL_POINT);
        glPolygonMode(GL_BACK, GL_POINT);
        break;

    default:
        break;
    }
}


void checkersScene::changeCameraToExernal() {
    currentCameraPointer = externalGuiCamera;
}

/* Search initial camera and set current camera pointer to it */
void checkersScene::setInitialCamera() {
    if (cameraVector.empty()) {
        throw geException("Camera vector is empty!", true);
    }

    if (currentCameraPointer != NULL) {
        throw geException("Current camera pointer is not NULL!", true);
    }

    /* Set first camera on vector */
    currentCameraPointer = cameraVector[0];

    if (currentCameraPointer == NULL) {
        throw geException("Null pointer in camera vector!", true);
    }
}


void checkersScene::applyGlobals() {
    /* Background color */
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);

    /* Cull order */
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    /* Shading mode */
    glShadeModel(GL_SMOOTH);

    /* Cull face */
    //glCullFace(GL_CCW);
    /* Draw mode */
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    drawModeInt = 0;

    /* Enable depth comparisons (z buffer) */
    glEnable(GL_DEPTH_TEST);
}

void checkersScene::init() {

}

/* Reload stuff after context change */
void checkersScene::reInit() {

}

void checkersScene::initLights() {
    /* General lighting parameters setup */
    /* Local is missing */
    glEnable(GL_LIGHTING);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambientLightColor);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, true);
    /* End general lighting */
}

void checkersScene::displayLights() {
    if (!this->lightVector.empty()) {
        for (std::vector<geLight*>::iterator it = lightVector.begin(); it != this->lightVector.end(); it++) {
            if ((*it)->getLightEnableStatus()) {
                (*it)->draw();
            }
        }
    }
}

void checkersScene::applyCameraView() {
    if (this->currentCameraPointer != NULL) {
        this->currentCameraPointer->applyView(this->aspectRatio);
    } else {
        throw geException("The current camera pointer is NULL.", true);
    }
}

void checkersScene::checkUpdate(){}

void checkersScene::display() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    applyCameraView();

    draw();
}

void checkersScene::draw(){

}

void checkersScene::drawPicking(GLfloat* pickMatrix){
	(void)pickMatrix;

}

void checkersScene::update(double dt) {
    (void) dt;
    throw geException("BUG: scene::update needs to be overridden.", true);
}

void checkersScene::processKey(int key){
    (void) key;
    /* Do nothing by default */
}

void checkersScene::processEndScene(){
}

unsigned short int checkersScene::getSceneID(){
    return (this->sceneID);
}

unsigned short int checkersScene::getNextSceneID(){
    return (this->nextSceneID);
}

bool checkersScene::isOver(){
    return sceneHasEnded;
}

void checkersScene::getCurrentCameraInfo(){
	if (currentCameraPointer != NULL)
	currentCameraPointer->printInfo();
}

double checkersScene::getAspectRatio(){
    return (this->aspectRatio);
}

void checkersScene::pickByID(unsigned int id){
    (void) id;
    throw geException("BUG: scene::pickByID needs to be overridden.", true);
}

void checkersScene::hooverByID(unsigned int id){
	/* By default we don't care about hoover events */
	(void)id;
}

void checkersScene::setAspectRatio(double in){
	this->aspectRatio = in;
}

checkersScene::~checkersScene(){

}
