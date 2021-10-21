#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 tex;

uniform mat4 transform = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec3 ourColor;
out vec2 TexCoord;
void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = tex;
}