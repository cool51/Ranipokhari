//#version 330 core
//out vec4 FragColor;
//
//void main()
//{
//    FragColor = vec4(1.0); // set alle 4 vector values to 1.0
//}

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
vec4 colo= vec4(0.2, 0.2, 0.2, 0.09);
uniform sampler2D texture_diffuse1;

void main()
{
    //    FragColor = texture(texture_diffuse1, TexCoords);
    //    FragColor =vec4(0.9);
    FragColor=colo;
     FragColor = colo*texture(texture_diffuse1, TexCoords);
    ////    FragColor = vertexColor;
}