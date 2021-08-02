//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_m.h"
////#include "shader_s.h"
//
//
//#include "Camera.h"
//#include "Model.h"
//
//#include <iostream>
//
//class RaniPokhari
//{
//public:
//
//    const unsigned int SCR_WIDTH = 1000;
//    const unsigned int SCR_HEIGHT = 900;
//
//    Shader ourShader;
//    Model ourModel;
//    Camera camera;
//    void loadModels();
//    void loadShaders();
//    void Draw();
//
//};
//
//void RaniPokhari::loadModels()
//{
////      /      Model ourModel("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
//      camera=Camera(glm::vec3(59.0f, 24.0f, 59.0f));
//
//      ourModel=Model("/home/cool/CLionProjects/RaniPokhari/rani/main_temple.obj");
//      Model wall("/home/cool/CLionProjects/RaniPokhari/rani/walls.obj");
//      Model ghantaghar("/home/cool/CLionProjects/RaniPokhari/rani/ghantaghar.obj");
//      Model water("/home/cool/CLionProjects/RaniPokhari/rani/water.obj");
//      Model stairs("/home/cool/CLionProjects/RaniPokhari/rani/stairs.obj");
//      Model light("/home/cool/CLionProjects/RaniPokhari/rani/lights_and_bars.obj");
//
//      Model ourModel2("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
//
//};
//void RaniPokhari::loadShaders() {
//      // Read and compile all shaders
//      ourShader=Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.frag");
//      Shader ourShader2("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.frag");
//      Shader waterShader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.frag");
//      Shader lightShader("/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.vert", "/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.frag");
//
//      Shader sunlight("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.frag");
//
//};
//
//void RaniPokhari::Draw() {
//      ourShader.use();
//
//      // view/projection transformations
//      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
//      glm::mat4 view = camera.GetViewMatrix();
//
//      ourShader.setMat4("projection", projection);
//      ourShader.setMat4("view", view);
//
//
//
//      // render the loaded model
//      glm::mat4 model = glm::mat4(1.0f);
//      model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//      model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
//
//      glm::mat4 model2 = glm::mat4(1.0f);
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
//      ourShader.setMat4("model", model);
//      //Draw temple,bridge wall, and ghantaghar
//      ourShader.use();
//      ourModel.Draw(ourShader);
//
//}
//
