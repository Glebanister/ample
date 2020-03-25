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
                         const std::vector<Vector2d<float>> &uvCoords,
                         const std::vector<Vector3d<float>> &normals,
                         const std::string &texrutePath,
                         const Vector2d<float> &textureSize,
                         const Vector2d<float> &texturePosition)
    : _totalVerts(shape.size())
{
    {
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
        DEBUG("Generating uv buffer");
        std::vector<GLfloat> _texCoords(uvCoords.size() * 2);
        for (size_t i = 0; i < shape.size(); ++i)
        {
            _texCoords[i * 2 + 0] = uvCoords[i].x;
            _texCoords[i * 2 + 1] = uvCoords[i].y;
        }
        glGenBuffers(1, &_textureBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, _textureBufferId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _texCoords.size(), _texCoords.data(), GL_STATIC_DRAW);
        _texture = std::make_unique<Texture>(texrutePath, textureSize, texturePosition);
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
    }

    exception::OpenGLException::handle();
}

void VertexArray::execute()
{
    glBindTexture(GL_TEXTURE_2D, _texture->getGlTextureId());
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferId);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        NULL      // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _textureBufferId);
    glVertexAttribPointer(
        1,        // attribute
        2,        // size
        GL_FLOAT, // type
        GL_TRUE,  // normalized?
        0,        // stride
        NULL      // array buffer offset
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
    glVertexAttribPointer(
        2,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        NULL      // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, _totalVerts);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void VertexArray::setColor256(double, double, double)
{
    // TODO: remove stub
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &_vertexBufferId);
    glDeleteBuffers(1, &_textureBufferId);
    glDeleteBuffers(1, &_normalBufferId);
}
} // namespace ample::graphics
