#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

mat4 scaling = mat4(
5.0, 0.0, 0.0, 0.0,
0.0, 5.0, 0.0, 0.0,
0.0, 0.0, 5.0, 0.0,
0.0, 0.0, 0.0, 1.0

);

mat4 tran = mat4(
1.0, 0.0, 0.0, 1.0,
0.0, 1.0, 0.0, 5.0,
0.0, 0.0, 1.0, 5.0,
0.0, 0.0, 0.0, 1.0

);
//vec4 new=vec4(tran*vec4(aPos,1/0));
void main()
{
    TexCoords = aTexCoords;
    gl_Position =projection * view*model*vec4(aPos,1.0);
}