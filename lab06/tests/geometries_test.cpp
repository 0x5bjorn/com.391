#include "aur.hpp"

// [[ noreturn ]]
int main(int argc, char **argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    // TODO

    // * * * PLANE DATA * * *
    auto plane1_geometry_data = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 5, 5);
    auto plane1_geometry = std::make_shared<ES2Geometry>(plane1_geometry_data.first, plane1_geometry_data.second);
    plane1_geometry->set_type(Geometry::Type::TriangleFan);
    auto plane1_material = std::make_shared<ES2ConstantMaterial>();
    plane1_material->set_emission_color(glm::vec4{1.0f, 0.0f, 0.0f, 1.0f});

    auto plane2_geometry_data = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 10, 10);
    auto plane2_geometry = std::make_shared<ES2Geometry>(plane2_geometry_data.first, plane2_geometry_data.second);
    plane2_geometry->set_type(Geometry::Type::LineLoop);
    auto plane2_material = std::make_shared<ES2ConstantMaterial>();
    plane2_material->set_emission_color(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

    auto plane3_geometry_data = geometry_generators::generate_plane_geometry_data(1.0f, 1.0f, 20, 20);
    auto plane3_geometry = std::make_shared<ES2Geometry>(plane3_geometry_data.first, plane3_geometry_data.second);
    plane3_geometry->set_type(Geometry::Type::Points);
    auto plane3_material = std::make_shared<ES2ConstantMaterial>();
    plane3_material->set_emission_color(glm::vec4{0.0f, 0.0f, 1.0f, 1.0f});


    // * * * CIRCLE DATA * * *
    auto circle1_geometry_data = geometry_generators::generate_circle_geometry_data(0.5f, 10);
    auto circle1_geometry = std::make_shared<ES2Geometry>(circle1_geometry_data.first, circle1_geometry_data.second);
    circle1_geometry->set_type(Geometry::Type::TriangleFan);
    auto circle1_material = std::make_shared<ES2ConstantMaterial>();
    circle1_material->set_emission_color(glm::vec4{1.0f, 0.0f, 1.0f, 1.0f});

    auto circle2_geometry_data = geometry_generators::generate_circle_geometry_data(0.5f, 20);
    auto circle2_geometry = std::make_shared<ES2Geometry>(circle2_geometry_data.first, circle2_geometry_data.second);
    circle2_geometry->set_type(Geometry::Type::LineLoop);
    auto circle2_material = std::make_shared<ES2ConstantMaterial>();
    circle2_material->set_emission_color(glm::vec4{1.0f, 1.0f, 0.0f, 1.0f});

    auto circle3_geometry_data = geometry_generators::generate_circle_geometry_data(0.5f, 30);
    auto circle3_geometry = std::make_shared<ES2Geometry>(circle3_geometry_data.first, circle3_geometry_data.second);
    circle3_geometry->set_type(Geometry::Type::Points);
    auto circle3_material = std::make_shared<ES2ConstantMaterial>();
    circle3_material->set_emission_color(glm::vec4{0.0f, 1.0f, 1.0f, 1.0f});


    // * * * SPHERE DATA * * *
    auto sphere1_geometry_data = geometry_generators::generate_sphere_geometry_data(0.5f, 10, 10);
    auto sphere1_geometry = std::make_shared<ES2Geometry>(sphere1_geometry_data.first, sphere1_geometry_data.second);
    sphere1_geometry->set_type(Geometry::Type::TriangleFan);
    auto sphere1_material = std::make_shared<ES2ConstantMaterial>();
    sphere1_material->set_emission_color(glm::vec4{1.0f, 0.7f, 0.0f, 1.0f});

    auto sphere2_geometry_data = geometry_generators::generate_sphere_geometry_data(0.5f, 20, 20);
    auto sphere2_geometry = std::make_shared<ES2Geometry>(sphere2_geometry_data.first, sphere2_geometry_data.second);
    sphere2_geometry->set_type(Geometry::Type::LineLoop);
    auto sphere2_material = std::make_shared<ES2ConstantMaterial>();
    sphere2_material->set_emission_color(glm::vec4{1.0f, 0.0f, 0.7f, 1.0f});

    auto sphere3_geometry_data = geometry_generators::generate_sphere_geometry_data(0.5f, 30, 30);
    auto sphere3_geometry = std::make_shared<ES2Geometry>(sphere3_geometry_data.first, sphere3_geometry_data.second);
    sphere3_geometry->set_type(Geometry::Type::Points);
    auto sphere3_material = std::make_shared<ES2ConstantMaterial>();
    sphere3_material->set_emission_color(glm::vec4{1.0f});


    // * * * PLANES * * *
    auto plane1 = std::make_shared<Mesh>(plane1_geometry, plane1_material, glm::vec3{-3.0f, 1.5f, 0.0f});
    plane1->set_name("Plane1");

    auto plane2 = std::make_shared<Mesh>(plane2_geometry, plane2_material, glm::vec3{0.0f, 1.5f, 0.0f});
    plane2->set_name("Plane2");

    auto plane3 = std::make_shared<Mesh>(plane3_geometry, plane3_material, glm::vec3{3.0f, 1.5f, 0.0f});
    plane3->set_name("Plane3");


    // * * *CIRCLES * * *
    auto circle1 = std::make_shared<Mesh>(circle1_geometry, circle1_material, glm::vec3{-3.0f, 0.0f, 0.0f});
    circle1->set_name("Circle1");

    auto circle2 = std::make_shared<Mesh>(circle2_geometry, circle2_material, glm::vec3{0.0f, 0.0f, 0.0f});
    circle2->set_name("Circle2");

    auto circle3 = std::make_shared<Mesh>(circle3_geometry, circle3_material, glm::vec3{3.0f, 0.0f, 0.0f});
    circle3->set_name("Circle3");


    // * * * SPHERES * * *
    auto sphere1 = std::make_shared<Mesh>(sphere1_geometry, sphere1_material, glm::vec3{-3.0f, -1.5f, 0.0f});
    sphere1->set_name("Sphere1");

    auto sphere2 = std::make_shared<Mesh>(sphere2_geometry, sphere2_material, glm::vec3{0.0f, -1.5f, 0.0f});
    sphere2->set_name("Sphere2");

    auto sphere3 = std::make_shared<Mesh>(sphere3_geometry, sphere3_material, glm::vec3{3.0f, -1.5f, 0.0f});
    sphere3->set_name("Sphere3");


    std::vector<std::shared_ptr<Object>> objects;

    objects.push_back(plane1);
    objects.push_back(plane2);
    objects.push_back(plane3);

    objects.push_back(circle1);
    objects.push_back(circle2);
    objects.push_back(circle3);

    objects.push_back(sphere1);
    objects.push_back(sphere2);
    objects.push_back(sphere3);

    auto scene = std::make_shared<Scene>(objects);
    auto root = scene->get_root();

    auto &camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    for (;;) {
        window->poll();

        // TODO
        plane1->set_rotation_x(plane1->get_rotation_x() - 0.01f);
        plane1->set_rotation_z(plane1->get_rotation_z() - 0.01f);

        plane2->set_rotation_x(plane2->get_rotation_x() - 0.01f);
        plane2->set_rotation_y(plane2->get_rotation_y() - 0.01f);

        plane3->set_rotation_y(plane3->get_rotation_y() - 0.01f);
        plane3->set_rotation_z(plane3->get_rotation_z() - 0.01f);


        circle1->set_rotation_x(circle1->get_rotation_x() - 0.01f);
        circle1->set_rotation_z(circle1->get_rotation_z() - 0.01f);

        circle2->set_rotation_x(circle2->get_rotation_x() - 0.01f);
        circle2->set_rotation_y(circle2->get_rotation_y() - 0.01f);

        circle3->set_rotation_y(circle3->get_rotation_y() - 0.01f);
        circle3->set_rotation_z(circle3->get_rotation_z() - 0.01f);


        sphere1->set_rotation_x(sphere1->get_rotation_x() - 0.01f);
        sphere1->set_rotation_z(sphere1->get_rotation_z() - 0.01f);

        sphere2->set_rotation_x(sphere2->get_rotation_x() - 0.01f);
        sphere2->set_rotation_y(sphere2->get_rotation_y() - 0.01f);

        sphere3->set_rotation_y(sphere3->get_rotation_y() - 0.01f);
        sphere3->set_rotation_z(sphere3->get_rotation_z() - 0.01f);

        renderer.render();
    }
}
