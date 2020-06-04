#pragma once
#include "GameCharacter.hpp"
#include <stdlib.h>

class Player : public GameCharacter {
public:
    enum ShootingState {
        Shooting,
        Idle
    };
    ShootingState _shooting_state{Idle};

    Player(const glm::vec3 &position, float size, const game_character_sprite_data_type &game_character_sprite_data)
        : GameCharacter (position, size, game_character_sprite_data)
    {
        auto[player_indices, player_vertices] = geometry_generators::generate_plane_geometry_data(2, 2, 1, 1);
        auto player_geometry = std::make_shared<ES2Geometry>(player_indices, player_vertices);
        auto player_material = std::make_shared<ES2ConstantMaterial>();
        player_material->set_texture_1(_texture);
        player_material->set_blending_enabled(true);
        player_material->set_overlay(true);

        _mesh = std::make_shared<Mesh>(player_geometry, player_material);
        _mesh->set_position(position);
        _bounding_volume = Sphere{_mesh->get_position(), size / 2};
    }

    ~Player() {}

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
            if (_shooting_state == Shooting) {
                if (_update_request++ % _update_rate != 0) {
                    return;
                }

                unsigned int frame = _texture_frame + 1;
                _set_texture_frame(frame % _first_dying_texture_frame);
            } else {
                if (_update_request++ % _update_rate != 0) {
                    return;
                }

                _set_texture_frame(0);
            }
        }
    }

    const State &get_state()
    {
        return _state;
    }

    void set_shooting_state(bool shooting_state)
    {
        _shooting_state = shooting_state ? Shooting : Idle;
    }

    void kill() {
        if (_state == Alive) {
            _state = Dying;
            _set_texture_frame(_first_dying_texture_frame);
        }
    }
};
