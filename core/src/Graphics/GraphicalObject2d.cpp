#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float thickness,
                                     const float z,
                                     const Vector2d<float> &faceTextureRepeats,
                                     const Vector2d<float> &sideTextureRepeats,
                                     const normalsMode sideNormalsMode,
                                     const glm::mat4 &translated,
                                     const glm::mat4 &scaled,
                                     const glm::mat4 &rotated)
    : GraphicalObject(translated, scaled, rotated),
      _face(graphicalShape, z, faceTextureRepeats),
      _side(graphicalShape, z, thickness, sideTextureRepeats, sideNormalsMode)
{
    addSubObject(_face);
    addSubObject(_side);
}

GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float thickness,
                                     const float z,
                                     const Vector2d<float> &faceTextureRepeats,
                                     const Vector2d<float> &sideTextureRepeats,
                                     const normalsMode sideNormalsMode,
                                     const Vector2d<float> &translated,
                                     const float &rotated)
    : GraphicalObject2d(graphicalShape,
                        thickness,
                        z,
                        faceTextureRepeats,
                        sideTextureRepeats,
                        sideNormalsMode,
                        glm::translate(glm::vec3{translated.x, translated.y, z}),
                        glm::scale(glm::vec3{1.0f}),
                        glm::rotate(rotated, glm::vec3{0.0f, 0.0f, 1.0f}))
{
}

GraphicalEdge &GraphicalObject2d::side() noexcept
{
    return _side;
}

GraphicalPolygon &GraphicalObject2d::face() noexcept
{
    return _face;
}

GraphicalObject2d::GraphicalObject2d(filing::JsonIO &input)
    : GraphicalObject(input),
      _face(input),
      _side(input)
{
}

void GraphicalObject2d::dump(filing::JsonIO &output)
{
    GraphicalObject::dump(output);
    _face.dump(output);
    _side.dump(output)
}

} // namespace ample::graphics
