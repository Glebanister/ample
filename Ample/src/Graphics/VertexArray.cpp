#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <iostream>

#include "VertexArray.h"
#include "Exception.h"
#include "Debug.h"

namespace ample::graphics
{
void VertexArray::_sendToOpenGL()
{
    DEBUG("Generating vertex buffer");
    glGenBuffers(1, &_vertexBufferId);
    DEBUG("Binding vertex buffer");
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    DEBUG("Sending buffer data");
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _data.size(), _data.data(), GL_STATIC_DRAW);
    _total = _data.size() / 3;
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
    // glColor3d(_r, _g, _b);
    glDrawArrays(GL_TRIANGLES, 0, _total); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

GLfloat *VertexArray::data()
{
    return _data.data();
}

void VertexArray::setColor256(double r, double g, double b)
{
    _r = r;
    _g = g;
    _b = b;
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &_vertexBufferId);
}
} // namespace ample::graphics
