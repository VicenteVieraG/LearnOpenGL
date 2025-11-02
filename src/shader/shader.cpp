#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <stdexcept>

#include <glbinding/gl/gl.h>

#include <shader.hpp>

namespace shader {
    Shader::Shader(const gl::GLenum& type, const std::string_view path)
    : type(type), path(path) {
        this->ID = gl::glCreateShader(this->type);
        this->source = this->loadShader(this->path);
        this->compileShader();

        switch(this->type){
            case gl::GL_VERTEX_SHADER: this->typeStr = "Vertex Shader"; break;
            case gl::GL_FRAGMENT_SHADER: this->typeStr = "Fragment Shader"; break;
            default: this->typeStr = "Invalid Shader Type";
        };
    }

    const std::string Shader::loadShader(const std::string_view& shaderPath) const {
        try {
            const std::ifstream shaderFile(shaderPath.data());

            std::stringstream fileBuffer;
            fileBuffer<<shaderFile.rdbuf();

            return fileBuffer.str();
        }catch(const std::fstream::failure& e){
            std::cerr<<"--[Error]: Could not load shader file: "<<shaderPath<<std::endl;
            std::cerr<<"[Exeption]: "<<e.what()<<std::endl;
            std::cerr<<"[Exeption Code]: "<<e.code()<<std::endl;
            return "";
        }
    }

    void Shader::compileShader() const {
        try {
            const gl::GLchar* shaderSource = this->source.c_str();

            gl::glShaderSource(this->ID, 1, &shaderSource, nullptr);
            gl::glCompileShader(this->ID);

            gl::GLint success;
            gl::glGetShaderiv(this->ID, gl::GL_COMPILE_STATUS, &success);

            if(!success) throw std::runtime_error("Error compiling shader.");
            else return;
        }catch(const std::runtime_error& e) {
            char log[512];
            gl::glGetShaderInfoLog(this->ID, sizeof(log), nullptr, log);

            std::cerr
                <<"--[Error]: Shader compilation failed"<<"\n"
                <<"[Exception]: "<<e.what()<<"\n"
                <<"[Log]: "<<log<<"\n"
                <<"[Shader Type]: "<<this->typeStr<<std::endl;
            return;
        }
    }

    const std::tuple<gl::GLuint> Shader::getID() const noexcept {
        return { this->ID };
    }

    Shader::~Shader(){
        gl::glDeleteShader(this->ID);
    }
};