#pragma once
#include <glad/glad.h>

class Framebuffer {
public:
    Framebuffer();
    ~Framebuffer();
    void create();
    void bind();
    void unbind();
    void rescale(float width, float height);
    GLuint getTextureID() const; // Getter for texture ID
private:
    GLuint FBO;
    GLuint RBO;
    GLuint textureID;
};