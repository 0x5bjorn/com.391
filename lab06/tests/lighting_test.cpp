#include "aur.hpp"

static const float CAMERA_SPEED { 0.5f };
static const float CAMERA_ROT_SPEED { 0.05f };

// static const

static const glm::vec4 FORWARD { 0.0f, 0.0f, 1.0f, 0.0f };
static const glm::vec4 SIDE { 1.0f, 0.0f, 0.0f, 0.0f };

// [[ noreturn ]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO
    auto plane_geometry_data = geometry_generators::generate_plane_geometry_data(40.0f, 40.0f, 20, 20);
    auto plane_geometry = std::make_shared<ES2Geometry>(plane_geometry_data.first, plane_geometry_data.second);
    // plane_geometry->set_type(Geometry::Type::TriangleStrip);
    auto plane_material = std::make_shared<ES2PhongMaterial>();
    plane_material->set_emission_color(glm::vec4{0.2f, 0.2f, 0.2f, 1.0f});
    plane_material->set_ambient_color(glm::vec3{0.5f, 0.5f, 0.5f});
    plane_material->set_diffuse_color(glm::vec4{0.7f});
    plane_material->set_specular_color(glm::vec3{1.0f});
    plane_material->set_specular_exponent(64);

    auto center_geometry_data = geometry_generators::generate_sphere_geometry_data(0.5f, 20, 20);
    auto center_geometry = std::make_shared<ES2Geometry>(center_geometry_data.first, center_geometry_data.second);
    // center_geometry->set_type(Geometry::Type::TriangleFan);
    auto center_material = std::make_shared<ES2PhongMaterial>();
    center_material->set_emission_color(glm::vec4{0.3f, 0.3f, 0.3f, 1.0f});
    center_material->set_ambient_color(glm::vec3{0.2f, 0.2f, 0.8f});
    center_material->set_diffuse_color(glm::vec4{0.2f, 0.3f, 0.8f, 1.0f});
    center_material->set_specular_color(glm::vec3{1.0f});
    center_material->set_specular_exponent(32);

    auto lamp_geometry_data = geometry_generators::generate_sphere_geometry_data(0.1f, 15, 15);
    auto lamp_geometry = std::make_shared<ES2Geometry>(lamp_geometry_data.first, lamp_geometry_data.second);
    lamp_geometry->set_type(Geometry::Type::Points);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    lamp_material->set_emission_color(glm::vec4{1.0f});

    auto plane = std::make_shared<Mesh>(plane_geometry, plane_material, glm::vec3{0.0f, -2.0f, 0.0f});
    plane->set_rotation_x(-1.57f);
    plane->set_name("Plane");

    auto center = std::make_shared<Mesh>(center_geometry, center_material, glm::vec3{0.0f, 0.0f, 0.0f});
    center->set_name("Center");

    auto lamp1 = std::make_shared<Mesh>(lamp_geometry, lamp_material);
    lamp1->set_name("Lamp1");
    auto lamp2 = std::make_shared<Mesh>(lamp_geometry, lamp_material);
    lamp2->set_name("Lamp2");

    std::vector<std::shared_ptr<Object>> objects;
    objects.push_back(plane);
    objects.push_back(center);
    // objects.push_back(lamp1);
    // objects.push_back(lamp2);

    auto scene = std::make_shared<Scene>(objects);

    auto &camera = scene->get_camera();
    camera->set_z(5.0f);
    camera->set_y(5.0f);
    camera->set_rotation_x(-0.78f);

    scene->get_directional_lights().clear();
    scene->get_point_lights().clear();

    auto point_light1 = std::make_shared<PointLight>();
    point_light1->set_intensity(0.5f);
    point_light1->set_y(1.0f);
    point_light1->set_x(0.0f);
    point_light1->add_child(lamp1);
    scene->get_root()->add_child(point_light1);
    scene->get_point_lights().push_back(point_light1);

    auto point_light2 = std::make_shared<PointLight>();
    point_light2->set_intensity(0.5f);
    point_light2->set_y(1.0f);
    point_light2->set_x(0.0f);
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light2);

    window->set_on_key([&](int key) {
        switch (key) {
            case SDLK_w: camera->set_rotation_x(camera->get_rotation_x() - CAMERA_ROT_SPEED); break;
            case SDLK_a: camera->set_rotation_y(camera->get_rotation_y() + CAMERA_ROT_SPEED); break;
            case SDLK_s: camera->set_rotation_x(camera->get_rotation_x() + CAMERA_ROT_SPEED); break;
            case SDLK_d: camera->set_rotation_y(camera->get_rotation_y() - CAMERA_ROT_SPEED); break;
            case SDLK_e: camera->set_y(camera->get_y() + CAMERA_ROT_SPEED); break;
            case SDLK_q: camera->set_y(camera->get_y() - CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera->set_position(camera->get_position() - glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED));   break;
            case SDLK_DOWN: camera->set_position(camera->get_position() + glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_LEFT: camera->set_position(camera->get_position() - glm::vec3(camera->get_model_matrix() * SIDE * CAMERA_SPEED));   break;
            case SDLK_RIGHT: camera->set_position(camera->get_position() + glm::vec3(camera->get_model_matrix() * SIDE * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0); break;
            default: break;
        }
    });

    ES2Renderer renderer(scene, window);

    float i = 0;
    for (;;) {
        window->poll();

        // TODO
        float road_angle = (float) i / (float) 360 * 2.0f * (float) M_PI;

        float road_x = cosf(road_angle) * 1.0f;
        float road_z = sinf(road_angle) * 1.0f;
        point_light1->set_x(road_x);
        point_light1->set_z(-road_z);

        road_x = cosf(road_angle) * 1.2f;
        road_z = sinf(road_angle) * 1.2f;
        point_light2->set_x(road_x);
        point_light2->set_z(road_z);

        // float round_x = cosf(road_angle) * 2.0f;
        // float round_z = sinf(road_angle) * 2.0f;
        // center->set_x(round_x);
        // center->set_z(round_z);

        i+=1.0f;
        if (i == 360) i = 0;


        renderer.render();
    }
}
