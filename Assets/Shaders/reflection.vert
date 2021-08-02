//#version 330 core
//layout (location = 0) in vec3 aPos;
//
//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
//
//void main()
//{
//    gl_Position = projection * view * model * vec4(aPos, 1.0);
//}
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//reflection matrix

mat4 m = mat4(
1.0, 0.0, 0.0, 0.0,
0.0, -1.0, 0.0, 0.0,
0.0, 0.0, 1.0, 0.0,
0.0, 0.0, 0.0, 1.0

);

void main()
{
    TexCoords = aTexCoords;
    gl_Position = projection * view * model *m* vec4(aPos, 1.0);
}
