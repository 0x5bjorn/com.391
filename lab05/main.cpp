#include "aur.hpp"

#include <ctime>

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

    // * * * GEOMETRY AND MATERIAL * * *
    // ! ! ! SPHERE ! ! !
    auto sphere_geometry_data = geometry_generators::generate_sphere_geometry_data(0.5f, 20, 20);
    auto sphere_geometry = std::make_shared<ES2Geometry>(sphere_geometry_data.first, sphere_geometry_data.second);
    sphere_geometry->set_type(GL_TRIANGLE_FAN);
    auto sphere_material = std::make_shared<ES2ConstantMaterial>();
    sphere_material->set_emission_color(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});

    // ! ! ! HAND ! ! !
    auto hand_geometry_data = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 20, 20);
    auto hand_geometry = std::make_shared<ES2Geometry>(hand_geometry_data.first, hand_geometry_data.second);
    hand_geometry->set_type(GL_TRIANGLE_FAN);
    auto hand_material = std::make_shared<ES2ConstantMaterial>();
    hand_material->set_emission_color(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});

    // ! ! ! CIRCLE ! ! !
    auto circle_geometry_data = geometry_generators::generate_circle_geometry_data(1.0f, 20);
    auto circle_geometry = std::make_shared<ES2Geometry>(circle_geometry_data.first, circle_geometry_data.second);
    circle_geometry->set_type(GL_TRIANGLE_FAN);
    auto circle_material = std::make_shared<ES2ConstantMaterial>();
    circle_material->set_emission_color(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});

    // ! ! ! PLANE ! ! !
    auto plane_geometry_data = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 1, 1);
    auto plane_geometry = std::make_shared<ES2Geometry>(plane_geometry_data.first, plane_geometry_data.second);
    plane_geometry->set_type(GL_TRIANGLE_FAN);
    auto plane_material = std::make_shared<ES2ConstantMaterial>();
    plane_material->set_emission_color(glm::vec4{1.0f, 1.0f, 0.0f, 1.0f});


    // * * * OBJECTS * * *
    std::vector<std::shared_ptr<Object>> objects;

    // * * * MESH * * *
    // ! ! ! CLOCK ! ! !
    auto center = std::make_shared<Mesh>(sphere_geometry, sphere_material, glm::vec3{0.0f, 0.0f, 0.0f});
    center->set_scale(glm::vec3{0.2f});
    center->set_name("Center");

    /* test */
    // auto center2 = std::make_shared<Mesh>(sphere_geometry, sphere_material, glm::vec3{0.0f, 0.0f, 0.0f});
    // center2->set_scale(glm::vec3{0.2f});
    // center2->set_name("Center");
    /* test */

    auto hour_hand = std::make_shared<Mesh>(hand_geometry, hand_material, glm::vec3{0.0f, 0.0f, 0.0f});
    hour_hand->set_scale(glm::vec3{7.0f, 0.5f, 0.0f});
    hour_hand->set_name("Hour");

    auto min_hand = std::make_shared<Mesh>(hand_geometry, hand_material, glm::vec3{0.0f, 0.0f, 0.0f});
    min_hand->set_scale(glm::vec3{10.0f, 0.3f, 0.0f});
    min_hand->set_name("Min");

    auto sec_hand = std::make_shared<Mesh>(hand_geometry, hand_material, glm::vec3{0.0f, 0.0f, 0.0f});
    sec_hand->set_scale(glm::vec3{12.0f, 0.1f, 0.0f});
    sec_hand->set_name("Sec");

    center->add_child(hour_hand);
    center->add_child(min_hand);
    center->add_child(sec_hand);

    // ! ! ! POINTS ! ! !
    for (int i = 0; i < 60; ++i) {
        float angle = (float) i / (float) 60 * 2.0f * (float) M_PI;
        float x = cosf(angle) * 13.0f;
        float y = sinf(angle) * 13.0f;

        auto point = std::make_shared<Mesh>(circle_geometry, circle_material, glm::vec3{x, y, 0.0f});
        point->set_scale(glm::vec3{0.2f});
        center->add_child(point);
    }

    /* test */
    // for (int i = 0; i < 60; ++i) {
    //     float angle = (float) i / (float) 60 * 2.0f * (float) M_PI;
    //     float x = cosf(angle) * 13.0f;
    //     float y = sinf(angle) * 13.0f;
    //
    //     auto point = std::make_shared<Mesh>(circle_geometry, circle_material, glm::vec3{x, y, 0.0f});
    //     point->set_scale(glm::vec3{0.2f});
    //     center2->add_child(point);
    // }
    /* test */

    // ! ! ! PLANES ! ! !
    for (int i = 0; i < 12; ++i) {
        float angle = (float) i / (float) 12 * 2.0f * (float) M_PI;
        float x = cosf(angle) * 14.0f;
        float y = sinf(angle) * 14.0f;

        auto plane = std::make_shared<Mesh>(plane_geometry, plane_material, glm::vec3{x, y, -0.5f});
        plane->set_rotation_z(0.8f);
        plane->set_scale(glm::vec3{0.6f});
        center->add_child(plane);

    }
    for (int i = 0; i < 4; ++i) {
        float angle = (float) i / (float) 4 * 2.0f * (float) M_PI;
        float x = cosf(angle) * 14.0f;
        float y = sinf(angle) * 14.0f;

        auto plane = std::make_shared<Mesh>(plane_geometry, sphere_material, glm::vec3{x, y, -0.2f});
        plane->set_rotation_z(0.8f);
        plane->set_scale(glm::vec3{1.2f});
        center->add_child(plane);
    }

    objects.push_back(center);
    // objects.push_back(center2);

    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();

    auto &camera = scene->get_camera();
    camera.set_z(5.0f);

    //          pass by reference
    //                  |
    //                  V
    window->set_on_key([&](int key) {
        switch (key) {
            case SDLK_w: camera.set_rotation_x(camera.get_rotation_x() - CAMERA_ROT_SPEED); break;
            case SDLK_a: camera.set_rotation_y(camera.get_rotation_y() + CAMERA_ROT_SPEED); break;
            case SDLK_s: camera.set_rotation_x(camera.get_rotation_x() + CAMERA_ROT_SPEED); break;
            case SDLK_d: camera.set_rotation_y(camera.get_rotation_y() - CAMERA_ROT_SPEED); break;
            case SDLK_e: camera.set_y(camera.get_y() + CAMERA_ROT_SPEED); break;
            case SDLK_q: camera.set_y(camera.get_y() - CAMERA_ROT_SPEED); break;
            case SDLK_UP: camera.set_position(camera.get_position() - glm::vec3(camera.get_model_matrix() * FORWARD * CAMERA_SPEED));   break;
            case SDLK_DOWN: camera.set_position(camera.get_position() + glm::vec3(camera.get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
            case SDLK_LEFT: camera.set_position(camera.get_position() - glm::vec3(camera.get_model_matrix() * SIDE * CAMERA_SPEED));   break;
            case SDLK_RIGHT: camera.set_position(camera.get_position() + glm::vec3(camera.get_model_matrix() * SIDE * CAMERA_SPEED)); break;
            case SDLK_ESCAPE: exit(0); break;
            default: break;
        }
    });

    ES2Renderer renderer(scene, window);

    float i = 0;
    for (;;) {
        window->poll();

        time_t curr_time;
        curr_time = time(NULL);
        tm *tm_local = localtime(&curr_time);

        int hour = 3 + tm_local->tm_hour;
        int min = 15 + tm_local->tm_min;
        int sec = 15 + tm_local->tm_sec;

        // TODO
        center->set_rotation_y(center->get_rotation_y() - 100.0f);

        /* test */
        // center2->set_rotation_x(center2->get_rotation_x() - 100.0f);
        //
        // float road_angle = (float) i / (float) 360 * 2.0f * (float) M_PI;
        // float road_x = cosf(road_angle) * 3.0f;
        // float road_y = sinf(road_angle) * 3.0f;
        // i+=1.0f;
        // if (i == 360) i = 0;

        // center->set_x(road_x);
        // center->set_y(road_y);

        // center2->set_x(road_x);
        // center2->set_y(road_y);
        //
        // center->set_z(center->get_z() - 0.01f);
        // center2->set_z(center2->get_z() - 0.01f);
        /* test */

        float hour_angle = (float) hour / (float) 12 * 2.0f * (float) M_PI;
        float hour_x = cosf(hour_angle) * 3.5f;
        float hour_y = sinf(hour_angle) * 3.5f;
        hour_hand->set_x(hour_x);
        hour_hand->set_y(hour_y);
        hour_hand->set_rotation_z( hour_angle );

        float min_angle = (float) min / (float) 60 * 2.0f * (float) M_PI;
        float min_x = cosf(min_angle) * 5.0f;
        float min_y = sinf(min_angle) * 5.0f;
        min_hand->set_x(min_x);
        min_hand->set_y(min_y);
        min_hand->set_rotation_z( min_angle );

        float sec_angle = (float) sec / (float) 60 * 2.0f * (float) M_PI;
        float sec_x = cosf(sec_angle) * 6.0f;
        float sec_y = sinf(sec_angle) * 6.0f;
        sec_hand->set_x(sec_x);
        sec_hand->set_y(sec_y);
        sec_hand->set_rotation_z( sec_angle );

	    // printf("Current local time %d:%d:%d\n", hour, min, sec);

        renderer.render();
    }
}
