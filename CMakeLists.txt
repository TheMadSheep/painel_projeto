cmake_minimum_required(VERSION 3.28.3)

# Nome do projeto
project(Painel)

set(CMAKE_CXX_STANDARD 17)

# Procurar por dependências
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Diretórios do ImGui
include_directories(
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

# Fontes do ImGui
set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

# Criar o executável com todos os arquivos
add_executable(painel
    main.cpp
    src/matematica.cpp
    ${IMGUI_SOURCES}
)

# Incluir diretórios de cabeçalhos do seu projeto
target_include_directories(painel PRIVATE include)

# Linkar bibliotecas
target_link_libraries(painel
    PRIVATE
    glfw
    OpenGL::GL
    pthread
    X11
    dl
)
