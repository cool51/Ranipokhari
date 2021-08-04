#include <GLFW/glfw3.h>
#include "Camera.h"
#include "RaniPok.h"
#include "iostream"
class InputProcess{
public:
//    const unsigned int SCR_WIDTH = 1000;
//    const unsigned int SCR_HEIGHT = 900;
//    bool firstMouse = true;
//    float lastX = SCR_WIDTH / 2.0f;
//    float lastY = SCR_HEIGHT / 2.0f;
//    void mouse_callback(GLFWwindow *window,RaniPokhari *rani, double xpos=0, double ypos=0);
//
//    void scroll_callback(GLFWwindow *window,RaniPokhari *rani, double xoffset, double yoffset);

    void processInput(GLFWwindow *window,Camera *camera,RaniPokhari *rani);
//    void mouseInput(GLFWwindow *window,RaniPokhari *rani);

};
//void InputProcess::mouseInput(GLFWwindow *window,RaniPokhari *rani) {
////      glfwSetCursorPosCallback(window,mouse_callback(window,rani));
////      glfwSetScrollCallback(window, scroll_callback(window,rani,0,0));
//}
void InputProcess::processInput(GLFWwindow *window, Camera *camera,RaniPokhari *rani) {
      float speed=0.2;
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            rani->camera.ProcessKeyboard(FORWARD, speed);
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            rani->camera.ProcessKeyboard(BACKWARD, speed);
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            rani->camera.ProcessKeyboard(LEFT, speed);
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            rani->camera.ProcessKeyboard(RIGHT, speed);


}



//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void InputProcess:: mouse_callback(GLFWwindow *window,RaniPokhari *rani ,double xpos=0, double ypos=0) {
//      if (firstMouse) {
//            lastX = xpos;
//            lastY = ypos;
//            firstMouse = false;
//      }
//
//      float xoffset = xpos - lastX;
//      float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//      lastX = xpos;
//      lastY = ypos;
//
//      rani->camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void InputProcess::scroll_callback(GLFWwindow *window,RaniPokhari *rani, double xoffset=0, double yoffset=0) {
//      rani->camera.ProcessMouseScroll(yoffset);
//}
