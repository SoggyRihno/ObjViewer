#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model, view, projection;

out vec4 color;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    color = vec4(position, 1.0);
}