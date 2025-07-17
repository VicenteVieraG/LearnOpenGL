#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace glfw {
    class Window {
        private:
            unsigned int width;
            unsigned int height;
            std::string title;
            GLFWwindow* window;

            void initGLFW() const;
            void setWindowHints() const;
            void createWindow();
            void initGLbinding() const;
            void setCallbacks() const;
        public:
            Window() = default;
            ~Window() = default;
            Window(const std::string_view title, const unsigned int width, const unsigned int height);
    
            GLFWwindow*& getPtr();
        };
};