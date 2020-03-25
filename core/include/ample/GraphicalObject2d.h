#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>

#include "GraphicalObject.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "VertexArray.h"
#include "VertexArrayFace2d.h"
#include "VertexArraySide2d.h"
#include "Color.h"

namespace ample::filing
{
class GraphicalObject2dIO;
}

namespace ample::graphics
{
class GraphicalObject2d;

struct GraphicalObject2dRaw final
{
    const std::vector<graphics::Vector2d<float>> graphicalShape;
    float depth;
    float z;

    const std::string faceTexturePath;
    Vector2d<int> faceTextureSize;
    Vector2d<int> faceTexturePos;
    const Vector2d<textureMode> faceTextureMode;
    const channelMode faceChannelMode;

    const std::string sideTexturePath;
    Vector2d<int> sideTextureSize;
    Vector2d<int> sideTexturePos;
    const Vector2d<textureMode> sideTextureMode;
    const normalsMode sideNormalsMode;
    const channelMode sideChannelMode;

    GraphicalObject2dRaw(const std::vector<graphics::Vector2d<float>> graphicalShape,
                         float depth,
                         float z,
                         const std::string faceTexturePath,
                         Vector2d<int> faceTextureSize,
                         Vector2d<int> faceTexturePos,
                         const Vector2d<textureMode> faceTextureMode,
                         const channelMode faceChannelMode,
                         const std::string sideTexturePath,
                         Vector2d<int> sideTextureSize,
                         Vector2d<int> sideTexturePos,
                         const Vector2d<textureMode> sideTextureMode,
                         const channelMode sideChannelMode,
                         const normalsMode sideNormalsMode);

    GraphicalObject2dRaw(const GraphicalObject2d &other);
};

class GraphicalObject2d : public GraphicalObject
{
public:
    GraphicalObject2d(const GraphicalObject2dRaw &raw);

    GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                      const float depth,
                      const float z);

    void drawSelf() override;

protected:
    friend class ample::graphics::GraphicalObject2dRaw;
    friend class ample::filing::GraphicalObject2dIO;

    GraphicalObject2dRaw _raw;

    std::unique_ptr<VertexArrayFace2d> _faceArray;
    std::unique_ptr<VertexArraySide2d> _sideArray;
};
} // namespace ample::graphics
