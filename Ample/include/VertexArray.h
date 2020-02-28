#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "Vector2d.h"
#include "Vector3d.h"

namespace ample::graphics
{
class VertexArray final
{
public:
    VertexArray() = delete;
    VertexArray(const VertexArray &other) = delete;
    VertexArray &operator=(const VertexArray &other) = delete;

    template <typename T>
    VertexArray(const std::vector<Vector2d<T>> &shape)
        : _data(std::vector<GLfloat>(shape.size() * 3))
    {
        for (size_t i = 0; i < shape.size(); ++i)
        {
            _data[i * 3] = shape[i].x;
            _data[i * 3 + 1] = shape[i].y;
            _data[i * 3 + 2] = 0;
        }
        _sendToOpenGL();
    }

    template <typename T>
    VertexArray(const std::vector<Vector3d<T>> &shape)
        : _data(std::vector<GLfloat>(shape.size()))
    {
        for (size_t i = 0; i < shape.size(); ++i)
        {
            _data[i * 3] = shape[i].x;
            _data[i * 3 + 1] = shape[i].y;
            _data[i * 3 + 2] = shape[i].z;
        }
        _sendToOpenGL();
    }

    void execute();

    GLfloat *data();

private:
    std::vector<GLfloat> _data;
    GLuint _vertexArrayId;
    GLuint _vertexBufferId;
    void _sendToOpenGL();
    GLsizei _total;
};
} // namespace ample::graphics
