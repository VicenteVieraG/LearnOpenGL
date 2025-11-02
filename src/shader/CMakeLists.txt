add_library(${SHADER} STATIC shader.cpp shaderProgram.cpp)

target_link_libraries(${SHADER}
    PRIVATE glbinding::glbinding
    PRIVATE glbinding::glbinding-aux
)