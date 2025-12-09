#include <GLFW/glfw3.h>
#include <filesystem>
#include <opencv2/opencv.hpp>

void loadIcon(GLFWwindow *window) {
  cv::Mat icon = cv::imread("icon.png", cv::IMREAD_UNCHANGED);
  cv::cvtColor(icon, icon, cv::COLOR_BGR2RGBA);

  GLFWimage images[1];
  images[0].pixels = icon.data;
  images[0].width = icon.cols;
  images[0].height = icon.rows;
  glfwSetWindowIcon(window, 1, images);
}

void cvToGl(GLuint *texture, cv::Mat *image) {
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->cols, image->rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
}

cv::Mat loadImage(const std::filesystem::path &path) {
  cv::Mat image = cv::imread(path.string().c_str(), cv::IMREAD_UNCHANGED);
  if (image.channels() == 3)
    cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);
  else if (image.channels() == 1)
    cv::cvtColor(image, image, cv::COLOR_GRAY2RGBA);
  return image;
}
