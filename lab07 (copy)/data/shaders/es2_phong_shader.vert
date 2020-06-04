attribute vec4 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec4 tangentDet;
attribute vec4 texture1_coordinates;
attribute vec4 texture2_coordinates;

uniform mat4 model_view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix;
uniform float point_size;

uniform bool texture1_enabled;
uniform bool texture1_transformation_enabled;
uniform mat4 texture1_transformation_matrix;

uniform sampler2D texture1_normal_sampler;
uniform bool texture1_normal_enabled;

uniform bool texture2_enabled;
uniform bool texture2_transformation_enabled;
uniform mat4 texture2_transformation_matrix;

varying vec3 fragment_view_direction;
varying vec3 fragment_view_normal;
varying vec3 fragment_view_tangent;
varying vec3 fragment_view_binormal;
varying mat3 fragment_view_tangent_binormal_normal;
varying vec4 fragment_color;
varying vec2 fragment_texture1_coordinates;
varying vec2 fragment_texture2_coordinates;

void main()
{
    vec4 view_position = model_view_matrix * position;
    fragment_view_direction = -view_position.xyz;
    vec3 binormal = cross(normal, tangentDet.xyz) * tangentDet.w;
    fragment_view_normal = normalize(normal_matrix * normal);
    fragment_view_tangent = normalize(normal_matrix * tangentDet.xyz);
    fragment_view_binormal = normalize(normal_matrix * binormal);
    fragment_view_tangent_binormal_normal = mat3(fragment_view_tangent, fragment_view_binormal, fragment_view_normal);
    fragment_color = color;
    if (texture1_enabled) {
        if (texture1_transformation_enabled) {
            vec4 transformed_texture1_coordinates = texture1_transformation_matrix * vec4(texture1_coordinates.st, 0.0, 1.0);
            fragment_texture1_coordinates = vec2(transformed_texture1_coordinates);
        } else {
            fragment_texture1_coordinates = vec2(texture1_coordinates);
        }
    }
    if (texture2_enabled) {
        if (texture2_transformation_enabled) {
            vec4 transformed_texture2_coordinates = texture2_transformation_matrix * vec4(texture2_coordinates.st, 0.0, 1.0);
            fragment_texture2_coordinates = vec2(transformed_texture2_coordinates);
        } else {
            fragment_texture2_coordinates = vec2(texture2_coordinates);
        }
    }

    gl_Position = projection_matrix * view_position;
    gl_PointSize = point_size;
}
