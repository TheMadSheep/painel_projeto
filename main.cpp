#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//rgb(39,0,68) rgb(234,206,255)rgb(251,245,255)rgb(128,0,225)
//rgb(16,49,59) rgb(40,125,150) rgb(53,165,198) rgb(221,240,246) 
// rgb(40,125,150) complementar rgb(215,130,101)
// rgb(40,125,150)analogos rgb(16,49,59) e rgb(53,165,198)

const unsigned int largura_janela = 800;
const unsigned int altura_janela = 600;

void framebuffer_size_callback(GLFWwindow* janela, int largura, int altura) {
    glViewport(0, 0, largura, altura);
}

int main() {
    // Inicializar GLFW
    if (!glfwInit()) {
        std::cout << "Falha ao inicializar o GLFW!!!" << std::endl;
        return -1;
    }

    // Configurações
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(largura_janela, altura_janela, "Painel", nullptr, nullptr);
    if (!window) {
        std::cout << "Falha ao criar a janela!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // Inicializar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // -------- Variáveis do layout ---------
    static float left_width = 300.0f;
    static float top_height = 300.0f;
    static float splitter_size = 6.0f;
    // ---------------------------------------


    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Nova frame do ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // ==========================
        // JANELA PRINCIPAL INVISÍVEL
        // ==========================
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::SetNextWindowSize(io.DisplaySize);

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoBackground;

        ImGui::Begin("MainWindow", nullptr, flags);

        ImVec2 win_size = ImGui::GetWindowSize();

        float right_width  = win_size.x - left_width - splitter_size;
        float bottom_height = win_size.y - top_height - splitter_size;


        // =======================================
        //          SPLITTER HORIZONTAL
        // =======================================
        ImGui::SetCursorPos(ImVec2(0, top_height));
        ImGui::InvisibleButton("splitter_h", ImVec2(win_size.x, splitter_size));

        bool hovered_h = ImGui::IsItemHovered();
        bool active_h  = ImGui::IsItemActive();

        // muda o cursor quando passar por cima
        if (hovered_h || active_h)
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);

        if (active_h) {
            top_height += ImGui::GetIO().MouseDelta.y;
            if (top_height < 100) top_height = 100;
            if (top_height > win_size.y - 100) top_height = win_size.y - 100;
        }

        // desenhar a barra visível
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetItemRectMin(), ImGui::GetItemRectMax(),
            IM_COL32(16, 49, 59, 255)   //rgb(16,49,59) rgb(221,240,246)
        );


        // =======================================
        //            SPLITTER VERTICAL
        // =======================================
        ImGui::SetCursorPos(ImVec2(left_width, 0));
        ImGui::InvisibleButton("splitter_v", ImVec2(splitter_size, top_height));

        bool hovered_v = ImGui::IsItemHovered();
        bool active_v  = ImGui::IsItemActive();

        // muda o cursor quando passar por cima
        if (hovered_v || active_v)
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        if (active_v) {
            left_width += ImGui::GetIO().MouseDelta.x;
            if (left_width < 150) left_width = 150;
            if (left_width > win_size.x - 150) left_width = win_size.x - 150;
        }

        // desenhar a barra visível
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetItemRectMin(), ImGui::GetItemRectMax(),
            IM_COL32(16, 49, 59, 255)   //rgb(16,49,59) rgb(221,240,246)
        );


        // ===============================
        //       PAINEL ESQUERDO
        // ===============================
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::BeginChild("PainelEsquerdo", ImVec2(left_width, top_height), true);

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(215,130,101, 255)); // vermelho

        ImGui::Text("Ferramentas");

        ImGui::PopStyleColor(); // volta à cor original

        ImGui::Button("Mover");
        ImGui::Button("Rotacionar");
        ImGui::Button("Escalar");

        

        ImGui::EndChild();


        // ===============================
        //       PAINEL DIREITO
        // ===============================
        ImGui::SetCursorPos(ImVec2(left_width + splitter_size, 0));
        ImGui::BeginChild("PainelDireito", ImVec2(right_width, top_height), true);

        static float intensidade = 1.0f;
        static bool ativo = true;
        

        ImGui::Text("Propriedades");
        ImGui::SliderFloat("Intensidade", &intensidade, 0, 10);
        ImGui::Checkbox("Ativo", &ativo);

        ImGui::EndChild();


        // ===============================
        //          CONSOLE
        // ===============================
        ImGui::SetCursorPos(ImVec2(0, top_height + splitter_size));
        ImGui::BeginChild("Console", ImVec2(win_size.x, bottom_height), true);

        static char cmd[128] = "";

        ImGui::Text("Console");
        ImGui::Separator();
        ImGui::InputText("Comando", cmd, IM_ARRAYSIZE(cmd));

        if (ImGui::Button("Executar")) {
            std::cout << "> " << cmd << std::endl;
        }

        ImGui::EndChild();


        ImGui::End(); // Main window invisível


        // Renderizar, 
        ImGui::Render();
        glViewport(0, 0, io.DisplaySize.x, io.DisplaySize.y);
        glClearColor(40/2/255.0f,125/2/255.0f,150/2/255.0f,1.0f); //cor de fundo rgb(20,60,75)
        // o correto seria (45/255.0f,171/255.0f,131/255.0f,1.0f)
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Finalizar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
