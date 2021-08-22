////#version 330 core
////out vec4 FragColor;
////
////in vec2 TexCoords;
////in vec4 vertexColor;
////uniform sampler2D texture_diffuse1;
////
////void main()
////{
////    // FragColor = texture(texture_diffuse1, TexCoords);
////    FragColor = vertexColor;
////
////}
//
//
//#version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//
//uniform sampler2D texture_diffuse1;
////
//in vec3 Normal;
//in  vec3 FragPos;
//vec3 lightPos=vec3 (10.0,6.0,30.0);
////vec3 lightPos=vec3(-61.0, 7.0 ,10.8);
////vec3 lightpos=vec3(-61.0, 6.0 ,10.0);
//vec4 lightColor=vec4 (1.0,1.0,1.0,1.0);
//void main()
//{
//
//    float ambientStrength = 0.1;
//    vec4 ambient = ambientStrength * lightColor;
//
//    // diffuse
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec4 diffuse = diff * lightColor;
//
//    vec4 result = (ambient + diffuse) * texture(texture_diffuse1, TexCoords);
//    FragColor =result;
////    FragColor = texture(texture_diffuse1, TexCoords);
//}

//#version 330 core
//out vec4 FragColor;
//
//in vec2 TexCoords;
//in vec4 vertexColor;
//uniform sampler2D texture_diffuse1;
//
//void main()
//{
//    // FragColor = texture(texture_diffuse1, TexCoords);
//    FragColor = vertexColor;
//
//}


#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 7


struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 viewPos;
uniform Material material;

vec4 lightColor=vec4 (1.0,1.0,1.0,1.0);

uniform sampler2D texture_diffuse1;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // final values results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // final results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}
void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
//vec3 result;

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);



    //    float ambientStrength = 0.1;
    //    vec4 ambient = ambientStrength * lightColor;
    //
    //    // diffuse
    //    vec3 norm = normalize(Normal);
    //    vec3 lightDir = normalize(lightPos - FragPos);
    //    float diff = max(dot(norm, lightDir), 0.0);
    //    vec4 diffuse = diff * lightColor;
    //
    //    vec4 result = (ambient + diffuse) * texture(texture_diffuse1, TexCoords);
    //    FragColor =result;
    ////    FragColor = texture(texture_diffuse1, TexCoords);
}

