#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Camera.h"
#include <iostream>
#include "RaniPok.h"
#include "inputHandle.h"
#include "skybox.h"


void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);


const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 700;

// camera
Camera camera(glm::vec3(59.0f, 24.0f, 59.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

RaniPokhari rani;
InputProcess input;
Skybox skybox;
int main() {
      // initialize glfw

      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

      // create window

      GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ranipokhari", NULL, NULL);
      if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
      }
      glfwMakeContextCurrent(window);
      glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
      glfwSetCursorPosCallback(window, mouse_callback);
      glfwSetScrollCallback(window, scroll_callback);

      // moue event handling
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      // error handle glad

      if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
      }


//      stbi_set_flip_vertically_on_load(true);


//load models and complile shaders

      rani.loadModels();
      rani.loadShaders();


      skybox.loadSkybox();



      // render loop


      float lighttime=0;
      while (!glfwWindowShouldClose(window)) {

            float currentFrame = glfwGetTime();
            deltaTime = (currentFrame - lastFrame) * 5;
            lastFrame = currentFrame;


//            handle keyboard events
            input.processInput(window,&camera,&rani);

            // render screen

            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            //Apply lighting

            rani.applyDayLighting((sin((pow(currentFrame,0.7)))));


            float skytime=(sin((pow(currentFrame,0.7))));

            //Draw skybix
            skybox.drawSkybox(skytime);

            // Draw model
            rani.Draw();








            // swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      // close  window and delete all processes

      glfwTerminate();
      return 0;
}



// handle window resize

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

      glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
      if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
      }

      float xoffset = xpos - lastX;
      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

      lastX = xpos;
      lastY = ypos;

      rani.camera.ProcessMouseMovement(xoffset, yoffset);
      skybox.camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
      rani.camera.ProcessMouseScroll(yoffset);
      skybox.camera.ProcessMouseScroll(yoffset);

}

