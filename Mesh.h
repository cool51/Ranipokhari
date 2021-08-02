//
// Created by cool on 5/26/21.
//

#ifndef LEARNOPENGLTUT_MESH_H
#define LEARNOPENGLTUT_MESH_H

#endif //LEARNOPENGLTUT_MESH_H

#include "shader_m.h"
#include "vector"
#include "glm/glm.hpp"
#include <string>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;

};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader &shader);

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};