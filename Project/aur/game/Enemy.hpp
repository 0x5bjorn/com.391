#pragma once
#include "GameCharacter.hpp"

class Enemy : public GameCharacter {
public:
    float _speed{1.0f};
    glm::vec3 _velocity{0.0f};

    std::shared_ptr<Camera> _target{nullptr};

    Enemy(const glm::vec3 &position, float size, const game_character_sprite_data_type &game_character_sprite_data, float speed)
        : GameCharacter (position, size, game_character_sprite_data), _speed{speed}
    {
        auto[billboard_indices, billboard_vertices] = geometry_generators::generate_plane_geometry_data(size, size, 1, 1);
        auto billboard_geometry = std::make_shared<ES2Geometry>(billboard_indices, billboard_vertices);
        auto billboard_material = std::make_shared<ES2ConstantMaterial>();
        billboard_material->set_texture_1(_texture);
        billboard_material->set_face_culling_enabled(false);
        billboard_material->set_blending_enabled(true);
        billboard_material->set_transparent(true);

        _mesh = std::make_shared<Mesh>(billboard_geometry, billboard_material);
        _mesh->set_position(position);
        _bounding_volume = Sphere{_mesh->get_position(), size / 2};
    }

    ~Enemy() {}

    void set_target(const std::shared_ptr<Camera> &target)
    {
        _target = target;
    }

    void update(float delta_time)
    {
        if (_state == Dying) {
            if (_update_request++ % _update_rate != 0) {
                return;
            }

            unsigned int frame = _texture_frame + 1;
            if (frame >= _texture_frames) {
                _state = Dead;
            } else {
                _set_texture_frame(frame);
            }
        } else if (_state == Alive) {
            if (_update_request++ % _update_rate != 0) {
                return;
            }

            _set_texture_frame((_texture_frame + 1) % _first_dying_texture_frame);

            glm::vec3 direction = _target->get_position() - _mesh->get_position();
            _mesh->set_y(_position.y);
            _mesh->add_to_position(direction*_speed);
            _bounding_volume.add_to_center(direction*_speed);
        }

        _mesh->billboard_toward_camera(_target);
    }

    void kill() {
        if (_state == Alive) {
            _state = Dying;
            _set_texture_frame(_first_dying_texture_frame);
        }
    }
};
