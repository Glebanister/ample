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
VertexArray::VertexBuffer::Executor::Executor(GLint size,
                                              GLenum type,
                                              GLboolean normalized,
                                              GLsizei stride,
                                              const void *pointer,
                                              VertexBuffer &buf)
    : _index(buf._bufferId)
{
    glEnableVertexAttribArray(_index);
    glBindBuffer(GL_ARRAY_BUFFER, buf._bufferId);
    glVertexAttribPointer(
        buf._bufferId,
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

VertexArray::VertexBuffer::VertexBuffer(GLsizeiptr size, void *pointer)
{
    glGenBuffers(1, &_bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferId);
    glBufferData(GL_ARRAY_BUFFER, size, pointer, GL_STATIC_DRAW);
}

VertexArray::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_bufferId);
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
        result[i * 2 + 0] = vector[i].x;
        result[i * 2 + 1] = vector[i].y;
        result[i * 2 + 1] = vector[i].z;
    }
    return result;
}

VertexArray::VertexArray(const std::vector<Vector3d<float>> &coords,
                         const std::vector<Vector2d<float>> &uvCoords,
                         const std::vector<Vector3d<float>> &normal)
    : _totalVerts(coords.size()),
      _xyzCoordsBuffer(sizeof(GLfloat) * coords.size() * 3, static_cast<void *>(expand(coords).data())),
      _uvCoordsBuffer(sizeof(GLfloat) * coords.size() * 2, static_cast<void *>(expand(uvCoords).data())),
      _normalsBuffer(sizeof(GLfloat) * coords.size() * 3, static_cast<void *>(expand(normal).data()))

{
    exception::OpenGLException::handle();
}

void VertexArray::execute()
{
    VertexBuffer::Executor execXYZ{3, GL_FLOAT, GL_FALSE, 0, NULL, _xyzCoordsBuffer};
    VertexBuffer::Executor execUV{2, GL_FLOAT, GL_FALSE, 0, NULL, _uvCoordsBuffer};
    VertexBuffer::Executor execTEX{3, GL_FLOAT, GL_FALSE, 0, NULL, _normalsBuffer};
    glDrawArrays(GL_TRIANGLES, 0, _totalVerts);
}
} // namespace ample::graphics
