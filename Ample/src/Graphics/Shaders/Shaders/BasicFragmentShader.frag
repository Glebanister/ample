#version 330

layout(location = 0) out vec4 out_color;

uniform vec3 object_color;

in float light;
 
void main()
{
    out_color = vec4(light + object_color[0],
                     light + object_color[1],
                     light + object_color[2],
                     1);
}
