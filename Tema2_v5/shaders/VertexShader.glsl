#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
// TODO(student): Output values to fragment shader
out vec3 f_position;
out vec3 f_normal;
out vec2 f_texture;
out vec3 f_color;


void main()
{
    // TODO(student): Send output to fragment shader
    f_position = v_position;
    f_normal = v_normal;
    //f_normal = v_normal;
    f_texture = v_texture;
    f_color = v_color;
    vec3 pos = vec3(v_position.x, v_position.y*0.2, v_position.z);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);

}
