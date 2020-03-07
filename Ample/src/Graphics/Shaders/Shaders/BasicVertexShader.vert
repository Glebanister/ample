#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
  
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertexPosition_modelspace, 1);
}
