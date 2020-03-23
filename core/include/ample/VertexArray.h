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

class VertexArray final : public utils::Noncopyable
{
public:
    VertexArray(const std::vector<Vector3d<float>> &shape,
                const normalsMode normalsType,
                const std::vector<Vector3d<float>> &normals,
                const std::string &texturePath = "../../demo/textures/lena512.png"); // TODO: remove lena's default path
    void execute();
    void setColor256(double r, double g, double b);
    const std::vector<Vector3d<float>> verticies() const;
    ~VertexArray();

private:
    std::vector<Vector3d<float>> _shape;
    GLuint _vertexBufferId;
    GLuint _textureBufferId;
    GLuint _normalBufferId;
    GLuint _normalLinesBufferId;
    GLsizei _totalVerts;
    normalsMode _normalsMode;
    GLsizei _normalStride;
    std::unique_ptr<Texture> _texture;
};
} // namespace ample::graphics
