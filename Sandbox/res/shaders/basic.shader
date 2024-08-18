#shader vertex
#version 400 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 transform;

out vec3 Normal;
out vec3 FragPos;
//out vec2 TexCoord;

void main()
{
    Normal = mat3(transpose(inverse(transform))) * aNormal;
    //TexCoord = aTexCoord;
    FragPos = vec3(transform * vec4(aPosition, 1.0));
    gl_Position = proj * view * transform * vec4(aPosition, 1.0);;
}

#shader fragment
#version 400 core

in vec3 Normal;
in vec3 FragPos;
//in vec2 TexCoord;

out vec4 FragColor; 

uniform vec3 ObjColor;
uniform vec3 LightPos;
uniform vec3 LightColor;

//uniform sampler2D ourTexture;

void main()
{
    float ambientStrength = 0.2;
    vec3 ambient = LightColor * ambientStrength;

    vec3 norm = normalize(Normal);
    vec3 lightDirection = normalize(LightPos - FragPos);

    float diff = max(dot(norm, lightDirection), 0.0);
    vec3 diffuse = diff * LightColor;

    //vec4 Color = texture(ourTexture, TexCoord);

    vec3 result = (ambient + diffuse) * ObjColor;
    FragColor = vec4(result, 1.0);
}