//
// Created by cool on 8/23/21.
//

#ifndef RANIPOKHARI_ALGROTHIMS_H
#define RANIPOKHARI_ALGROTHIMS_H
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Algorithms{
public:
    static glm::mat4 prespective(float fov, float aspectRatio, float near, float far);
    static glm::mat4 translate(const glm::mat4& mat, glm::vec3 vec);
    static glm::mat4 scale(const glm::mat4& mat, glm::vec3 vec);
    };

glm::mat4 Algorithms::scale(const glm::mat4& mat, glm::vec3 vec) {
      glm::mat4 result = mat;
      result[0][0] *= vec.x;
      result[1][1] *= vec.y;
      result[2][2] *= vec.z;
      return result * mat;
}

glm::mat4 Algorithms:: translate(const glm::mat4& mat, glm::vec3 vec) {
      glm::mat4 result = mat;
      result[3][0] += vec.x;
      result[3][1] += vec.y;
      result[3][2] += vec.z;

      return result * mat;
}
glm::mat4 Algorithms::prespective(float fov, float aspectRatio, float near, float far){

/*       P'=M*P
      Opengl has near and far plane clipping so point is displayed only if z lies within defined range
      so new linera mapping is done to manage this for whis we introduce alpha and beta now on solving
      we get value of alpha and beta is in equation below
      M=[scale 0 0 0
         0 scale 0 0
         0 0 Alpha beta
         0 0 -1 0
         ]

         Aplha=(near+far)/(near-far)
         Beta=(2*near*far)/(near-far)
      */



      glm::mat4 result(0.0f);
      float scale = 1.0 / std::tan(fov / 2);//fov =field of view
      result[0][0] = scale/aspectRatio; // scale the x coordinates
      result[1][1] = scale; // scale the y coordinates
      result[2][2] = -(far+near) / (far - near); // remap z to [0,1]
      result[2][3] = -1; // in opengl camera is pointing to negative z axis
      result[3][2] = (2*far*near)/(near - far);
      return result;
}

#endif //RANIPOKHARI_ALGROTHIMS_H
