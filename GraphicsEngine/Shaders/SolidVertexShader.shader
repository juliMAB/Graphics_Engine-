#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 transform = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 vertexColor;
void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    vertexColor = vec4(aColor.x, aColor.y, aColor.z, 1.0); // set the output variable to a dark-red color
}