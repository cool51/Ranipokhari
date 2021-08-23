#version 330 core
out vec4 FragColor;
//in vec2 TexCoords;
uniform float lTime;

void main()
{
        FragColor = vec4(sin(lTime),cos(lTime),cos(lTime),0.5);
//    FragColor = texture(TexCoords);
//        FragColor = vec4(1.0,1.0,0.0,1.0);

}