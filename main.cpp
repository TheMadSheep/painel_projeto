#include <GLFW/glfw3.h>
#include <iostream>

const unsigned int largura_janela = 800;
const unsigned int altura_janela = 600;

// Callback para redimensionar a janela
void framebuffer_size_callback(GLFWwindow* juanela, int largura, int altura){
    glViewport(0, 0, largura, altura);
}

int main() {
    // Inicializando o GLFW
    if (!glfwInit()) {
        std::cout << "Falha ao inicializar o GLFW!!!" << std::endl;
        return -1;
    }

    // Obtém o monitor primário (geralmente o monitor principal)
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    
    // Obtém as propriedades da tela (como a resolução)
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Configurações da janela
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Versão principal do OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // Versão secundária do OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Usando o perfil moderno do OpenGL
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);  // Ativar os controles de janela (minimizar, maximizar, fechar)

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Criando a janela (sem ser em tela cheia, mas ocupando toda a tela)
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Painel", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Falha ao criar a janela!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Faz a janela criada o contexto atual para renderização
    glfwMakeContextCurrent(window);

    // Configura o callback para redimensionamento da janela
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Loop principal da janela
    while (!glfwWindowShouldClose(window)) {
        // Processa eventos
        glfwPollEvents();

        // Limpa a tela com uma cor (RGB)
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);  // Define a cor de fundo (cyan-escuro)
        glClear(GL_COLOR_BUFFER_BIT);  // Limpa a tela

        // Troca os buffers (vai para o que foi desenhado)
        glfwSwapBuffers(window);
    }

    // Limpeza de recursos
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}
