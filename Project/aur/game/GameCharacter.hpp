#pragma once
#include "aur.hpp"

using namespace aur;

class GameCharacter {
public:
    typedef std::tuple<const std::string, unsigned int, unsigned int> game_character_sprite_data_type;

    enum State {
        Alive,
        Dying,
        Dead
    };
    State _state{Alive};

    glm::vec3 _position;

    int _update_request{0};
    int _update_rate{10};

    std::shared_ptr<Mesh> _mesh;
    Sphere _bounding_volume{glm::vec3{0.0f}, 1.0f};

    std::shared_ptr<ES2Texture> _texture;
    unsigned int _texture_frame{0};
    unsigned int _texture_frames{1};
    unsigned int _first_dying_texture_frame{0};

    GameCharacter(const glm::vec3 &position, float size, const game_character_sprite_data_type &game_character_sprite_data)
        : _position{position}
    {
        const auto&[sprite_file, sprite_frame_count, first_dying_texture_frame] = game_character_sprite_data;

        auto[image_data, image_width, image_height, image_channels] = file_utilities::read_image_file(sprite_file);
        _texture = std::make_shared<ES2Texture>(image_data, image_width, image_height, image_channels);
        _texture->set_minification_filter(Texture::FilterType::Nearest);
        _texture->set_magnification_filter(Texture::FilterType::Nearest);
        _texture->set_mode(Texture::Mode::Modulation);
        _texture->set_transformation_enabled(true);
        _set_texture_frames(sprite_frame_count);
        _set_first_dying_texture_frame(first_dying_texture_frame);
    }

    ~GameCharacter() {}

    const std::shared_ptr<Mesh> &get_mesh()
    {
        return _mesh;
    }

    bool intersects_with_ray(const Ray &ray) const
    {
        return ray.intersects_with_sphere(_bounding_volume).first;
    }

    void kill();
    void update();

protected:
    void _set_texture_frame(unsigned int texture_frame)
    {
        _texture_frame = texture_frame;

        glm::mat4 matrix = _texture->get_transformation_matrix();
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }

    void _set_texture_frames(unsigned int texture_frames)
    {
        _texture_frames = texture_frames;

        glm::mat4 matrix = _texture->get_transformation_matrix();
        matrix[0][0] = 1.0f / static_cast<float>(_texture_frames);
        matrix[3][0] = static_cast<float>(_texture_frame) / static_cast<float>(_texture_frames);
        _texture->set_transformation_matrix(matrix);
    }

    void _set_first_dying_texture_frame(unsigned int first_dying_texture_frame)
    {
        _first_dying_texture_frame = first_dying_texture_frame;
    }
};
