#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "GraphicalObject.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "VertexArray.h"

namespace ample::graphics
{
class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float depth,
                      const float z);

    void draw(Vector3d<float> &&scaled = {1.0, 1.0, 1.0},
              Vector3d<float> &&rotated = {0.0, 0.0, 0.0},
              Vector3d<float> &&translated = {0.0, 0.0, 0.0}) override;

    void setColor256(float r, float g, float b);

protected:
    std::unique_ptr<VertexArray> _sideArray;
    std::unique_ptr<VertexArray> _faceArray;
    const GLuint _programId;
    const GLuint _modelMatrixId;
    float _depth;
    float _z;
};
} // namespace graphics
