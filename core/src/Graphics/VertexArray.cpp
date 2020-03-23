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
                         const std::vector<Vector3d<float>> &normals,
                         const std::string &texrutePath)
    : _shape(shape),
      _totalVerts(shape.size()),
      _normalsMode(normMode)
{
    {
        DEBUG("Generating vertex buffer");
        std::vector<GLfloat> _coords(shape.size() * 3);
        for (size_t i = 0; i < shape.size(); ++i)
        {
            _coords[i * 3 + 0] = shape[i].x;
            _coords[i * 3 + 1] = shape[i].y;
            _coords[i * 3 + 2] = shape[i].z;
        }
        glGenBuffers(1, &_vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _coords.size(), _coords.data(), GL_STATIC_DRAW);
    }

    {
        DEBUG("Generating texture buffer");
        std::vector<GLfloat> _texCoords(shape.size() * 2);
        // int texWidth = _texture.getWidth();
        // int texHeight = _texture.getHeight();
        for (size_t i = 0; i < shape.size(); ++i)
        {
            _texCoords[i * 2 + 0] = shape[i].x;
            _texCoords[i * 2 + 1] = shape[i].y;
        }
        glGenBuffers(1, &_textureBufferId);
        glBindBuffer(GL_TEXTURE_BUFFER, _textureBufferId);
        glBufferData(GL_TEXTURE_BUFFER, sizeof(GLfloat) * _texCoords.size(), _texCoords.data(), GL_STATIC_DRAW);
    }

    {
        DEBUG("Generating normals buffer");
        std::vector<GLfloat> _normals(normals.size() * 3);
        for (size_t i = 0; i < normals.size(); ++i)
        {
            _normals[i * 3] = normals[i].x;
            _normals[i * 3 + 1] = normals[i].y;
            _normals[i * 3 + 2] = normals[i].z;
        }

        glGenBuffers(1, &_normalBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _normals.size(), _normals.data(), GL_STATIC_DRAW);
        _texture = std::make_unique<Texture>(texrutePath);
        glBindBuffer(GL_TEXTURE_BUFFER, 0);
    }

    {
        // DEBUG("DEBUG: Generating normal lines buffer");
        // std::vector<GLfloat> _normalsLines(normals.size() * 6);
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
    }

    exception::OpenGLException::handle();
}

void VertexArray::execute()
{
    DEBUG("Enabling 0 arrrib");
    glEnableVertexAttribArray(0);
    exception::OpenGLException::handle();
    DEBUG("Enabling 0 arrrib done");
    DEBUG("Binding");
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    exception::OpenGLException::handle();
    DEBUG("Binding done");
    DEBUG("Sending vertex attrib pointer");
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    exception::OpenGLException::handle();
    DEBUG("Sending vertex attrib pointer done");

    DEBUG("Enabling 1 arrrib");
    glEnableVertexAttribArray(1);
    exception::OpenGLException::handle();
    DEBUG("Enabling 1 arrrib done");
    DEBUG("Binding buffer");
    glBindBuffer(GL_TEXTURE_BUFFER, _textureBufferId);
    exception::OpenGLException::handle();
    DEBUG("Binding buffer done");
    DEBUG("Sending vertex attrib pointer");
    glVertexAttribPointer(
        1,        // attribute
        2,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    exception::OpenGLException::handle();
    DEBUG("Sending vertex attrib pointer done");

    DEBUG("Enabling 2 arrrib");
    glEnableVertexAttribArray(2);
    exception::OpenGLException::handle();
    DEBUG("Enabling 1 arrrib done");
    DEBUG("Binding buffer");
    glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
    exception::OpenGLException::handle();
    DEBUG("Binding buffer done");
    DEBUG("Sending vertex attrib pointer");
    glVertexAttribPointer(
        2,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    exception::OpenGLException::handle();
    DEBUG("Sending vertex attrib pointer done");

    DEBUG("Drawing arrays");
    glDrawArrays(GL_TRIANGLES, 0, _totalVerts);
    exception::OpenGLException::handle();
    DEBUG("Drawing arrays done");


    DEBUG("disabling 0");
    glDisableVertexAttribArray(0);
    exception::OpenGLException::handle();
    DEBUG("disabling 0 done");
    DEBUG("disabling 1");
    glDisableVertexAttribArray(1);
    exception::OpenGLException::handle();
    DEBUG("disabling 1 done");
    DEBUG("disabling 2");
    glDisableVertexAttribArray(2);
    exception::OpenGLException::handle();
    DEBUG("disabling 2 done");
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

void VertexArray::setColor256(double, double, double)
{
    // TODO: remove stub
}

const std::vector<Vector3d<float>> &VertexArray::verticies() const
{
    return _shape;
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &_vertexBufferId);
}
} // namespace ample::graphics
