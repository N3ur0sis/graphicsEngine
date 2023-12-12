#include <glad/glad.h>

#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();
    void initialize();  // Initialisation des VAO, VBO, EBO, etc.
    void render();      // Fonction de rendu de la scène
    void cleanup();     // Nettoyage des ressources OpenGL
    void bindtex();

public:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    unsigned int texture1;
};