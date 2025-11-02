#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <config.hpp>

#include <window.hpp>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glbinding/Version.h>
#include <glbinding-aux/ContextInfo.h>

#include <geometry.hpp>

#define BLACK 0.0f, 0.0f, 0.0f, 1.0f
#define WHITE 1.0f, 1.0f, 1.0f, 1.0f

void gameLoop(glfw::Window& window);
void initGL();
const std::string loadShader(const std::string& filePath);
void createShader(const std::string& shaderPath, const gl::GLenum& shaderType);
const gl::GLuint compileShader(const gl::GLenum& shaderType, const std::string& shaderSource);

int main(void){
    std::cout<<project_name<<std::endl;
    std::cout<<project_version<<std::endl;
    std::cout<<"C++ Standard: "<<__cplusplus<<std::endl;

    glfw::Window window("LearOpenGL", 800, 600);
    initGL();
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

void initGL(){
    unsigned int VBO;
    unsigned int VAO;

    constexpr geom::Vertex vertices[3] = {
        {-0.5f, -0.5f, 0.0f},
        {0.5f, -0.5f, 0.0f},
        {0.0f,  0.5f, 0.0f}
    };

    gl::glGenBuffers(1, &VBO);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, VBO);
        gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(vertices), vertices, gl::GL_STATIC_DRAW);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
}

const std::string loadShader(const std::string& filePath){
    try {
        std::ifstream file(filePath);

        std::stringstream fileBuffer;
        fileBuffer<<file.rdbuf();

        return fileBuffer.str();
    }catch(const std::fstream::failure& e) {
        std::cerr<<"--[Error]: Could not load shader file: "<<filePath<<std::endl;
        std::cerr<<"[Exeption]: "<<e.what()<<std::endl;
        std::cerr<<"[Exeption Code]: "<<e.code()<<std::endl;
        return "";
    }
}

void createShader(const std::string& shaderPath, const gl::GLenum& shaderType){
    const gl::GLuint program = gl::glCreateProgram();

    const std::string shaderSource = loadShader(shaderPath);
    const gl::GLuint shader = compileShader(shaderType, shaderSource);

    gl::glAttachShader(program, shader);
    gl::glLinkProgram(program);

    gl::GLint success;
    gl::glGetProgramiv(program, gl::GL_LINK_STATUS, &success);
    if(!success){
        char log[512];
        gl::glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        std::cerr
            <<"--[Error]: Program linking failed"<<"\n"
            <<"[Log]: "<<log<<"\n"
            <<"[Shader Path]: "<<shaderPath<<std::endl;
        return;
    }

    gl::glDeleteShader(shader);
    return;
}

const gl::GLuint compileShader(const gl::GLenum& shaderType, const std::string& shaderSource){
    const gl::GLuint shader = gl::glCreateShader(shaderType);
    const gl::GLchar* source = shaderSource.c_str();

    gl::glShaderSource(shader, 1, &source, nullptr);
    gl::glCompileShader(shader);

    gl::GLint success;
    gl::glGetShaderiv(shader, gl::GL_COMPILE_STATUS, &success);
    if(!success){
        char log[512];
        gl::glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        
        std::string shaderTypeStr;
        switch(shaderType){
            case gl::GL_VERTEX_SHADER: shaderTypeStr = "Vertex Shader"; break;
            case gl::GL_FRAGMENT_SHADER: shaderTypeStr = "Fragment Shader"; break;
        };
        
        std::cerr
            <<"--[Error]: Shader compilation failed"<<"\n"
            <<"[Log]: "<<log<<"\n"
            <<"[Shader Type]: "<<shaderTypeStr<<std::endl;
        return 0;
    }

    return shader;
}