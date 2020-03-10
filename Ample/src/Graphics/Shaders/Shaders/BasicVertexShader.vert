#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;

uniform mat4 model_matrix, view_matrix, projection_matrix;

uniform vec3 light_position;
uniform vec3 eye_position;

out float light;

void main()
{
    int material_shininess = 100;
    float material_kd = 0.5;
    float material_ks = 0.4;
    
    vec3 world_position = mat3(model_matrix) * in_position;//careful here

    vec3 world_normal = normalize(mat3(model_matrix) * in_normal);

    //don't forget to normalize
    vec3 L = normalize(light_position - world_position);//light direction
    vec3 V = normalize(eye_position - world_position); //view direction

    //Lambert term
    float LdotN = max(0, dot(L, world_normal));

    //consider diffuse light color white(1,1,1)
    //all color channels have the same float value
    float diffuse = material_kd * LdotN;

    float specular = 0;

    if(LdotN > 0.0)
    {
        //can use built-in max or saturate function
        vec3 R = -normalize(reflect(L,world_normal));//reflection
        specular = material_ks * pow( max(0, dot( R, V)), material_shininess);
    }

    //pass light to fragment shader
    light = diffuse + specular;

    //How about with ambinetal and emissive?
    //Final light(with white(1,1,1)) would be:
    //light = ke + material_ka + diffuse + specular;

    //final vertex position
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1);
}