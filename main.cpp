#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Enumeration for buffer indexing, pluss numbers of avaliable buffers.
enum {VB_POSITION, NUM_BUFFERS};

// Open a window and create its OpenGL context
GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)

// An array of 3 vectors which represents 3 vertices
static const GLfloat vertecies[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    0.0f,  1.0f,
};

int main()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 16); // 16x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    window = glfwCreateWindow(1024, 768, "OpenGl2d", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 4.0 compatible.\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Our vertex array object (contains vbo's. MAX: 16)
    GLuint vao;

    // Out vertex buffer object (lives inside the vao)
    GLuint vbo;

    // Generate vao
    glGenVertexArrays(1, &vao);

    // Bind it for use
    glBindVertexArray(vao);

    // Gen vertex buffer object
    glGenBuffers(1, &vbo);

    // Bind buffer for use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Fill the vbo with our vertecies
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);

    // Draw loop
    do {
        // Clear window with white color
        //glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        // Enable Vertex Attrib Array "VB_POSITION"
        glEnableVertexAttribArray(VB_POSITION);

        // Bind the vbo for drawing
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Tell OpenGL aboutn the data and how it should read it
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Tell OpenGL to draw
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Disable the vbo "VB_POSITION"
        glDisableVertexAttribArray(VB_POSITION);

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll event off event queue for handling
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    return 0;
}