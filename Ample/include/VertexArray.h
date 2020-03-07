#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

#include "Vector2d.h"
#include "Vector3d.h"
#include "Noncopyable.h"

namespace ample::graphics
{
enum glDrawMode
{
    POLYGON,
    QUAD_STRIP,
};

class VertexArray final : public utils::Noncopyable
{
public:
    VertexArray(const std::vector<Vector3d<float>> &shape, const GLuint mode);
    void execute();
    void setColor256(double r, double g, double b);
    ~VertexArray();

private:
    std::vector<GLfloat> _data;
    GLuint _vertexBufferId;
    GLsizei _total;
    double _r = 0.5, _g = 0.5, _b = 0.5;
    GLint _drawMode;
};
} // namespace ample::graphics
