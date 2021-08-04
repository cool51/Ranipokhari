//
// Created by cool on 7/31/21.
//

#ifndef RANIPOKHARI_RANIPOK_H
#define RANIPOKHARI_RANIPOK_H

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

class RaniPokhari {
public:
      float aR=0.5,aG=0.5,aB=0.5;
      float dR=0.5,dG=0.5,dB=0.5;
    const unsigned int SCR_WIDTH = 1000;
    const unsigned int SCR_HEIGHT = 900;

    Shader mainShader, reflectionShader, waterShader, lightShader, sunlight,sunShader;
    Model mainTemple, wall, ghantaghar, water, stairs, light, reflection,sun;
    Camera camera;

    RaniPokhari() {
    }

    void loadModels();

    void loadShaders();
    
    void applyLighting();
    void applyDayLighting(float time);
    glm::mat4 translate(float tx,float sy,float sz);

    void Draw();
    glm::mat4 scaling(float sx,float sy,float sz);

};

void RaniPokhari::loadModels() {
//      /      Model ourModel("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
      camera = Camera(glm::vec3(59.0f, 24.0f, 59.0f));

      mainTemple = Model("/home/cool/CLionProjects/RaniPokhari/rani/main_temple.obj");
      wall = Model("/home/cool/CLionProjects/RaniPokhari/rani/walls.obj");
      ghantaghar = Model("/home/cool/CLionProjects/RaniPokhari/rani/ghantaghar.obj");
      water = Model("/home/cool/CLionProjects/RaniPokhari/rani/water.obj");
      stairs = Model("/home/cool/CLionProjects/RaniPokhari/rani/stairs.obj");
      light = Model("/home/cool/CLionProjects/RaniPokhari/rani/lights_and_bars_without_sun.obj");
      reflection = Model("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
      sun=Model("/home/cool/CLionProjects/RaniPokhari/rani/sun_only.obj");

};

void RaniPokhari::loadShaders() {
      // Read and compile all shaders
      mainShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.vert",
                          "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/shader.frag");
      reflectionShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.vert",
                                "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/reflection.frag");
      waterShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.vert",
                           "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/water.frag");
//      Shader lightShader("/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.vert", "/home/cool/CLionProjects/LearnOpenglTut/Assets/Shaders/light.frag");
//
      sunlight = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.vert",
                        "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunlight.frag");
      sunShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunShader.vert",
                        "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/sunShader.frag");

};

void RaniPokhari::Draw() {
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                              500.0f);
      glm::mat4 view = camera.GetViewMatrix();



      //------     Draw water  ------------
      waterShader.use();
      waterShader.setMat4("projection", projection);
      waterShader.setMat4("view", view);
      glm::mat4 waterModel = glm::mat4(1.0f);
      waterModel = glm::translate(waterModel,glm::vec3(cos(glfwGetTime()),0.0, 0.0)); // translate it down so it's at the center of the scene
      waterModel = glm::scale(waterModel,
                              glm::vec3(1.0f, 1.0f, 1.0f));      // it's a bit too big for our scene, so scale it down
      waterShader.setMat4("model", waterModel);
//            waterShader.setFloat("deltatime", glm::sin(currentFrame));
      water.Draw(waterShader);

      //Draw reflection


      reflectionShader.use();
      reflectionShader.setMat4("projection", projection);
      reflectionShader.setMat4("view", view);
      glm::mat4 reflectionModel = glm::mat4(1.0f);

      reflectionModel = glm::translate(reflectionModel, glm::vec3(0.0f, -10.0f, 0.0f)); // translate it down so it's at the center of the scene
      reflectionModel = glm::scale(reflectionModel, glm::vec3(1.0f, 1.0f,1.0f));      // it's a bit too big for our scene, so scale it down
      reflectionShader.setMat4("model", reflectionModel);
      reflection.Draw(reflectionShader);




      glEnable(GL_DEPTH_TEST);

      //------     Draw temple,ghataghar,wall,stairs  ------------
      mainShader.use();
      // view/projection transformations
      mainShader.setMat4("projection", projection);
      mainShader.setMat4("view", view);
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model,glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//      model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));      // it's a bit too big for our scene, so scale it down
      model=scaling(1,1,1);
glm::mat4 model2 = glm::mat4(1.0f);
      mainShader.setMat4("model", model);

      mainShader.use();
      ghantaghar.Draw(mainShader);
      wall.Draw(mainShader);
      stairs.Draw(mainShader);
      mainTemple.Draw(mainShader);



      // ---------    Draw light sources   ---------

      glm::mat4 lightModel = glm::mat4(1.0f);
      sunlight.use();
      sunlight.setMat4("projection", projection);
      sunlight.setMat4("view", view);
      lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//      lightModel=translate(0,0,0);
lightModel = glm::scale(lightModel, glm::vec3(1.0f, 1.0f, 1.0f));      // it's a bit too big for our scene, so scale it down
      sunlight.setMat4("model", lightModel);
      light.Draw(sunlight);

      glm::mat4 sunModel = glm::mat4(1.0f);

      sunShader.use();
      sunShader.setMat4("projection", projection);
      sunShader.setMat4("view", view);
      float t=3.14*sin(pow(glfwGetTime(),0.7));
      sunModel = glm::rotate(sunModel,-t,glm::vec3(1.0)); // translate it down so it's at the center of the scene

//      sunModel = glm::translate(sunModel, glm::vec3(0.0f, -sin(pow(glfwGetTime(),0.7)*90), -sin(pow(glfwGetTime(),0.7))*90)); // translate it down so it's at the center of the scene
//      lightModel=translate(0,0,0);
      sunModel = glm::scale(sunModel, glm::vec3(1.0f, 1.0f, 1.0f));      // it's a bit too big for our scene, so scale it down
      sunShader.setMat4("model", sunModel);
      sunShader.setFloat("tim",glfwGetTime());

      sun.Draw(sunShader);

glDisable(GL_DEPTH_TEST);

}

void RaniPokhari::applyLighting() {
      float currentFrame = glfwGetTime();

      mainShader.use();
      mainShader.setVec3("viewPos", camera.Position);

      mainShader.setVec3("dirLight.direction", 100.0f, -34.0f, -0.3f);
      mainShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
      mainShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
      mainShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//
      mainShader.setVec3("pointLights[0].position", -61.34, 7.13, 109.8);
      mainShader.setVec3("pointLights[0].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[0].constant", 1.0f);
      mainShader.setFloat("pointLights[0].linear", 0.09);
      mainShader.setFloat("pointLights[0].quadratic", 0.032);
      // point light 2
      mainShader.setVec3("pointLights[1].position", -61,6, 10);
      mainShader.setVec3("pointLights[1].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[1].constant", 1.0f);
      mainShader.setFloat("pointLights[1].linear", 0.09);
      mainShader.setFloat("pointLights[1].quadratic", 0.032);
      // point light 3
      mainShader.setVec3("pointLights[2].position", 42,6,110);
      mainShader.setVec3("pointLights[2].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[2].constant", 1.0f);
      mainShader.setFloat("pointLights[2].linear", 0.09);
      mainShader.setFloat("pointLights[2].quadratic", 0.032);
      // point light 4
      mainShader.setVec3("pointLights[3].position", 41,6,10);
      mainShader.setVec3("pointLights[3].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[3].constant", 1.0f);
      mainShader.setFloat("pointLights[3].linear", 0.09);
      mainShader.setFloat("pointLights[3].quadratic", 0.032);

      //lamp ghntaghar
      mainShader.setVec3("pointLights[4].position", -97,53,35);
      mainShader.setVec3("pointLights[4].ambient", 1.0f, 1.0f, 0.0f);
      mainShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[4].constant", 1.0f);
      mainShader.setFloat("pointLights[4].linear", 0.09);
      mainShader.setFloat("pointLights[4].quadratic", 0.032);

      mainShader.setVec3("pointLights[6].position", 9,9,56);
      mainShader.setVec3("pointLights[6].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[6].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[6].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[6].constant", 1.0f);
      mainShader.setFloat("pointLights[6].linear", 0.09);
      mainShader.setFloat("pointLights[6].quadratic", 0.032);
//moon
      mainShader.setVec3("pointLights[5].position", -100,34,38);
      mainShader.setVec3("pointLights[5].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[5].constant", 1.0f);
      mainShader.setFloat("pointLights[5].linear", 0.09);
      mainShader.setFloat("pointLights[5].quadratic", 0.032);

      mainShader.setVec3("light.direction", -currentFrame, -currentFrame, -currentFrame);
      mainShader.setVec3("viewPos", camera.Position);

//            // light properties
             mainShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
            mainShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
            mainShader.setVec3("light.specular", 0.50f, 0.50f, 0.50f);

//       material properties
            mainShader.setFloat("material.shininess", 32.0f);
      mainShader.setFloat("material.diffuse", 0.5f);
      mainShader.setFloat("material.specular", 0.30f);

      // view/projection transformations
      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
      glm::mat4 view = camera.GetViewMatrix();

      mainShader.setMat4("projection", projection);
      mainShader.setMat4("view", view);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      mainShader.setMat4("model", model);
//      mainTemple.Draw(mainShader);


// lighting for water

      waterShader.use();
      waterShader.setVec3("viewPos", camera.Position);
//lamp1
      waterShader.setVec3("dirLight.direction", -100.0f, -34.0f, -0.3f);
      waterShader.setVec3("dirLight.ambient", 0.0f, 0.0f, 0.0f);
      waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
      waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//lamp2
      waterShader.setVec3("pointLights[0].position", -61.34, 7.13, 109.8);
      waterShader.setVec3("pointLights[0].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[0].constant", 1.0f);
      waterShader.setFloat("pointLights[0].linear", 0.09);
      waterShader.setFloat("pointLights[0].quadratic", 0.032);
      // lamp3
      waterShader.setVec3("pointLights[1].position", -61.0,6.0f, 10.0f);
      waterShader.setVec3("pointLights[1].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[1].constant", 1.0f);
      waterShader.setFloat("pointLights[1].linear", 0.09);
      waterShader.setFloat("pointLights[1].quadratic", 0.032);
      // lamp 4
      waterShader.setVec3("pointLights[2].position", 42,6,110);
      waterShader.setVec3("pointLights[2].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[2].constant", 1.0f);
      waterShader.setFloat("pointLights[2].linear", 0.09);
      waterShader.setFloat("pointLights[2].quadratic", 0.032);
      // point light 4
      waterShader.setVec3("pointLights[3].position", 41,6,10);
      waterShader.setVec3("pointLights[3].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[3].constant", 1.0f);
      waterShader.setFloat("pointLights[3].linear", 0.09);
      waterShader.setFloat("pointLights[3].quadratic", 0.032);
//lamp ghntaghar
      waterShader.setVec3("pointLights[4].position", -100,34,38);
      waterShader.setVec3("pointLights[4].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[4].constant", 1.0f);
      waterShader.setFloat("pointLights[4].linear", 0.09);
      waterShader.setFloat("pointLights[4].quadratic", 0.032);

      //moon
      waterShader.setVec3("pointLights[6].position", -97,53,35);
      waterShader.setVec3("pointLights[6].ambient", 1.0f, 0.0f, 0.0f);
      waterShader.setVec3("pointLights[6].diffuse", 1.0f, 0.0f, 0.0f);
      waterShader.setVec3("pointLights[6].specular", 1.0f, 0.0f, 0.0f);
      waterShader.setFloat("pointLights[6].constant", 1.0f);
      waterShader.setFloat("pointLights[6].linear", 0.09);
      waterShader.setFloat("pointLights[6].quadratic", 0.032);

      waterShader.setVec3("pointLights[5].position", -100,34,38);
      waterShader.setVec3("pointLights[5].ambient", 1.0f, 1.0f, 1.0f);
      waterShader.setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[5].constant", 1.0f);
      waterShader.setFloat("pointLights[5].linear", 0.09);
      waterShader.setFloat("pointLights[5].quadratic", 0.032);

      waterShader.setVec3("light.direction", -currentFrame, -currentFrame, -currentFrame);
      waterShader.setVec3("viewPos", camera.Position);

//            // light properties
      waterShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
      waterShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
      waterShader.setVec3("light.specular", 0.50f, 0.50f, 0.50f);

//       material properties
      waterShader.setFloat("material.shininess", 32.0f);
      waterShader.setFloat("material.diffuse", 0.5f);
      waterShader.setFloat("material.specular", 0.30f);

//      // view/projection transformations
//      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
//      glm::mat4 view = camera.GetViewMatrix();
//
//      waterShader.setMat4("projection", projection);
//      waterShader.setMat4("view", view);
//
//      // world transformation
//      glm::mat4 model = glm::mat4(1.0f);
//      waterShader.setMat4("model", model);
}

void RaniPokhari::applyDayLighting(float time) {


      float currentFrame = glfwGetTime();

      mainShader.use();
      mainShader.setVec3("viewPos", camera.Position);

      mainShader.setVec3("dirLight.direction", 100.0f, -34.0f, -0.3f);
      if(time>=0.6)
      {
            mainShader.setVec3("dirLight.ambient", 0.6,0.6,0.6);

      }
      else if(time<=0.001)
      {
            mainShader.setVec3("dirLight.ambient", 0.001,0.001,0.001);
      }
      else
      {
            mainShader.setVec3("dirLight.ambient", time,time,time);
      }

      mainShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
      mainShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//
      mainShader.setVec3("pointLights[0].position", -61.34, 7.13, 109.8);
      mainShader.setVec3("pointLights[0].ambient", 0.0f, 0.0f, 0.0f);
      mainShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[0].constant", 1.0f);
      mainShader.setFloat("pointLights[0].linear", 0.09);
      mainShader.setFloat("pointLights[0].quadratic", 0.032);
      // point light 2
      mainShader.setVec3("pointLights[1].position", -61,6, 10);
      mainShader.setVec3("pointLights[1].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[1].constant", 1.0f);
      mainShader.setFloat("pointLights[1].linear", 0.09);
      mainShader.setFloat("pointLights[1].quadratic", 0.032);
      // point light 3
      mainShader.setVec3("pointLights[2].position", 42,6,110);
      mainShader.setVec3("pointLights[2].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[2].constant", 1.0f);
      mainShader.setFloat("pointLights[2].linear", 0.09);
      mainShader.setFloat("pointLights[2].quadratic", 0.032);
      // point light 4
      mainShader.setVec3("pointLights[3].position", 41,6,10);
      mainShader.setVec3("pointLights[3].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[3].constant", 1.0f);
      mainShader.setFloat("pointLights[3].linear", 0.09);
      mainShader.setFloat("pointLights[3].quadratic", 0.032);

      //lamp ghntaghar
      mainShader.setVec3("pointLights[4].position", -97,53,35);
      mainShader.setVec3("pointLights[4].ambient", 1.0f, 1.0f, 0.0f);
      mainShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[4].constant", 1.0f);
      mainShader.setFloat("pointLights[4].linear", 0.09);
      mainShader.setFloat("pointLights[4].quadratic", 0.032);

      mainShader.setVec3("pointLights[6].position", 9,9,56);
      mainShader.setVec3("pointLights[6].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[6].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[6].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[6].constant", 1.0f);
      mainShader.setFloat("pointLights[6].linear", 0.09);
      mainShader.setFloat("pointLights[6].quadratic", 0.032);
//moon
      mainShader.setVec3("pointLights[5].position", -100,34,38);
      mainShader.setVec3("pointLights[5].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[5].constant", 1.0f);
      mainShader.setFloat("pointLights[5].linear", 0.09);
      mainShader.setFloat("pointLights[5].quadratic", 0.032);

      mainShader.setVec3("light.direction", -currentFrame, -currentFrame, -currentFrame);
      mainShader.setVec3("viewPos", camera.Position);

//            // light properties
      mainShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
      mainShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
      mainShader.setVec3("light.specular", 0.50f, 0.50f, 0.50f);

//       material properties
      mainShader.setFloat("material.shininess", 32.0f);
      mainShader.setFloat("material.diffuse", 0.5f);
      mainShader.setFloat("material.specular", 0.30f);

      // view/projection transformations
      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
      glm::mat4 view = camera.GetViewMatrix();

      mainShader.setMat4("projection", projection);
      mainShader.setMat4("view", view);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      mainShader.setMat4("model", model);
//      mainTemple.Draw(mainShader);


// lighting for water

      waterShader.use();
      waterShader.setVec3("viewPos", camera.Position);
//lamp1
      waterShader.setVec3("dirLight.direction", 100.0f, -34.0f, -0.3f);

      if(time>=0.6)
      {
            waterShader.setVec3("dirLight.ambient", 0.6,0.6,0.6);
//            waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//            waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//
      }
      else if(time<=0.001)
      {
            waterShader.setVec3("dirLight.ambient", 0.001,0.001,0.001);
//            waterShader.setVec3("dirLight.diffuse", 0.001,0.001,0.001);
//            waterShader.setVec3("dirLight.specular", 0.001,0.001,0.001);


      }
      else
      {
            waterShader.setVec3("dirLight.ambient", time,time,time);
            waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
      }
      
//      waterShader.setVec3("dirLight.ambient", 0.50f, 0.50f, 0.50f);
      waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
      waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//lamp2
      waterShader.setVec3("pointLights[0].position", -61.34, 7.13, 109.8);
      waterShader.setVec3("pointLights[0].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[0].constant", 1.0f);
      waterShader.setFloat("pointLights[0].linear", 0.09);
      waterShader.setFloat("pointLights[0].quadratic", 0.032);
      // lamp3
      waterShader.setVec3("pointLights[1].position", -61.0,6.0f, 10.0f);
      waterShader.setVec3("pointLights[1].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[1].constant", 1.0f);
      waterShader.setFloat("pointLights[1].linear", 0.09);
      waterShader.setFloat("pointLights[1].quadratic", 0.032);
      // lamp 4
      waterShader.setVec3("pointLights[2].position", 42,6,110);
      waterShader.setVec3("pointLights[2].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[2].constant", 1.0f);
      waterShader.setFloat("pointLights[2].linear", 0.09);
      waterShader.setFloat("pointLights[2].quadratic", 0.032);
      // point light 4
      waterShader.setVec3("pointLights[3].position", 41,6,10);
      waterShader.setVec3("pointLights[3].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[3].constant", 1.0f);
      waterShader.setFloat("pointLights[3].linear", 0.09);
      waterShader.setFloat("pointLights[3].quadratic", 0.032);
//lamp ghntaghar
      waterShader.setVec3("pointLights[4].position", -100,34,38);
      waterShader.setVec3("pointLights[4].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[4].constant", 1.0f);
      waterShader.setFloat("pointLights[4].linear", 0.09);
      waterShader.setFloat("pointLights[4].quadratic", 0.032);

      //moon
      waterShader.setVec3("pointLights[6].position", -97,53,35);
      waterShader.setVec3("pointLights[6].ambient", 1.0f, 0.0f, 0.0f);
      waterShader.setVec3("pointLights[6].diffuse", 1.0f, 0.0f, 0.0f);
      waterShader.setVec3("pointLights[6].specular", 1.0f, 0.0f, 0.0f);
      waterShader.setFloat("pointLights[6].constant", 1.0f);
      waterShader.setFloat("pointLights[6].linear", 0.09);
      waterShader.setFloat("pointLights[6].quadratic", 0.032);

      waterShader.setVec3("pointLights[5].position", -100,34,38);
      waterShader.setVec3("pointLights[5].ambient", 1.0f, 1.0f, 1.0f);
      waterShader.setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[5].constant", 1.0f);
      waterShader.setFloat("pointLights[5].linear", 0.09);
      waterShader.setFloat("pointLights[5].quadratic", 0.032);

      waterShader.setVec3("light.direction", -currentFrame, -currentFrame, -currentFrame);
      waterShader.setVec3("viewPos", camera.Position);

//            // light properties
      waterShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
      waterShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
      waterShader.setVec3("light.specular", 0.50f, 0.50f, 0.50f);

//       material properties
      waterShader.setFloat("material.shininess", 32.0f);
      waterShader.setFloat("material.diffuse", 0.5f);
      waterShader.setFloat("material.specular", 0.30f);
}

glm::mat4 RaniPokhari::scaling(float sx,float sy,float sz)
{
      glm::vec4 r1(sx,0,0,0);
      glm::vec4 r2(0,sy,0,0);
      glm::vec4 r3(0,0,sz,0);
      glm::vec4 r4(0,0,0,1);

      glm::mat4 scale(r1,r2,r3,r4);
      return scale;

}

glm::mat4 RaniPokhari::translate(float tx,float ty,float tz)
{
      glm::vec4 r1(1,0,0,tx);
      glm::vec4 r2(0,1,0,ty);
      glm::vec4 r3(0,0,1,tz);
      glm::vec4 r4(0,0,0,1);

      glm::mat4 translate(r1,r2,r3,r4);
      return translate;

}


#endif //RANIPOKHARI_RANIPOK_H
