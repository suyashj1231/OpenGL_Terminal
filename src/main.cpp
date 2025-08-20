#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) { std::cerr << "GLFW init failed\n"; return -1; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(1280, 720, "OpenGL Terminal (Scaffold)", nullptr, nullptr);
    if (!win) { std::cerr << "Window create failed\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD load failed\n"; return -1;
    }

    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.06f, 0.07f, 0.09f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(win);
    }
    glfwTerminate();
    return 0;
}
