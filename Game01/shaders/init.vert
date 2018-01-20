#version 410 core
uniform vec2 size;
uniform float scale;
uniform mat4 modelview;
uniform mat4 projection;
layout(location=0) in vec4 position;
//layout(location=1) in vec4 color;
out vec4 vertex_color;
uniform vec2 location;

void main()
{
    vertex_color = vec4(0.0, 0.0, 0.0, 1.0);
    gl_Position = projection * modelview * position;
}
