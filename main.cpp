#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
//#include "shader_s.h"


#include "Camera.h"
#include "Model.h"

#include <iostream>
#include "RaniPok.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(59.0f, 24.0f, 59.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

RaniPokhari rani;

int main() {
      // glfw: initialize and configure
      // ------------------------------
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

      // glfw window creation
      // --------------------
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

      // tell GLFW to capture our mouse
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      // glad: load all OpenGL function pointers
      // ---------------------------------------
      if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
      }

      // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
      stbi_set_flip_vertically_on_load(true);

      // configure global opengl state
      // -----------------------------


//      glEnable(GL_DEPTH_TEST);


//      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//      glEnable(GL_BLEND);

//      glEnable(GL_DEPTH_TEST);
//      glDepthFunc(GL_ALWAYS);
//      glAlphaFunc(GL_LESS,0.2);

      rani.loadModels();
      rani.loadShaders();
//////////////////////


//      // build and compile shaders
//      // -------------------------
//      Shader ourShader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.frag");
//      Shader ourShader2("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.frag");
//      Shader waterShader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.frag");
//      Shader lightShader("/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.vert", "/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.frag");
//
//      Shader sunlight("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.frag");
//
//      // load models
//      // -----------
////      Model ourModel("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
//      Model ourModel("/home/cool/CLionProjects/RaniPokhari/rani/main_temple.obj");
//      Model wall("/home/cool/CLionProjects/RaniPokhari/rani/walls.obj");
//      Model ghantaghar("/home/cool/CLionProjects/RaniPokhari/rani/ghantaghar.obj");
//      Model water("/home/cool/CLionProjects/RaniPokhari/rani/water.obj");
//      Model stairs("/home/cool/CLionProjects/RaniPokhari/rani/stairs.obj");
//      Model light("/home/cool/CLionProjects/RaniPokhari/rani/lights_and_bars.obj");
//
//
//
//
//
//      Model ourModel2("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
//

/////////////////////////////////
      // draw in wireframe
      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

      // render loop
      // -----------
      while (!glfwWindowShouldClose(window)) {
            // per-frame time logic
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = (currentFrame - lastFrame) * 5;
//            std::cout << "time  " << deltaTime << std::endl;
            lastFrame = currentFrame;

            // input
            // -----
            processInput(window);

            // render
            // ------
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            rani.applyLighting();

            rani.Draw();



//            // don't forget to enable shader before setting uniforms
//            ourShader.use();
//
//            // view/projection transformations
//            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
//            glm::mat4 view = camera.GetViewMatrix();
//
//            ourShader.setMat4("projection", projection);
//            ourShader.setMat4("view", view);
//
//
//
//            // render the loaded model
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//
//            glm::mat4 model2 = glm::mat4(1.0f);
//
////
////            glm::mat4 theMatrix;
////            theMatrix[0] = glm::vec4(1.0, 0.0, 0.0,0.0f);
////            theMatrix[1] = glm::vec4(0.0, -1.0, 0.0,0.0f);
////            theMatrix[2] = glm::vec4(0.0, 0.0, 1.0,0.0f);
////            theMatrix[3] = glm::vec4(0.0, 0.0, 0.0,1.0f);
////
////            glm::mat4 m=model2*theMatrix;
//
//
//            ourShader.setMat4("model", model);
//
//
//
//// Draw water
//            waterShader.use();
//            waterShader.setMat4("projection", projection);
//            waterShader.setMat4("view", view);
//
//            glm::mat4 waterModel = glm::mat4(1.0f);
//
//            waterModel = glm::translate(waterModel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//            waterModel = glm::scale(waterModel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//            waterShader.setMat4("model", waterModel);
//            waterShader.setFloat("deltatime", glm::sin(currentFrame));
//
//
//
//            water.Draw(waterShader);
//
//
//
//         //Draw reflection
//
//
//            ourShader2.use();
//            ourShader2.setMat4("projection", projection);
//            ourShader2.setMat4("view", view);
//
//            model2 = glm::translate(model2, glm::vec3(0.0f, -10.0f, 0.0f)); // translate it down so it's at the center of the scene
//            model2 = glm::scale(model2, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//            ourShader2.setMat4("model", model2);
//
//
//            ourModel2.Draw(ourShader2);
//
//            //Draw temple,bridge wall, and ghantaghar
//            ourShader.use();
//
//            ghantaghar.Draw(ourShader);
//
//            wall.Draw(ourShader);
//
//            stairs.Draw(ourShader);
//            ourModel.Draw(ourShader);
////
//
//
//            // Draw light sources
//
//            glm::mat4 lightModel = glm::mat4(1.0f);
//
//            sunlight.use();
//            sunlight.setMat4("projection", projection);
//            sunlight.setMat4("view", view);
//
//            lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//            lightModel = glm::scale(lightModel, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//            sunlight.setMat4("model", lightModel);
//
//
//            light.Draw(sunlight);





            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
      }

      // glfw: terminate, clearing all previously allocated GLFW resources.
      // ------------------------------------------------------------------
      glfwTerminate();
      return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
      if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            rani.camera.ProcessKeyboard(FORWARD, deltaTime);
      if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            rani.camera.ProcessKeyboard(BACKWARD, deltaTime);
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            rani.camera.ProcessKeyboard(LEFT, deltaTime);
      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            rani.camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
      // make sure the viewport matches the new window dimensions; note that width and
      // height will be significantly larger than specified on retina displays.
      glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
      rani.camera.ProcessMouseScroll(yoffset);
}

