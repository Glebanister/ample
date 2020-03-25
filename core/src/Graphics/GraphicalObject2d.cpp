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
                                           Vector2d<int> faceTextureSize,
                                           Vector2d<int> faceTexturePos,
                                           const Vector2d<textureMode> faceTextureMode,
                                           const std::string sideTexturePath,
                                           Vector2d<int> sideTextureSize,
                                           Vector2d<int> sideTexturePos,
                                           const Vector2d<textureMode> sideTextureMode,
                                           const normalsMode sideNormalsMode)
    : graphicalShape(graphicalShape),
      depth(depth),
      z(z),
      faceTexturePath(faceTexturePath),
      faceTextureSize(faceTextureSize),
      faceTexturePos(faceTexturePos),
      faceTextureMode(faceTextureMode),
      sideTexturePath(sideTexturePath),
      sideTextureSize(sideTextureSize),
      sideTexturePos(sideTexturePos),
      sideTextureMode(sideTextureMode),
      sideNormalsMode(sideNormalsMode)
{
}

GraphicalObject2dRaw::GraphicalObject2dRaw(const GraphicalObject2d &other)
    : GraphicalObject2dRaw(other._raw) {}

GraphicalObject2d::GraphicalObject2d(const GraphicalObject2dRaw &raw)
    : _raw(raw)
{
    DEBUG("Setup graphical object 2d") << _raw.faceTextureSize.x << ' ' << _raw.faceTextureSize.y << std::endl;
    _faceArray = std::make_unique<VertexArrayFace2d>(_raw.graphicalShape,
                                                     _raw.z,
                                                     _raw.faceTexturePath,
                                                     _raw.faceTextureSize,
                                                     _raw.faceTexturePos,
                                                     _raw.faceTextureMode);
    _sideArray = std::make_unique<VertexArraySide2d>(_raw.graphicalShape,
                                                     _raw.z,
                                                     _raw.depth,
                                                     _raw.sideTexturePath,
                                                     _raw.sideTextureSize,
                                                     _raw.sideTexturePos,
                                                     _raw.sideTextureMode,
                                                     _raw.sideNormalsMode);
    DEBUG("Setup graphical object 2d done!");
}

GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float depth,
                                     const float z)
    : GraphicalObject2d({
          graphicalShape,
          depth,
          z,
          "../../demo/textures/lena512.png",
          {0, 0},
          {512, 512},
          {textureMode::STRETCH, textureMode::STRETCH},
          "../../demo/textures/lena512.png",
          {0, 0},
          {512, 512},
          {textureMode::STRETCH, textureMode::STRETCH},
          normalsMode::FACE,
      })
{
    DEBUG("Bad GraphicalObject2d constructor usage!");
    // TODO: remove this constructor
}

void GraphicalObject2d::drawSelf()
{
    _sideArray->execute();
    _faceArray->execute();
    exception::OpenGLException::handle();
}
} // namespace ample::graphics
