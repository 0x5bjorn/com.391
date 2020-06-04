#pragma once
#include "aur.hpp"

using namespace aur;

class RoomComponent {
public:
    // enum Type {
    //     Wall,
    //     Ground,
    //     Ceiling
    // };
    // Type _type{};

    glm::vec3 _position;
    glm::vec3 _rotation;

    std::shared_ptr<Mesh> _mesh;

    std::shared_ptr<ES2Texture> _texture;

    RoomComponent(const glm::vec3 &position, const glm::vec3 &rotation, float size, const std::string texture_file)
        : _position{position}, _rotation{rotation}
    {
        auto[room_component_data, room_component_width, room_component_height, room_component_channels] = file_utilities::read_image_file(texture_file);
        _texture = std::make_shared<ES2Texture>(room_component_data, room_component_width, room_component_height, room_component_channels);
        _texture->set_enabled(true);
        _texture->set_wrap_mode_s(Texture::WrapMode::Repeat);
        _texture->set_wrap_mode_t(Texture::WrapMode::Repeat);
        _texture->set_transformation_enabled(true);
        glm::mat4 room_component_texture_transformation_matrix{1.0f};
        room_component_texture_transformation_matrix[0] = glm::vec4{10.0f, 0.0f, 0.0f, 0.0f};
        room_component_texture_transformation_matrix[1] = glm::vec4{0.0f, 10.0f, 0.0f, 0.0f};
        room_component_texture_transformation_matrix[2] = glm::vec4{0.0f, 0.0f, 10.0f, 0.0f};
        room_component_texture_transformation_matrix[3] = glm::vec4{0.0f, 0.0f, 0.0f, 10.0f};
        _texture->set_transformation_matrix(room_component_texture_transformation_matrix);

        auto[room_component_indices, room_component_vertices] = geometry_generators::generate_plane_geometry_data(size, size, 1, 1);
        auto room_component_geometry = std::make_shared<ES2Geometry>(room_component_indices, room_component_vertices);
        auto room_component_material = std::make_shared<ES2PhongMaterial>();
        room_component_material->set_texture_1(_texture);
        room_component_material->set_specular_exponent(1.0f);
        room_component_material->set_specular_color(glm::vec3{0.0f});
        room_component_material->set_diffuse_color(glm::vec4{0.25f});

        _mesh = std::make_shared<Mesh>(room_component_geometry, room_component_material);
        _mesh->set_position(_position);
        _mesh->set_rotation(_rotation);
    }

    ~RoomComponent() {}

    const std::shared_ptr<Mesh> &get_mesh()
    {
        return _mesh;
    }
};
