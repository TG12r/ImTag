#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void holiii(){
  std::cout << "holaaa" << std::endl;
}

int main() {
  // Inicialización de GLFW
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = monitor ? glfwGetVideoMode(monitor) : nullptr;

  const int width = mode ? (mode->width / 2) : 1280;
  const int height = mode ? (mode->height / 2) : 720;

  //  Crear la ventana principal
  GLFWwindow *window =
      glfwCreateWindow(width, height, "Test ImTag", nullptr, nullptr);
  if (window == nullptr) {
    // Fallback en caso de que OpenGL 4.6 no esté soportado por el driver
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "Test ImTag", nullptr, nullptr);
  }
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  if (mode) {
    glfwSetWindowPos(window, (mode->width - width) / 2,
                     (mode->height - height) / 2);
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable V-Sync

  // 3. Inicializar GLAD (obligatorio antes de ImGui y funciones OpenGL)
  int version = gladLoadGL((GLADloadfunc)glfwGetProcAddress);
  if (version == 0) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 460");

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // Iniciar frame de ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Código ImTag

    // if(ImGui::Begin("")){

    //   ImGui::End();
    // }
    static bool varBoolCheck = false;
    static float volumen = 0.5f;
    static int nivel = 1;
    static char nombreUsuario[128] = "";


    
    // [ImTag] Contexto de viewport para unidades de medida
    const ImGuiViewport* __imtag_vp = ImGui::GetMainViewport();
    const float __imtag_vw = __imtag_vp->WorkSize.x;
    const float __imtag_vh = __imtag_vp->WorkSize.y;


ImGui::SetNextWindowPos(__imtag_vp->WorkPos);
ImGui::SetNextWindowSize(__imtag_vp->WorkSize);
ImGui::SetNextWindowViewport(__imtag_vp->ID);
ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
if (ImGui::Begin("Hola", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus)) {
    ImGui::PopStyleVar(3);

      ImGui::Text("Hola mundo");

      if (ImGui::Button("Click para saludar")){
holiii();
}


      ImGui::Separator();

      ImGui::Spacing();


      if (ImGui::Checkbox("ejemplo checkbox", &varBoolCheck)) {holiii();
}

      ImGui::Spacing();


      ImGui::SliderFloat("Volumen (float)", &volumen, 0.0f, 1.0f);

      ImGui::SliderInt("Nivel (int)", &nivel, 1, 10);

      ImGui::Spacing();

      ImGui::InputText("Tu Nombre", nombreUsuario, sizeof(nombreUsuario));


    }
else {
    ImGui::PopStyleVar(3);
}
ImGui::End();

    
    // Fin Código ImTag

    // ImGui::ShowDemoWindow();

    // Renderizado
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.12f, 0.12f, 0.14f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Soporte de múltiples ventanas / viewports independientes de ImGui Docking
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow *backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}