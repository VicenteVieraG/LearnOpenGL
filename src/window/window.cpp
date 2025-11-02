#include <iostream>
#include <string>

#include <window.hpp>
#include <GLFW/glfw3.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/ContextInfo.h>

namespace glfw {
    Window::Window(const std::string_view title, const unsigned int width, const unsigned int height)
        : title(title), width(width), height(height), window(nullptr){
            this->initGLFW();
            this->setWindowHints();
            this->createWindow();
            this->initGLbinding();
            this->setCallbacks();
    }

    void Window::initGLFW() const {
        if(!glfwInit()) std::cerr<<"Error initializing GLFW"<<std::endl;
        return;
    }
    void Window::setWindowHints() const {
        glfwWindowHint(GLFW_RESIZABLE, true);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        return;
    }
    void Window::createWindow() {
        this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
        if(!this->window){
            std::cerr<<"Error creating GLFW Window"<<std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(this->window);
        return;
    }
    void Window::initGLbinding() const {
        glbinding::initialize(glfwGetProcAddress);

        std::cout<<"OpenGL Version: "<<glbinding::aux::ContextInfo::version().toString()<<std::endl;
        std::cout<<"OpenGL Vendor: "<<glbinding::aux::ContextInfo::vendor()<<std::endl;
        std::cout<<"OpenGL Renderer: "<<glbinding::aux::ContextInfo::renderer()<<std::endl;

        return;
    }
    void Window::setCallbacks() const {
        glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height) -> void {
            gl::glViewport(0, 0, width, height);
            return;
        });
    }

    GLFWwindow*& Window::getPtr() noexcept {
        return this->window;
    }

    Window::~Window(){
        if(this->window){
            glfwDestroyWindow(this->window);
            this->window = nullptr;
        }
    }
};