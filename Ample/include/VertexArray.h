#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "Vector2d.h"
#include "Vector3d.h"
#include "Noncopyable.h"

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
                const std::vector<Vector3d<float>> &normals);
    void execute();
    void setColor256(double r, double g, double b);
    const std::vector<Vector3d<float>> &verticies() const;
    ~VertexArray();

private:
    std::vector<GLfloat> _coords;
    std::vector<GLfloat> _normals;
    std::vector<GLfloat> _normalsLines;
    std::vector<Vector3d<float>> _shape;
    GLuint _vertexBufferId;
    GLuint _normalBufferId;
    GLuint _normalLinesBufferId;
    GLsizei _totalVerts;
    normalsMode _normalsMode;
    GLint _colorVectorId;
    double _r = 0.5, _g = 0.5, _b = 0.5;
    GLsizei _normalStride;
};
} // namespace ample::graphics
