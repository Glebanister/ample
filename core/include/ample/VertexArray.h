#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <memory>

#include "Vector2d.h"
#include "Vector3d.h"
#include "Noncopyable.h"
#include "Texture.h"

namespace ample::graphics
{
enum class normalsMode
{
    SINGLE,
    VERTEX,
    FACE,
};

enum class textureMode
{
    TILE,
    STRETCH,
};

class VertexArray : public utils::Noncopyable
{
public:
    VertexArray(const std::vector<Vector3d<float>> &coords,
                const std::vector<Vector2d<float>> &uvCoords,
                const std::vector<Vector3d<float>> &normals,
                const std::string &texturePath);
    void execute();
    void setColor256(double r, double g, double b);
    ~VertexArray();

private:
    GLuint _vertexBufferId;
    GLuint _textureBufferId;
    GLuint _normalBufferId;
    GLuint _normalLinesBufferId;
    GLsizei _totalVerts;
    GLsizei _normalStride;
    std::unique_ptr<Texture> _texture;
};
} // namespace ample::graphics
