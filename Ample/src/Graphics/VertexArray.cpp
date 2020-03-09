#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <iostream>

#include "VertexArray.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::graphics
{
VertexArray::VertexArray(const std::vector<Vector3d<float>> &shape, const GLuint mode)
    : _data(shape.size() * 3), _shape(shape), _drawMode(mode)
{
    for (size_t i = 0; i < shape.size(); ++i)
    {
        _data[i * 3] = shape[i].x;
        _data[i * 3 + 1] = shape[i].y;
        _data[i * 3 + 2] = shape[i].z;
    }
    DEBUG(shape.size());
    DEBUG(_data.size());
    DEBUG("Generating vertex buffer");
    glGenBuffers(1, &_vertexBufferId);
    DEBUG("Binding vertex buffer");
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    DEBUG("Sending buffer data");
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _data.size(), _data.data(), GL_STATIC_DRAW);
    _total = shape.size();
    for (int i = 0; i < _data.size(); ++i)
    {
        std::cerr << _data[i] << ' ';
    }
    std::cerr << std::endl;
    exception::OpenGLException::handle();
}

void VertexArray::execute()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    glDrawArrays(_drawMode, 0, _total);
    glDisableVertexAttribArray(0);
}

void VertexArray::setColor256(double r, double g, double b)
{
    _r = r;
    _g = g;
    _b = b;
}

const std::vector<Vector3d<float>> VertexArray::verticies() const
{
    return _shape;
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &_vertexBufferId);
}
} // namespace ample::graphics
