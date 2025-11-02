#pragma once

#include <string>
#include <tuple>
#include <glbinding/gl/gl.h>

namespace shader {
    class Shader {
        private:
            gl::GLuint ID;
            gl::GLenum type;
            std::string typeStr;
            std::string_view path;
            std::string source;

            const std::string loadShader(const std::string_view& shaderPath) const;
            void compileShader() const;
        public:
            Shader() = default;
            Shader(const gl::GLenum& type, const std::string_view path);
            Shader(Shader&&) = default;
            ~Shader();

            const std::tuple<gl::GLuint> getID() const noexcept;
    };
};