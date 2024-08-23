#shader vertex
#version 400 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 vNormal;
out vec3 vFragPos;

uniform mat4 view;
uniform mat4 transform;
uniform mat4 proj;

void main()
{
    vNormal = mat3(transpose(inverse(transform))) * aNormal;
    vFragPos = vec3(transform * vec4(aPosition, 1.0));
    gl_Position = proj * view * transform * vec4(aPosition, 1.0);;
}

#shader fragment
#version 400 core

in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;

uniform vec3 LightPos;
uniform vec3 ObjColor;
uniform vec3 LightColor;

void main()
{
    vec3 norm = normalize(vNormal);
    vec3 light_dir = normalize(LightPos - vFragPos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * LightColor;
    vec3 result = (diffuse) * ObjColor;
    FragColor = vec4(result, 1.0);
}