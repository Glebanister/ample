#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "GraphicalObject.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "VertexArray.h"
#include "Color.h"

namespace ample::filing
{
class GraphicalObject2dIO;
}

namespace ample::graphics
{
class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float depth,
                      const float z);

    void drawSelf(const glm::mat4 &) override;

    void setFaceColor256(Color color);
    void setSideColor256(Color color);

protected:
    friend class ample::filing::GraphicalObject2dIO;

    std::unique_ptr<VertexArray> _sideArray;
    std::unique_ptr<VertexArray> _faceArray;
    const GLuint _programId;
    const GLuint _modelMatrixId;
    float _depth;
    float _z;
};
} // namespace ample::graphics
