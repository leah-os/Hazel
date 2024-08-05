#shader vertex
#version 400 core
layout (location = 0) in vec3 aPosition;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 transform;

void main()
{
    gl_Position = proj * view * transform * vec4(aPosition, 1.0);;
}

#shader fragment
#version 400 core

out vec4 FragColor; 

uniform vec4 color;
uniform vec4 light;

void main()
{
    FragColor = color * light;
}