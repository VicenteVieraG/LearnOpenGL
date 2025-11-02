#pragma once

#include <string>
#include <glbinding/gl/gl.h>

#include <shader.hpp>

namespace shader {
    class Program {
        private:
            gl::GLuint ID;
        public:
            Program();

            void attachShader(const Shader& shader) const;
            void linkProgram() const;
    };
};