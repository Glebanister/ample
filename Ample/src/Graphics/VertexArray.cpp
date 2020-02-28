#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <iostream>

#include "VertexArray.h"
#include "Exception.h"

namespace ample::graphics
{
void VertexArray::_sendToOpenGL()
{
    glGenVertexArrays(1, &_vertexArrayId);
    glBindVertexArray(_vertexArrayId);
    glGenBuffers(1, &_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_data.data()), _data.data(), GL_STATIC_DRAW);
    _total = _data.size() / 3;
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
    glDrawArrays(GL_TRIANGLES, 0, _total); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

GLfloat *VertexArray::data()
{
    return _data.data();
}
} // namespace ample::graphics
