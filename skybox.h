//
// Created by cool on 8/18/21.
//

#ifndef RANIPOKHARI_SKYBOX_H
#define RANIPOKHARI_SKYBOX_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Algrothims.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"

#include "Camera.h"
#include "Model.h"

#include <iostream>
class Skybox
{
public:
//    float skyboxVertices[];
    Shader skyboxShader;
    Camera camera;
    unsigned int skyboxVAO, skyboxVBO;
    const unsigned int SCR_WIDTH = 1000;
    const unsigned int SCR_HEIGHT = 700;
    unsigned int cubemapTexture;
    vector<std::string> faces;
    glm::mat4 projection;
    glm::mat4 view ;


    Skybox()
    {

    }

    unsigned int loadCubemap(std::vector<std::string> faces)
    {
          unsigned int textureID;
          glGenTextures(1, &textureID);
          glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

          int width, height, nrChannels;
          for (unsigned int i = 0; i < faces.size(); i++)
          {
                unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
                if (data)
                {
                      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                   0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                      );
                      stbi_image_free(data);
                }
                else
                {
                      std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                      stbi_image_free(data);
                }
          }
          glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

          return textureID;
    }

    void loadSkybox(){
//          stbi_set_flip_vertically_on_load(true);

          skyboxShader=Shader("/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/skybox.vert", "/home/cool/CLionProjects/RaniPokhari/Assets/Shaders/skybox.frag");

          float skyboxVertices[] = {
                  // positions
                  -1.0f,  1.0f, -1.0f,
                  -1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                  -1.0f,  1.0f, -1.0f,

                  -1.0f, -1.0f,  1.0f,
                  -1.0f, -1.0f, -1.0f,
                  -1.0f,  1.0f, -1.0f,
                  -1.0f,  1.0f, -1.0f,
                  -1.0f,  1.0f,  1.0f,
                  -1.0f, -1.0f,  1.0f,

                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,

                  -1.0f, -1.0f,  1.0f,
                  -1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f,
                  -1.0f, -1.0f,  1.0f,

                  -1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f, -1.0f,
                  1.0f,  1.0f,  1.0f,
                  1.0f,  1.0f,  1.0f,
                  -1.0f,  1.0f,  1.0f,
                  -1.0f,  1.0f, -1.0f,

                  -1.0f, -1.0f, -1.0f,
                  -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f, -1.0f,
                  1.0f, -1.0f, -1.0f,
                  -1.0f, -1.0f,  1.0f,
                  1.0f, -1.0f,  1.0f
          };

          glGenVertexArrays(1, &skyboxVAO);
          glGenBuffers(1, &skyboxVBO);
          glBindVertexArray(skyboxVAO);
          glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
          glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
          glEnableVertexAttribArray(0);
          glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

          // load textures
          // -------------

           faces=
                  {
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/posx.jpg",
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/negx.jpg",
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/posy.jpg",
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/negy.jpg",
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/posz.jpg",
                          "/home/cool/CLionProjects/RaniPokhari/rani/skybox/football/negz.jpg",

                  };

          cubemapTexture = loadCubemap(faces);

          // shader configuration
          // --------------------
          skyboxShader.use();
          skyboxShader.setInt("skybox", 0);
    }

    void drawSkybox(float sktime){
          projection = Algorithms::prespective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);

/*          projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);*/
//           view = camera.GetViewMatrix();
          // draw skybox as last
          glEnable(GL_DEPTH_TEST);
          glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
          skyboxShader.use();
          skyboxShader.setFloat("skyboxtime",sktime );

          view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
          skyboxShader.setMat4("view", view);
          skyboxShader.setMat4("projection", projection);
          //  skybox cube
          glBindVertexArray(skyboxVAO);
          glActiveTexture(GL_TEXTURE0);
          glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
          glDrawArrays(GL_TRIANGLES, 0, 36);
          glBindVertexArray(0);
          glDepthFunc(GL_LESS); // set depth function back to default
          glDisable(GL_DEPTH_TEST);
    }
};

#endif //RANIPOKHARI_SKYBOX_H
