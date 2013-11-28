/* 
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Texture class, part stolen from CGFlib.
 */

#ifndef GELTEXTURE_HPP_
#define GELTEXTURE_HPP_

#include "hoIncludes.hpp"

using namespace std;

class geTexture {
private:
    /* Attributes */
    static GLuint idOpenGLTotal;
    GLuint idOpenGL;
    int width, height;
    string fileName;

    bool loaded, loadedOnce;

    GLint wrap_s, wrap_t;
    unsigned char* textureData;

public:
    geTexture(string input);

    GLuint getIdOpenGL();
    int getWidth();
    int getHeight();

    void loadTexture();
    void reloadTexture();
    void apply();

    virtual ~geTexture();
};

#endif
