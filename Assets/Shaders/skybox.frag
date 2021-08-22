
#version 330 core
out vec4 FragColor;
uniform float skyboxtime;

in vec3 TexCoords;
vec4 colo= vec4(1.0, 1.0, 1.0, skyboxtime);

uniform samplerCube skybox;

void main()
{
    FragColor = colo*texture(skybox, TexCoords);
}
