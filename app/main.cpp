#include <iostream>
#include <string>
#include <config.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/ContextInfo.h>

#define BLACK 0.0f, 0.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f, 1.0f

void initGLFW();
void initWindow(GLFWwindow*& window, const std::string& title, const unsigned int width, const unsigned int height);
void initGLbinding();
void glfwSetCallbacks(GLFWwindow*& window);
void gameLoop(GLFWwindow*& window);

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"C++ Standard: "<<__cplusplus<<std::endl;

    GLFWwindow* window = nullptr;
    const std::string TITLE = "LearOpenGL";
    const unsigned int WIDTH = 800;
    const unsigned int HEIGHT = 600;

    initGLFW();
    initWindow(window, TITLE, WIDTH, HEIGHT);
    initGLbinding();
    glfwSetCallbacks(window);
    gameLoop(window);

    return 0;
}

void initGLFW(){
    if(!glfwInit()) std::cerr<<"Error initializing GLFW"<<std::endl;

    return;
}

void initWindow(GLFWwindow*& window, const std::string& title, const unsigned int width, const unsigned int height){
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(!window){
        std::cerr<<"Error creating GLFW window"<<std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    return;
}

void initGLbinding(){
    glbinding::initialize(glfwGetProcAddress);

    std::cout<<"OpenGL Version: "<<glbinding::aux::ContextInfo::version().toString()<<std::endl;
    std::cout<<"OpenGL Vendor: "<<glbinding::aux::ContextInfo::vendor()<<std::endl;
    std::cout<<"OpenGL Renderer: "<<glbinding::aux::ContextInfo::renderer()<<std::endl;

    return;
}

void glfwSetCallbacks(GLFWwindow*& window){
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {
        gl::glViewport(0, 0, width, height);
    });

    return;
}

void gameLoop(GLFWwindow*& window){
    do{
        glfwPollEvents();

        gl::glClearColor(WHITE);
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }while(!glfwWindowShouldClose(window));

    glfwDestroyWindow(window);
    glfwTerminate();

    return;
}