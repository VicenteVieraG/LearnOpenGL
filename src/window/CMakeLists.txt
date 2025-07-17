add_library(${WINDOW} STATIC window.cpp)

target_link_libraries(${WINDOW}
    PRIVATE glfw
    PRIVATE glbinding::glbinding
    PRIVATE glbinding::glbinding-aux
)