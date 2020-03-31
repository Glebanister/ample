#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexArray.h"
#include "Exception.h"
#include "Debug.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
struct VertexArrayImpl
{
    VertexArrayImpl() = default;
    VertexArrayImpl(AbstractIO &input)
    {
        input.read("coords", coords);
        input.read("uvCoords", uvCoords);
        input.read("normals", normals);
    }

    std::vector<Vector3d<float>> coords;
    std::vector<Vector3d<float>> uvCoords;
    std::vector<Vector3d<float>> normals;
};

VertexArray::VertexBuffer::Executor::Executor(GLuint index,
                                              GLint size,
                                              GLenum type,
                                              GLboolean normalized,
                                              GLsizei stride,
                                              const void *pointer,
                                              VertexBuffer &buf)
    : _index(index)
{
    glEnableVertexAttribArray(_index);
    glBindBuffer(GL_ARRAY_BUFFER, buf._bufferId);
    glVertexAttribPointer(
        _index,
        size,
        type,
        normalized,
        stride,
        pointer);
}

VertexArray::VertexBuffer::Executor::~Executor()
{
    glDisableVertexAttribArray(_index);
}

std::vector<float> expand(const std::vector<Vector2d<float>> &vector)
{
    std::vector<GLfloat> result(vector.size() * 2);
    for (size_t i = 0; i < vector.size(); ++i)
    {
        result[i * 2 + 0] = vector[i].x;
        result[i * 2 + 1] = vector[i].y;
    }
    return result;
}

std::vector<float> expand(const std::vector<Vector3d<float>> &vector)
{
    std::vector<GLfloat> result(vector.size() * 3);
    for (size_t i = 0; i < vector.size(); ++i)
    {
        result[i * 3 + 0] = vector[i].x;
        result[i * 3 + 1] = vector[i].y;
        result[i * 3 + 2] = vector[i].z;
    }
    return result;
}

VertexArray::VertexBuffer::VertexBuffer(GLsizeiptr size, void *pointer)
{
    glGenBuffers(1, &_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
}

VertexArray::VertexBuffer::VertexBuffer(std::vector<Vector2d<float>> &data)
    : VertexBuffer(sizeof(GLfloat) * data.size() * 2, static_cast<void *>(expand(data).data())) {}

VertexArray::VertexBuffer::VertexBuffer(std::vector<Vector3d<float>> &data)
    : VertexBuffer(sizeof(GLfloat) * data.size() * 3, static_cast<void *>(expand(data).data())) {}

VertexArray::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_bufferId);
}

VertexArray::VertexArray(const std::vector<Vector3d<float>> &coords,
                         const std::vector<Vector2d<float>> &uvCoords,
                         const std::vector<Vector3d<float>> &normal)
    : _coords(coords),
      _uvCoords(uvCoords),
      _normalsBuffer(normal),
      _xyzCoordsBuffer(coords),
      _uvCoordsBuffer(uvCoords),
      _normalsBuffer(normal),
      _totalVerts(coords.size())

{
    exception::OpenGLException::handle();
}

VertexArray::VertexArray(filing::JsonIO &input)
    : VertexArray(input.read<std::vector<Vector2d<float>>>("coords"),
                  input.read<std::vector<Vector2d<float>>>("uvCoords"),
                  input.read<std::vector<Vector3d<float>>>("normals"))
{
}

void VertexArray::dump(filing::JsonIO &output)
{
    output.write<std::vector<Vector3d<float>>>("coords", _coords);
    output.write<std::vector<Vector2d<float>>>("uvCoords", _uvCoords);
    output.write<std::vector<Vector3d<float>>>("normals", _normals);
}

void VertexArray::execute()
{
    VertexBuffer::Executor execXYZ{0, 3, GL_FLOAT, GL_FALSE, 0, NULL, _xyzCoordsBuffer};
    VertexBuffer::Executor execUV{1, 2, GL_FLOAT, GL_FALSE, 0, NULL, _uvCoordsBuffer};
    VertexBuffer::Executor execNormals{2, 3, GL_FLOAT, GL_FALSE, 0, NULL, _normalsBuffer};
    glDrawArrays(GL_TRIANGLES, 0, _totalVerts);
}
} // namespace ample::graphics
