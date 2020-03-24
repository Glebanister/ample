#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <memory>
#include <algorithm>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
GraphicalObject2dRaw::GraphicalObject2dRaw(const std::vector<graphics::Vector2d<float>> graphicalShape,
                                           float depth,
                                           float z,
                                           const std::string faceTexturePath,
                                           Vector2d<float> faceTexturePos,
                                           Vector2d<float> faceTextureSize,
                                           const Vector2d<textureMode> faceTextureMode,
                                           const std::string sideTexturePath,
                                           Vector2d<float> sideTexturePos,
                                           Vector2d<float> sideTextureSize,
                                           const Vector2d<textureMode> sideTextureMode,
                                           const normalsMode sideNormalsMode)
    : graphicalShape(graphicalShape),
      depth(depth),
      z(z),
      faceTexturePath(faceTexturePath),
      faceTexturePos(faceTexturePos),
      faceTextureSize(faceTextureSize),
      faceTextureMode(faceTextureMode),
      sideTexturePath(sideTexturePath),
      sideTexturePos(sideTexturePos),
      sideTextureSize(sideTextureSize),
      sideTextureMode(sideTextureMode),
      sideNormalsMode(sideNormalsMode)
{
}

GraphicalObject2dRaw::GraphicalObject2dRaw(const GraphicalObject2d &other)
    : GraphicalObject2dRaw(other._raw) {}

GraphicalObject2d::GraphicalObject2d(const GraphicalObject2dRaw &raw)
    : _raw(raw)
{
    DEBUG("Setup graphical object 2d");
    _faceArray = std::make_unique<VertexArrayFace2d>(_raw.faceTextureSize,
                                                     _raw.z,
                                                     _raw.faceTexturePath,
                                                     _raw.faceTexturePos,
                                                     _raw.faceTextureSize,
                                                     _raw.faceTextureMode);
    _sideArray = std::make_unique<VertexArraySide2d>(_raw.sideTexturePath,
                                                     _raw.z,
                                                     _raw.depth,
                                                     _raw.sideTexturePath,
                                                     _raw.sideTexturePos,
                                                     _raw.sideTextureSize,
                                                     _raw.sideTextureMode,
                                                     _raw.sideNormalsMode);
    DEBUG("Setup graphical object 2d done!");
}

void GraphicalObject2d::drawSelf()
{
    _sideArray->execute();
    _faceArray->execute();
    exception::OpenGLException::handle();
}
} // namespace ample::graphics
