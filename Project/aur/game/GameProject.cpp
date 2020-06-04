#include "Enemy.hpp"
#include "Player.hpp"
#include "RoomComponent.hpp"
#include <chrono>

static const float CAMERA_SPEED{0.3f};
static const float CAMERA_SENSITIVITY{0.001f};

const glm::vec4 FORWARD{0.0f, 0.0f, 1.0f, 0.0f};
const glm::vec4 RIGHT{1.0f, 0.0f, 0.0f, 0.0f};

// [[noreturn]]
int main(int argc, char **argv)
{

    // Window

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);
    window->set_capture_mouse_enabled(true);
    window->set_relative_mouse_mode_enabled(true);

    RoomComponent ground{glm::vec3(0.0f, -2.5f, 0.0f), glm::vec3(-M_PI / 2.0f, 0.0f, 0.0f), 50, "../data/images/ground.png"};
    RoomComponent wall1{glm::vec3(0.0f, 22.5f, -25.0f), glm::vec3(0.0f, 0.0f, 0.0f), 50, "../data/images/wall.png"};
    RoomComponent wall2{glm::vec3(0.0f, 22.5f, 25.0f), glm::vec3(0.0f, M_PI, 0.0f), 50, "../data/images/wall.png"};
    RoomComponent wall3{glm::vec3(-25.0f, 22.5f, 0.0f), glm::vec3(0.0f, M_PI / 2.0f, 0.0f), 50, "../data/images/wall.png"};
    RoomComponent wall4{glm::vec3(25.0f, 22.5f, 0.0f), glm::vec3(0.0f, -M_PI / 2.0f, 0.0f), 50, "../data/images/wall.png"};

    // Monsters

    Enemy enemy1{glm::vec3(-5.0f, 2.0f, 0.0f), 9, std::make_tuple("../data/images/enemy.png", 10, 4), 0.05f};
    Enemy enemy2{glm::vec3(5.0f, 2.0f, 0.0f), 9, std::make_tuple("../data/images/enemy.png", 10, 4), 0.05f};

    // Gun

    Player player{glm::vec3(0.0f, -2.0f, 0.0f), 2, std::make_tuple("../data/images/gun.png", 4, 4)};

    // Lamps

    auto[lamp_indices, lamp_vertices] = geometry_generators::generate_sphere_geometry_data(0.5f, 20, 20);
    auto lamp_sphere_geometry = std::make_shared<ES2Geometry>(lamp_indices, lamp_vertices);
    auto lamp_material = std::make_shared<ES2ConstantMaterial>();
    auto lamp1 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp2 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp3 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);
    auto lamp4 = std::make_shared<Mesh>(lamp_sphere_geometry, lamp_material);

    std::vector<std::shared_ptr<Object>> objects{
        ground.get_mesh(), wall1.get_mesh(), wall2.get_mesh(),
        wall3.get_mesh(), wall4.get_mesh(),
        enemy1.get_mesh(), enemy2.get_mesh(), player.get_mesh()
    };
    auto scene = std::make_shared<Scene>(objects);

    // Point Lights

    auto point_light1 = std::make_shared<PointLight>();
    point_light1->set_intensity(4000.0f);
    point_light1->set_constant_attenuation(0.0f);
    point_light1->set_linear_attenuation(0.2f);
    point_light1->set_quadratic_attenuation(0.8f);
    point_light1->set_two_sided(true);
    point_light1->set_position(glm::vec3(-25.0f, 6.0f, 25.0f));
    point_light1->add_child(lamp1);
    scene->get_root()->add_child(point_light1);
    scene->get_point_lights().push_back(point_light1);

    auto point_light2 = std::make_shared<PointLight>();
    point_light2->set_intensity(4000.0f);
    point_light2->set_constant_attenuation(0.0f);
    point_light2->set_linear_attenuation(0.2f);
    point_light2->set_quadratic_attenuation(0.8f);
    point_light2->set_two_sided(true);
    point_light2->set_position(glm::vec3(25.0f, 6.0f, 25.0f));
    point_light2->add_child(lamp2);
    scene->get_root()->add_child(point_light2);
    scene->get_point_lights().push_back(point_light2);

    auto point_light3 = std::make_shared<PointLight>();
    point_light3->set_intensity(4000.0f);
    point_light3->set_constant_attenuation(0.0f);
    point_light3->set_linear_attenuation(0.2f);
    point_light3->set_quadratic_attenuation(0.8f);
    point_light3->set_two_sided(true);
    point_light3->set_position(glm::vec3(25.0f, 6.0f, -25.0f));
    point_light3->add_child(lamp3);
    scene->get_root()->add_child(point_light3);
    scene->get_point_lights().push_back(point_light3);

    auto point_light4 = std::make_shared<PointLight>();
    point_light4->set_intensity(4000.0f);
    point_light4->set_constant_attenuation(0.0f);
    point_light4->set_linear_attenuation(0.2f);
    point_light4->set_quadratic_attenuation(0.8f);
    point_light4->set_two_sided(true);
    point_light4->set_position(glm::vec3(-25.0f, 6.0f, -25.0f));
    point_light4->add_child(lamp4);
    scene->get_root()->add_child(point_light4);
    scene->get_point_lights().push_back(point_light4);

    // Camera

    auto camera = scene->get_camera();
    camera->set_position(glm::vec3(0.0f, 0.0f, 20.0f));
    camera->set_zoom(3.0f);

    enemy1.set_target(camera);
    enemy2.set_target(camera);

    // Input

    window->set_on_key_down([&](int key, const Uint8* state) {
        glm::mat4 model_matrix = camera->get_model_matrix();
        glm::mat3 move = glm::mat3{1.0};
        move[0] = glm::vec3{1.0f, 0.0f, 0.0f};
        move[1] = glm::vec3{0.0f};
        move[2] = glm::vec3{0.0f, 0.0f, 1.0f};

        if (state[SDL_SCANCODE_W]) camera->add_to_position(-glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)*move);
        else if (state[SDL_SCANCODE_S]) camera->add_to_position(glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)*move);

        if (state[SDL_SCANCODE_A]) camera->add_to_position(-glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)*move);
        else if (state[SDL_SCANCODE_D]) camera->add_to_position(glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)*move);

        if (SDLK_ESCAPE == key) exit(0);

        // switch (key) {
        //     case SDLK_w: camera->add_to_position(-glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)*move); break;
        //     case SDLK_a: camera->add_to_position(-glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)*move); break;
        //     case SDLK_s: camera->add_to_position(glm::vec3(model_matrix * FORWARD * CAMERA_SPEED)*move); break;
        //     case SDLK_d: camera->add_to_position(glm::vec3(model_matrix * RIGHT * CAMERA_SPEED)*move); break;
        //     case SDLK_ESCAPE: exit(0);
        //     default: break;
        // }
    });

    window->set_on_mouse_move([&](int x, int y, int x_rel, int y_rel) {
        camera->add_to_rotation_y(static_cast<float>(-x_rel) * CAMERA_SENSITIVITY);
        camera->add_to_rotation_x(static_cast<float>(-y_rel) * CAMERA_SENSITIVITY);
    });

    window->set_on_mouse_down([&](int button, int state, int x, int y) {
        if (state == SDL_PRESSED) {
            player.set_shooting_state(true);

            int cx = static_cast<int>(window->get_width() / 2);
            int cy = static_cast<int>(window->get_height() / 2);
            Ray ray = camera->world_ray_from_screen_point(cx, cy, static_cast<int>(window->get_width()), static_cast<int>(window->get_height()));

            if (enemy1.intersects_with_ray(ray)) {
                enemy1.kill();
            }

            if (enemy2.intersects_with_ray(ray)) {
                enemy2.kill();
            }
        }

        if (state == SDL_RELEASED) {
            player.set_shooting_state(false);
        }

    });

    // Rendering

    auto prev_frame_time = std::chrono::steady_clock::now();

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        auto curr_frame_time = std::chrono::steady_clock::now();
        auto frame_time_diff = curr_frame_time - prev_frame_time;
        float delta_time = frame_time_diff.count();

        player.update(delta_time);
        enemy1.update(delta_time);
        enemy2.update(delta_time);

        renderer.render();
    }
}
