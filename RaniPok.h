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
#include "Math.h"
#include "Camera.h"
#include "Model.h"
#include "Algrothims.h"

#include <iostream>

class RaniPokhari {
public:
//      float aR=0.5,aG=0.5,aB=0.5;
//      float dR=0.5,dG=0.5,dB=0.5;
//      bool turnback=false;

    const unsigned int SCR_WIDTH = 1000;
    const unsigned int SCR_HEIGHT = 700;

    Shader mainShader, reflectionShader, waterShader, wireShader, sunlight,sunShader,vehicleShader;
    Model mainTemple, wall, ghantaghar, water, stairs, light, reflection,sun,boat1,boat2,boat3,wire,hour,minute,ground,trees,flowers,statue;
    Camera camera;

    RaniPokhari() {
    }

    void loadModels();
    void loadShaders();
/*
    void applyLighting();
*/
    void applyDayLighting(float time);
    void Draw();

};

void RaniPokhari::loadModels() {
//           Model ourModel("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
// Define initial view position of scene

      camera = Camera(glm::vec3(59.0f, 24.0f, 59.0f));

      mainTemple = Model("/home/cool/CLionProjects/RaniPokhari/rani/main_temple.obj");
      wall = Model("/home/cool/CLionProjects/RaniPokhari/rani/walls.obj");
      ghantaghar = Model("/home/cool/CLionProjects/RaniPokhari/rani/ghantaghar2.obj");
      water = Model("/home/cool/CLionProjects/RaniPokhari/rani/water.obj");
      stairs = Model("/home/cool/CLionProjects/RaniPokhari/rani/stairs.obj");
      light = Model("/home/cool/CLionProjects/RaniPokhari/rani/lights_and_bars_without_sun.obj");
      reflection = Model("/home/cool/CLionProjects/RaniPokhari/rani/begin_____.obj");
      sun=Model("/home/cool/CLionProjects/RaniPokhari/rani/sun_only.obj");
      boat1 = Model("/home/cool/CLionProjects/RaniPokhari/rani/boats_1.obj");
      boat2 = Model("/home/cool/CLionProjects/RaniPokhari/rani/boats_2.obj");
      boat3 = Model("/home/cool/CLionProjects/RaniPokhari/rani/boats_3.obj");
      hour = Model("/home/cool/CLionProjects/RaniPokhari/rani/hour_hand.obj");
      minute = Model("/home/cool/CLionProjects/RaniPokhari/rani/minute_hand.obj");
      trees = Model("/home/cool/CLionProjects/RaniPokhari/rani/trees.obj");
      flowers = Model("/home/cool/CLionProjects/RaniPokhari/rani/plants1.obj");
      statue = Model("/home/cool/CLionProjects/RaniPokhari/rani/sivalinga.obj");

      ground = Model("/home/cool/CLionProjects/RaniPokhari/rani/road_and_ground.obj");

//      wire = Model("/home/cool/CLionProjects/RaniPokhari/rani/wires.obj");



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

      vehicleShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/vehicleShader.vert",
                         "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/vehicleShader.frag");
      /*wireShader = Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/wireShader.vert",
                             "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/wireShader.frag");
*/

};

void RaniPokhari::Draw() {
      //Aplha blending to allow reflection on water
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);

/*      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                              500.0f);*/
      glm::mat4 projection = Algorithms::prespective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 500.0f);
      glm::mat4 view = camera.GetViewMatrix();



      //                  -------------------Draw water  ------------

      waterShader.use();
      waterShader.setMat4("projection", projection);
      waterShader.setMat4("view", view);
      glm::mat4 waterModel = glm::mat4(1.0f); // define modal matrix as identy matrix to perform other transforamtion in world coordinates
      waterModel = Algorithms::translate(waterModel,glm::vec3((sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*2, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*2)); // simulating water movement
      waterShader.setMat4("model", waterModel);
      water.Draw(waterShader);



      //                      ----------------Draw reflection---------------------

      reflectionShader.use();
      reflectionShader.setMat4("projection", projection);
      reflectionShader.setMat4("view", view);
      glm::mat4 reflectionModel = glm::mat4(1.0f);

     /* reflectionModel = Algorithms::translate(reflectionModel, glm::vec3(0.0f, -10.0f, 0.0f));
      reflectionModel = glm::scale(reflectionModel, glm::vec3(1.0f, 1.0f,1.0f));  */
      reflectionShader.setMat4("model", reflectionModel);
      reflection.Draw(reflectionShader);



      //   Enable depth test and disable alpha blending
      glEnable(GL_DEPTH_TEST);

      //                 ---------------------Draw temple,ghataghar,wall,stairs  ------------

      mainShader.use();
      mainShader.setMat4("projection", projection);
      mainShader.setMat4("view", view);
      glm::mat4 model = glm::mat4(1.0f);
      /*model = Algorithms::translate(model,glm::vec3(0.0f, 0.0f, 0.0f));*/
      mainShader.setMat4("model", model);


      mainShader.use();
      float cf = glfwGetTime()*2;
      glm::mat4 minuteModel = glm::mat4(1.0f);
      minuteModel = glm::translate(minuteModel,glm::vec3(0.0f, 40.0f, 35.0f)); // translate to origin
      minuteModel=glm::rotate(minuteModel,-(glm::radians(cf*60)),glm::vec3(1,0,0));//rotate clock hand
      minuteModel = glm::translate(minuteModel,glm::vec3(0.0f, -40.0f, -35.0f)); // translate back
      mainShader.setMat4("model", minuteModel);
      minute.Draw(mainShader);


      mainShader.use();
      glm::mat4 hourModel = glm::mat4(1.0f);
      hourModel = glm::translate(hourModel,glm::vec3(0.0f, 40.0f, 35.0f));
      hourModel=glm::rotate(hourModel,-(glm::radians(cf*20)),glm::vec3(1,0,0));
      hourModel = glm::translate(hourModel,glm::vec3(0.0f, -40.0f, -35.0f));
      mainShader.setMat4("model", hourModel);
      hour.Draw(mainShader);



      mainShader.use();
      glm::mat4 flowerModel = glm::mat4(1.0f);
      flowerModel = Algorithms::translate(   flowerModel,glm::vec3(50.0f, -3.0f, 65.0f));
      flowerModel = Algorithms::scale(flowerModel,glm::vec3(0.004f, 0.004f, 0.004f));
      mainShader.setMat4("model", flowerModel);
      flowers.Draw(mainShader);



      mainShader.use();
      glm::mat4 flowerModel2 = glm::mat4(1.0f);
      flowerModel2 = Algorithms::translate(   flowerModel2,glm::vec3(50.0f, -3.0f, 66.0f));
      flowerModel2 = Algorithms::scale(flowerModel2,glm::vec3(0.004f, 0.004f, 0.004f));
      mainShader.setMat4("model", flowerModel2);
      flowers.Draw(mainShader);



      glm::mat4 flowerModel3 = glm::mat4(1.0f);
      flowerModel3 = Algorithms::translate(   flowerModel3,glm::vec3(50.0f, -3.0f, 53.50f));
      flowerModel3 = Algorithms::scale(flowerModel3,glm::vec3(0.004f, 0.004f, 0.004f));
      mainShader.setMat4("model", flowerModel3);
      flowers.Draw(mainShader);



      mainShader.use();
      glm::mat4 flowerModel4 = glm::mat4(1.0f);
      flowerModel4 = Algorithms::translate(   flowerModel4,glm::vec3(49.0f, -3.0f, 52.0f));
      flowerModel4 = Algorithms::scale(flowerModel4,glm::vec3(0.004f, 0.004f, 0.004f));
      mainShader.setMat4("model", flowerModel4);
      flowers.Draw(mainShader);


      mainShader.use();
      mainShader.setMat4("model", model);
      trees.Draw(mainShader);
      ground.Draw(mainShader);
      ghantaghar.Draw(mainShader);
      wall.Draw(mainShader);
      stairs.Draw(mainShader);
      statue.Draw(mainShader);
      mainTemple.Draw(mainShader);


      glm::mat4 vehicleModel1 = glm::mat4(1.0f);
      glm::mat4 vehicleModel2 = glm::mat4(1.0f);
      glm::mat4 vehicleModel3 = glm::mat4(1.0f);
      vehicleShader.use();
      vehicleShader.setMat4("projection", projection);
      vehicleShader.setMat4("view", view);

      float tr=3.14;
      vehicleModel1 = Algorithms::translate(vehicleModel1, glm::vec3(0.0f, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, 10)); // moving boat
      vehicleModel1 = Algorithms::translate(vehicleModel1, glm::vec3(20.0f, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, 30*(sin((tr/180)*glfwGetTime())))); // moving boat
      vehicleModel2 = Algorithms::translate(vehicleModel2, glm::vec3(-15.0f, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, 0.0)); // floating boat
      vehicleModel2 = Algorithms::translate(vehicleModel2, glm::vec3(20*(sin((tr/180)*glfwGetTime())), (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, 0.0)); // floating boat
      vehicleModel3 = Algorithms::translate(vehicleModel3, glm::vec3(0.0, (sin(glfwGetTime()) + cos(1.5 + glfwGetTime()))*5, 0.0)); // floating boat


      vehicleShader.setMat4("model", vehicleModel1);

      boat1.Draw(vehicleShader);
      vehicleShader.use();
      vehicleShader.setMat4("model", vehicleModel2);
      boat2.Draw(vehicleShader);
      vehicleShader.use();
      vehicleShader.setMat4("model", vehicleModel3);
      boat3.Draw(vehicleShader);



      // ---------    Draw light sources   ---------

      glm::mat4 lightModel = glm::mat4(1.0f);
      sunlight.use();
      sunlight.setMat4("projection", projection);
      sunlight.setMat4("view", view);
      lightModel = Algorithms::translate(lightModel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
      lightModel = glm::scale(lightModel, glm::vec3(1.0f, 1.0f, 1.0f));      // it's a bit too big for our scene, so scale it down
      sunlight.setMat4("model", lightModel);
      light.Draw(sunlight);


      glm::mat4 sunModel = glm::mat4(1.0f);
      sunShader.use();
      sunShader.setMat4("projection", projection);
      sunShader.setMat4("view", view);
      float t=(3.14)*sin(pow(glfwGetTime(),0.7));

      sunModel = glm::rotate(sunModel,-t,glm::vec3(1.0,1.0,0.0));
      sunModel = Algorithms::translate(sunModel, glm::vec3(6.0f,9,70));
      sunModel = glm::scale(sunModel, glm::vec3(2.0f, 2.0f, 2.0f));
      sunShader.setMat4("model", sunModel);
      sunShader.setFloat("tim",glfwGetTime());
      sun.Draw(sunShader);

      glDisable(GL_DEPTH_TEST);

}


void RaniPokhari::applyDayLighting(float time) {


      float currentFrame = glfwGetTime();
      float glight =abs(cos(pow(currentFrame,0.7)));
      float glight2 =abs (sin(pow(currentFrame,0.7)));


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
//    point light 2
      mainShader.setVec3("pointLights[1].position", -61,6, 10);
      mainShader.setVec3("pointLights[1].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[1].constant", 1.0f);
      mainShader.setFloat("pointLights[1].linear", 0.09);
      mainShader.setFloat("pointLights[1].quadratic", 0.032);
//    point light 3
      mainShader.setVec3("pointLights[2].position", 42,6,110);
      mainShader.setVec3("pointLights[2].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[2].constant", 1.0f);
      mainShader.setFloat("pointLights[2].linear", 0.09);
      mainShader.setFloat("pointLights[2].quadratic", 0.032);
//    point light 4
      mainShader.setVec3("pointLights[3].position", 41,6,10);
      mainShader.setVec3("pointLights[3].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.0f);
      mainShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[3].constant", 1.0f);
      mainShader.setFloat("pointLights[3].linear", 0.09);
      mainShader.setFloat("pointLights[3].quadratic", 0.032);

//    lamp ghntaghar
      mainShader.setVec3("pointLights[4].position", -97,53,35);
      mainShader.setVec3("pointLights[4].ambient", glight2, glight, glight);
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
//    sun/moon
      mainShader.setVec3("pointLights[5].position", -100,34,38);
      mainShader.setVec3("pointLights[5].ambient", 1.0f, 1.0f, 1.0f);
      mainShader.setVec3("pointLights[5].diffuse", 0.8f, 0.8f, 0.8f);
      mainShader.setVec3("pointLights[5].specular", 1.0f, 1.0f, 1.0f);
      mainShader.setFloat("pointLights[5].constant", 1.0f);
      mainShader.setFloat("pointLights[5].linear", 0.09);
      mainShader.setFloat("pointLights[5].quadratic", 0.032);

      mainShader.setVec3("light.direction", -currentFrame, -currentFrame, -currentFrame);
      mainShader.setVec3("viewPos", camera.Position);

//    light properties
      mainShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
      mainShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
      mainShader.setVec3("light.specular", 0.50f, 0.50f, 0.50f);

//    material properties
      mainShader.setFloat("material.shininess", 32.0f);
      mainShader.setFloat("material.diffuse", 0.5f);
      mainShader.setFloat("material.specular", 0.30f);

      // view/projection transformations
/*      glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
      glm::mat4 view = camera.GetViewMatrix();*/

      glm::mat4 projection = Algorithms::prespective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
      glm::mat4 view = camera.GetViewMatrix();

      mainShader.setMat4("projection", projection);
      mainShader.setMat4("view", view);

      glm::mat4 model = glm::mat4(1.0f);
      mainShader.setMat4("model", model);


//    lighting for water

      waterShader.use();
      waterShader.setVec3("viewPos", camera.Position);
//    lamp1
      waterShader.setVec3("dirLight.direction", 100.0f, -34.0f, -0.3f);

      if(time>=0.6)
      {
            waterShader.setVec3("dirLight.ambient", 0.6,0.6,0.6);

      }
      else if(time<=0.001)
      {
            waterShader.setVec3("dirLight.ambient", 0.001,0.001,0.001);

      }
      else
      {
            waterShader.setVec3("dirLight.ambient", time,time,time);
            waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
            waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
      }
      
//    waterShader.setVec3("dirLight.ambient", 0.50f, 0.50f, 0.50f);
      waterShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
      waterShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//    lamp2
      waterShader.setVec3("pointLights[0].position", -61.34, 7.13, 109.8);
      waterShader.setVec3("pointLights[0].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[0].constant", 1.0f);
      waterShader.setFloat("pointLights[0].linear", 0.09);
      waterShader.setFloat("pointLights[0].quadratic", 0.032);
//    lamp3
      waterShader.setVec3("pointLights[1].position", -61.0,6.0f, 10.0f);
      waterShader.setVec3("pointLights[1].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[1].constant", 1.0f);
      waterShader.setFloat("pointLights[1].linear", 0.09);
      waterShader.setFloat("pointLights[1].quadratic", 0.032);
//    lamp 4
      waterShader.setVec3("pointLights[2].position", 42,6,110);
      waterShader.setVec3("pointLights[2].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[2].constant", 1.0f);
      waterShader.setFloat("pointLights[2].linear", 0.09);
      waterShader.setFloat("pointLights[2].quadratic", 0.032);
//    light 5
      waterShader.setVec3("pointLights[3].position", 41,6,10);
      waterShader.setVec3("pointLights[3].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[3].constant", 1.0f);
      waterShader.setFloat("pointLights[3].linear", 0.09);
      waterShader.setFloat("pointLights[3].quadratic", 0.032);
//    lamp ghntaghar
      waterShader.setVec3("pointLights[4].position", -100,34,38);
      waterShader.setVec3("pointLights[4].ambient", 0.3f, 0.3f, 0.3f);
      waterShader.setVec3("pointLights[4].diffuse", 0.8f, 0.8f, 0.8f);
      waterShader.setVec3("pointLights[4].specular", 1.0f, 1.0f, 1.0f);
      waterShader.setFloat("pointLights[4].constant", 1.0f);
      waterShader.setFloat("pointLights[4].linear", 0.09);
      waterShader.setFloat("pointLights[4].quadratic", 0.032);

//    sun/moon
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





#endif //RANIPOKHARI_RANIPOK_H
