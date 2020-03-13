//Phong Reflection Model Vertex Shader

#version 330
 
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
 
uniform mat4 model_matrix, view_matrix, projection_matrix;
 
//send them to fragment shader
out vec3 world_pos;
out vec3 world_normal;
 
void main()
{
    // convert in world coords
    world_pos = mat3(model_matrix) * in_position; // careful here
    world_normal = normalize(mat3(model_matrix) * in_normal);
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);
}
