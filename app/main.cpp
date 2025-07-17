#include <iostream>
#include <string>
#include <config.hpp>

#include <window.hpp>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/ContextInfo.h>

#define BLACK 0.0f, 0.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f, 1.0f

void gameLoop(glfw::Window& window);

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"C++ Standard: "<<__cplusplus<<std::endl;

    glfw::Window window("LearOpenGL", 800, 600);
    gameLoop(window);

    return 0;
}

void gameLoop(glfw::Window& window){
    do{
        glfwPollEvents();

        gl::glClearColor(WHITE);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.getPtr());
    }while(!glfwWindowShouldClose(window.getPtr()));

    glfwDestroyWindow(window.getPtr());
    glfwTerminate();

    return;
}