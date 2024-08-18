#shader vertex
#version 400 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec3 Normal;
out vec3 FragPos;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPosition, 1.0));
    gl_Position = proj * view * model * vec4(aPosition, 1.0);;
}

#shader fragment
#version 400 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor; 

uniform vec3 ObjColor;
uniform vec3 LightColor;
uniform vec3 ViewPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

void main()
{
    vec3 ambient = LightColor * (light.ambient * material.ambient);

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(light.position - FragPos);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = LightColor * light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(ViewPosition - FragPos);
    vec3 reflectDir = reflect(-light.position, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4);
    vec3 specular = light.specular * (spec * material.specular) * LightColor;

    vec3 result = (ambient + diffuse + specular) * ObjColor;
    FragColor = vec4(result, 1.0);
}