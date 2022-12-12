#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 f_position;
in vec3 f_normal;
in vec2 f_texture;
in vec3 f_color;

// Output
layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;


void main()
{   

    // TODO(student): Write pixel out color
    out_color = vec4(f_color, 1);
    //out_color = vec4(f_normal, 1);
    //out_normal	= vec4(f_normal, 1);
	//out_texture = vec3(f_texture, 1);

}
