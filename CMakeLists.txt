cmake_minimum_required(VERSION 3.28.3)

# Definir o nome do projeto
project(Painel)

# Procurar pela instalação do GLFW
find_package(glfw3 REQUIRED)

# Procurar pela instalação do OpenGL (geralmente disponível por padrão)
find_package(OpenGL REQUIRED)

# Criar o executável 'painel' com os arquivos fonte
add_executable(painel main.cpp src/matematica.cpp)

# Incluir diretórios de cabeçalhos
target_include_directories(painel PRIVATE include)

# Incluir o diretório do GLFW
target_link_libraries(painel PRIVATE glfw)

# Incluir a biblioteca OpenGL
target_link_libraries(painel PRIVATE OpenGL::GL)
