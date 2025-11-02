#include <iostream>
#include <stdexcept>

#include <glbinding/gl/gl.h>

#include <shader.hpp>
#include <shaderProgram.hpp>

namespace shader {
    Program::Program() {
        try {
            if(this->ID = gl::glCreateProgram(); this->ID == 0)
                throw std::runtime_error("Failed to create shader program");
        }catch(const std::runtime_error& e) {
            std::cerr<<"--[Error]: "<<e.what()<<std::endl;
        }
    }

    void Program::attachShader(const Shader& shader) const {
        auto& [shaderID] = shader.getID();

        gl::glAttachShader(this->ID, shaderID);
        return;
    }

    void Program::linkProgram() const {
        gl::glLinkProgram(this->ID);

        gl::GLint success;
        gl::glGetProgramiv(this->ID, gl::GL_LINK_STATUS, &success);
        if(!success){
            char log[512];
            gl::glGetProgramInfoLog(this->ID, sizeof(log), nullptr, log);
            std::cerr
                <<"--[Error]: Program Linking failed"<<"\n"
                <<"[Log]: "<<log<<std::endl;
            return;
        }
    }
};