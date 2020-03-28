#version 330

uniform mat4 model_matrix, view_matrix, projection_matrix;

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

out vec3 fragVert;
out vec2 fragTexCoord;
out vec3 fragNormal;

void main() {
    // Pass some variables to the fragment shader
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragVert = vert;
    
    // Apply all matrix transformations to vert
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vert, 1);
}
