//Phong Reflection Model Vertex Shader

#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;

uniform mat4 model_matrix, view_matrix, projection_matrix;

out vec3 fragVert;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    fragNormal = in_normal;
    fragVert = in_position;
    
    // Apply all matrix transformations to vert
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);
}