#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "materials/material.hpp"
#include "geometries/vertex.hpp"

#include <vector>
#include <utility>

#include <glm/glm.hpp>

namespace aur
{
    class Geometry
    {
    public:
        enum Type
        {
            Points,
            Lines,
            LineLoop,
            LineStrip,
            Triangles,
            TriangleFan,
            TriangleStrip
        };

        enum UsageStrategy
        {
            StaticStrategy,
            DynamicStrategy,
            StreamStrategy
        };

        explicit Geometry(std::vector<unsigned int> indices, std::vector<Vertex> vertices)
            : _indices(std::move(indices)), _vertices(std::move(vertices))
        {
            computeTangentVectors();
        }

        virtual ~Geometry() = default;

        [[nodiscard]] Type get_type() const
        {
            return _type;
        }

        void set_type(Type type)
        {
            _type = type;
        }

        [[nodiscard]] const std::vector<unsigned int> &get_indices() const
        {
            return _indices;
        }

        [[nodiscard]] const std::vector<Vertex> &get_vertices() const
        {
            return _vertices;
        }

        [[nodiscard]] UsageStrategy get_vertices_usage_strategy() const
        {
            return _vertices_usage_strategy;
        }

        void set_vertices_usage_strategy(UsageStrategy vertices_usage_strategy)
        {
            if (_vertices_usage_strategy != vertices_usage_strategy) {
                _vertices_usage_strategy = vertices_usage_strategy;
                _requires_vertices_update = true;
            }
        }

        [[nodiscard]] UsageStrategy get_indices_usage_strategy() const
        {
            return _indices_usage_strategy;
        }

        void set_indices_usage_strategy(UsageStrategy indices_usage_strategy)
        {
            if (_indices_usage_strategy != indices_usage_strategy) {
                _indices_usage_strategy = indices_usage_strategy;
                _requires_indices_update = true;
            }
        }

        [[nodiscard]] float get_line_width() const
        {
            return _line_width;
        }

        void set_line_width(float lineWidth)
        {
            _line_width = lineWidth;
        }

        void transform(glm::mat4 transformation_matrix)
        {
            for (auto &vertex : _vertices) {
                vertex.position = glm::vec3(transformation_matrix * glm::vec4(vertex.position, 1.0f));
            }
            _requires_vertices_update = true;
        }

        void computeTangentVectors() {

            std::vector<glm::vec3> tempTangent;
            std::vector<glm::vec3> tempBinormal;

            for (int i = 0; i < _vertices.size(); ++i) {
                tempTangent.push_back(glm::vec3(0.0f));
                tempBinormal.push_back(glm::vec3(0.0f));
            }

            for (int i = 0; i < _indices.size(); i+=3) {

                const Vertex v0 = _vertices[_indices[i]];
                const Vertex v1 = _vertices[_indices[i+1]];
                const Vertex v2 = _vertices[_indices[i+2]];

                glm::vec3 q1 = v1.position - v0.position;
                glm::vec3 q2 = v2.position - v0.position;
                float s1 = v1.texture1_coordinates.x - v0.texture1_coordinates.x;
                float s2 = v2.texture1_coordinates.x - v0.texture1_coordinates.x;
                float t1 = v1.texture1_coordinates.y - v0.texture1_coordinates.y;
                float t2 = v2.texture1_coordinates.y - v0.texture1_coordinates.y;

                glm::vec3 tangent = t2*q1 - t1*q2;
                tangent = glm::normalize(tangent);
                glm::vec3 binormal = -s2*q1 + s1*q2;
                binormal = glm::normalize(binormal);

                tempTangent[_indices[i]] += tangent;
                tempTangent[_indices[i+1]] += tangent;
                tempTangent[_indices[i+2]] += tangent;
                tempBinormal[_indices[i]] += binormal;
                tempBinormal[_indices[i+1]] += binormal;
                tempBinormal[_indices[i+2]] += binormal;
            }

            for (int i = 0; i < _indices.size(); ++i) {
                Vertex v = _vertices[_indices[i]];
                glm::vec3 t = tempTangent[_indices[i]];

                t -= v.normal * glm::dot(t, v.normal);
                t = glm::normalize(t);
                _vertices[_indices[i]].tangentDet = glm::vec4(t, v.tangentDet.w);

                if ( glm::dot(glm::cross(v.normal, t), tempBinormal[_indices[i]]) < 0.0f ) {
                    _vertices[_indices[i]].tangentDet.w = -1.0f;
                } else {
                    _vertices[_indices[i]].tangentDet.w = 1.0f;
                }
            }
        }

        virtual void update(const Material &material) = 0;

        virtual void use() = 0;

    protected:
        Type _type{Triangles};

        std::vector<unsigned int> _indices;
        std::vector<Vertex> _vertices;
        bool _requires_indices_update{true};
        bool _requires_vertices_update{true};

        UsageStrategy _vertices_usage_strategy{StaticStrategy};
        UsageStrategy _indices_usage_strategy{StaticStrategy};

        float _line_width{1.0f};
    };
}

#endif
