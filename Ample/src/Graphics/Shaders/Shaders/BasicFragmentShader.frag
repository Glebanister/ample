// Phong reflection model; Fragment Shader
// To keep it simple didn't add ambient and emissive lights;
// only diffuse and specular with white intensity

#version 330

layout(location = 0) out vec4 out_color;

uniform vec3 light_position;
uniform vec3 object_color;

// in vec3 world_pos;
// in vec3 world_normal;

// here
uniform mat4 model_matrix;

in vec3 fragNormal;
in vec3 fragVert;

out vec4 finalColor;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(model_matrix)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    vec3 fragPosition = vec3(model_matrix * vec4(fragVert, 1));
    vec3 surfaceToLight = light_position - fragPosition;
    float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
    brightness = clamp(brightness, 0, 1);
    finalColor = vec4(brightness * 1.5 * object_color, 1);
}
