#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform int is_spot_light;
uniform float cut_off;


uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    vec3 L = normalize( light_position - world_position );
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = normalize(reflect(-L, world_normal));//-L !!!!!!!!!!!!1 la speculara

    float ambient_light = material_kd * 0.25;
    float diffuse_light = material_kd * 1 * max(dot(world_normal, L), 0);
    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        //specular_light = material_ks * 1 * pow(max(dot(world_normal, H), 0), material_shininess);
		specular_light = material_ks * 1 * pow(max(dot(V, R), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    float spot_light = dot(-L, light_direction);
    float spot_light_limit = cos(cut_off);

    float dist = distance (light_position, world_position);
    float light_att_factor = 1.0 / pow((dist + 1), 2);
    if (is_spot_light == 1) {
        if (spot_light > cos(cut_off))
        {
	        // fragmentul este iluminat de spot, deci se calculeaza valoarea luminii conform  modelului Phong
	        // se calculeaza atenuarea luminii
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            light_att_factor = pow(linear_att, 2);


        }
        else{
            light_att_factor = 0;
        }
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    //float dist = distance (light_position, world_position);
    //float att_factor = 1.0 / pow((dist + 1), 2);
    float light = ambient_light + 0 + light_att_factor * (diffuse_light + specular_light);


    // TODO(student): Write pixel out color
    vec3 color = object_color * light;
    out_color = vec4(color, 1);

}
