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
VertexArray::VertexArray(const std::vector<Vector3d<float>> &shape,
                         const normalsMode normMode,
                         const std::vector<Vector3d<float>> &normals)
    : _coords(shape.size() * 3),
      _normals(normals.size() * 3),
      _normalsLines(normals.size() * 6),
      _shape(shape),
      _totalVerts(shape.size()),
      _normalsMode(normMode),
      _colorVectorId(glGetUniformLocation(shaders::ShaderProcessor::instance().getProgramId(),
                                          "object_color"))
{
    DEBUG("Generating vertex buffer");
    for (size_t i = 0; i < shape.size(); ++i)
    {
        _coords[i * 3 + 0] = shape[i].x;
        _coords[i * 3 + 1] = shape[i].y;
        _coords[i * 3 + 2] = shape[i].z;
    }
    glGenBuffers(1, &_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _coords.size(), _coords.data(), GL_STATIC_DRAW);

    DEBUG("Generating normals buffer");
    for (size_t i = 0; i < normals.size(); ++i)
    {
        _normals[i * 3] = normals[i].x;
        _normals[i * 3 + 1] = normals[i].y;
        _normals[i * 3 + 2] = normals[i].z;
    }

    glGenBuffers(1, &_normalBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _normals.size(), _normals.data(), GL_STATIC_DRAW);

    // DEBUG("DEBUG: Generating normal lines buffer");
    // for (size_t i = 0; i < normals.size(); ++i)
    // {
    //     _normalsLines[i * 6 + 0] = shape[i].x;
    //     _normalsLines[i * 6 + 1] = shape[i].y;
    //     _normalsLines[i * 6 + 2] = shape[i].z;
    //     _normalsLines[i * 6 + 3] = shape[i].x + normals[i].x * 5;
    //     _normalsLines[i * 6 + 4] = shape[i].y + normals[i].y * 5;
    //     _normalsLines[i * 6 + 5] = shape[i].z + normals[i].z * 5;
    // }

    // glGenBuffers(1, &_normalLinesBufferId);
    // glBindBuffer(GL_ARRAY_BUFFER, _normalLinesBufferId);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _normalsLines.size(), _normalsLines.data(), GL_STATIC_DRAW);

    exception::OpenGLException::handle();
}

void VertexArray::execute()
{
    glm::vec3 color{_r, _g, _b};
    glUniform3fv(_colorVectorId, 1, glm::value_ptr(color));

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

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
    glVertexAttribPointer(
        1,             // attribute
        3,             // size
        GL_FLOAT,      // type
        GL_FALSE,      // normalized?
        0, // stride
        (void *)0      // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, _totalVerts);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    // DEBUG normals
    // glm::vec3 colorNormals{1.0, 0, 0};
    // glUniform3fv(_colorVectorId, 1, glm::value_ptr(colorNormals));

    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, _normalLinesBufferId);
    // glVertexAttribPointer(
    //     0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //     3,        // size
    //     GL_FLOAT, // type
    //     GL_FALSE, // normalized?
    //     0,        // stride
    //     (void *)0 // array buffer offset
    // );
    // glLineWidth(3);
    // glPointSize(10);
    // glDrawArrays(GL_LINES, 0, _totalVerts * 2);
    // glDisableVertexAttribArray(0);
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
