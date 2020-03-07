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
    GraphicalObject2d() = delete;
    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape);

    virtual float getX() const = 0;
    virtual float getY() const = 0;
    virtual float getZ() const = 0;

    virtual float getAngleX() const = 0;
    virtual float getAngleY() const = 0;
    virtual float getAngleZ() const = 0;

    virtual float getScaleX() const = 0;
    virtual float getScaleY() const = 0;
    virtual float getScaleZ() const = 0;

    void draw(Vector3d<float> &&scaled = {1.0, 1.0, 1.0},
              Vector3d<float> &&rotated = {0.0, 0.0, 0.0},
              Vector3d<float> &&translated = {0.0, 0.0, 0.0}) override;
    void setRatio(float);
    float getRatio() const;

    void setColor256(float r, float g, float b);

protected:
    float _ratio = 1.0;
    std::unique_ptr<VertexArray> _vertexArray;
    const GLuint _programId;
    const GLuint _modelMatrixId;
};
} // namespace ample::graphics
