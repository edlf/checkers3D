/*
 * TP3 LAIG
 *
 * Eduardo Fernandes  200803951
 *
 * Texture class methods.
 */

#include "include/geTexture.hpp"

GLuint geTexture::idOpenGLTotal = 0;

geTexture::geTexture(string input) {
    this->loaded = false;
    this->loadedOnce = false;
    this->fileName = input;

    this->wrap_s = 1;
    this->wrap_t = 1;

    this->width = -1;
    this->height = -1;

    this->idOpenGLTotal++;
    this->idOpenGL = idOpenGLTotal;

    this->textureData = NULL;
}

GLuint geTexture::getIdOpenGL() {
    return (this->idOpenGL);
}

int geTexture::getWidth() {
    return (this->width);
}

int geTexture::getHeight() {
    return (this->height);
}

void geTexture::loadTexture() {

    if (!this->fileName.empty() && !this->loaded) {
        string pathFileName = string(TEXTURE_FOLDER) + this->fileName;

        /* Load image */
        try {
            png::image<png::rgb_pixel> textureImage(pathFileName);

            width = (int) textureImage.get_width();
            height = (int) textureImage.get_height();

            /* Load the uncompressed image to ram */
            png::pixel_buffer<png::rgb_pixel> pixbuf = textureImage.get_pixbuf();

            /* OpenGL */
            glGenTextures(1, &idOpenGL);

            int imageSize = width * height * 3;

            textureData = new unsigned char[imageSize];

            for (int i = 0; i < imageSize; i += 3) {
                int x = (i / 3) % width;
                int y = (i / 3) / width;

                png::rgb_pixel pix = pixbuf.get_pixel((std::size_t) x, (std::size_t) y);

                textureData[i + 0] = pix.blue;
                textureData[i + 1] = pix.green;
                textureData[i + 2] = pix.red;
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, this->width);
            glBindTexture(GL_TEXTURE_2D, this->idOpenGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, textureData);

            /* Free ram, texture is in video ram now */
            delete (textureData);
            textureData = NULL;

            /* It has been loaded */
            this->loadedOnce = true;
            this->loaded = true;

        } catch (png::std_error &e) {
            std::cout << "PNG decode error: " << e.what() << std::endl;
        }

    } else {
        throw geException("Texture already loaded or empty file name! " + fileName, true);
    }
}

void geTexture::reloadTexture() {

    if (loadedOnce) {
        string pathFileName = string(TEXTURE_FOLDER) + this->fileName;

        /* Load image */
        try {
            png::image<png::rgb_pixel> textureImage(pathFileName);

            width = (int) textureImage.get_width();
            height = (int) textureImage.get_height();

            /* Load the uncompressed image to ram */
            png::pixel_buffer<png::rgb_pixel> pixbuf = textureImage.get_pixbuf();

            /* OpenGL */
            glGenTextures(1, &idOpenGL);

            int imageSize = width * height * 3;

            textureData = new unsigned char[imageSize];

            for (int i = 0; i < imageSize; i += 3) {
                int x = (i / 3) % width;
                int y = (i / 3) / width;

                png::rgb_pixel pix = pixbuf.get_pixel((std::size_t) x, (std::size_t) y);

                textureData[i + 0] = pix.blue;
                textureData[i + 1] = pix.green;
                textureData[i + 2] = pix.red;
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, this->width);
            glBindTexture(GL_TEXTURE_2D, this->idOpenGL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, textureData);

            /* Free ram, texture is in video ram now */
            delete (textureData);
            textureData = NULL;

            /* It has been loaded */
            this->loaded = true;

        } catch (png::std_error &e) {
            std::cout << "PNG decode error: " << e.what() << std::endl;
        }

    } else {
        throw geException("Texture file deleted during execution!", true);
    }
}

void geTexture::apply() {
    if (this->loaded) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
        glBindTexture(GL_TEXTURE_2D, idOpenGL);
    } else {
        throw geException(this->fileName + " texture is not loaded", true);
    }
}

geTexture::~geTexture() {

}
