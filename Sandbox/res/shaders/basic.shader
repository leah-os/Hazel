#shader vertex
#version 400 core
layout (location = 0) in vec3 aPos;

out vec3 Position;

void main()
{
    Position = aPos;
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 400 core

in vec3 Position;
out vec4 FragColor;

void main()
{
    FragColor = vec4(Position * 0.5 + 0.5, 1.0);
}