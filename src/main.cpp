#include <GLFW/glfw3.h>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <opencv2/opencv.hpp>

int main() {
  glfwInit();
  GLFWwindow *window = glfwCreateWindow(800, 600, "TEST", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  int display_w, display_h;

  // cv::Mat icon = cv::imread("icon.png", cv::IMREAD_UNCHANGED);
  // cv::cvtColor(icon, icon, cv::COLOR_BGR2RGBA);

  // GLFWimage images[1];
  // images[0].pixels = icon.data;
  // images[0].width = icon.cols;
  // images[0].height = icon.rows;
  // glfwSetWindowIcon(window, 1, images);

  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 330 core");

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;

  cv::Mat source_image;

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, source_image.cols, source_image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, source_image.data);

  ImGuiViewport *viewport = ImGui::GetMainViewport();

  ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                  ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoDecoration;

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glfwGetFramebufferSize(window, &display_w, &display_h);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::SetNextWindowPos(viewport->Pos);

    ImGui::SetNextWindowSize(ImVec2{(float)display_w, (float)display_h});
    ImGui::Begin("#pscaler", 0, window_flags);
    ImGui::Text("Hello from ImGUI");
    ImGui::Image((ImTextureID)(intptr_t)texture, {source_image.cols / 2.f, source_image.rows / 2.f});
    ImGui::End();
    ImGui::Render();

    glViewport(0, 0, display_w, display_h);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
