#version 330 core
out vec4 FragColor;
uniform float tim;

void main()
{
    FragColor = vec4(1.0,sin(tim),0.0,1.0);// set alle 4 vector values to 1.0
}