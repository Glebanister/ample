#define GLM_ENABLE_EXPERIMENTAL
#define GL_GLEXT_PROTOTYPES 1

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>

#include "GraphicalObject2d.h"
#include "Vector2d.h"
#include "Debug.h"
#include "Exception.h"
#include "ShaderProcessor.h"

namespace ample::graphics
{
static std::vector<Vector3d<float>> generateFaceNormals(const std::vector<Vector3d<float>> &vert)
{
    return {vert.size(), {0, 0, -1}};
}

static std::vector<Vector3d<float>> generateSideNormals(const std::vector<Vector3d<float>> &vert)
{
    std::vector<glm::vec3> triangleNormals(vert.size());
    for (size_t vId = 0; vId < vert.size(); ++vId)
    {
        glm::vec3 first{vert[vId].x, vert[vId].y, vert[vId].z};
        glm::vec3 second{vert[(vId + 1) % vert.size()].x, vert[(vId + 1) % vert.size()].y, vert[(vId + 1) % vert.size()].z};
        glm::vec3 third{vert[(vId + 2) % vert.size()].x, vert[(vId + 2) % vert.size()].y, vert[(vId + 2) % vert.size()].z};
        triangleNormals[vId] = glm::triangleNormal(std::move(first), std::move(second), std::move(third));
    }
    std::vector<Vector3d<float>> normals(vert.size());
    for (size_t vId = 0; vId < vert.size(); ++vId)
    {
        size_t adj[] = {(vId - 2 + vert.size()) % vert.size(),
                        (vId - 1 + vert.size()) % vert.size(),
                        vId};
        glm::vec3 normal = (triangleNormals[adj[0]] + triangleNormals[adj[1]] + triangleNormals[adj[2]]) * (1.0f / 3.0f);
        normals[vId] = {normal[0], normal[1], normal[2]};
    }
    return normals;
}

GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float depth,
                                     const float z)
    : _programId(shaders::ShaderProcessor::instance().getProgramId()),
      _modelMatrixId(glGetUniformLocation(_programId, "model_matrix")),
      _depth(depth),
      _z(z)
{
    DEBUG("Setup graphical object 2d");
    exception::OpenGLException::handle();
    std::vector<Vector3d<float>> sideArray(graphicalShape.size() * 2 + 2);
    std::vector<Vector3d<float>> faceArray(graphicalShape.size());
    for (size_t vId = 0; vId < graphicalShape.size(); ++vId)
    {
        sideArray[vId * 2] = {graphicalShape[vId].x,
                              graphicalShape[vId].y,
                              depth + z};
        sideArray[vId * 2 + 1] = {graphicalShape[vId].x,
                                  graphicalShape[vId].y,
                                  z};
        faceArray[vId] = {graphicalShape[vId].x,
                          graphicalShape[vId].y,
                          z};
    }
    sideArray[sideArray.size() - 2] = sideArray[0];
    sideArray[sideArray.size() - 1] = sideArray[1];
    _sideArray = std::make_unique<VertexArray>(sideArray, generateSideNormals(sideArray), GL_TRIANGLE_STRIP);
    _faceArray = std::make_unique<VertexArray>(faceArray, generateFaceNormals(faceArray), GL_TRIANGLE_FAN);
}

void GraphicalObject2d::drawSelf(const glm::mat4 &)
{
    _sideArray->execute();
    _faceArray->execute();
    exception::OpenGLException::handle();
}

void GraphicalObject2d::setFaceColor256(Color color)
{
    _faceArray->setColor256(color.r, color.g, color.b);
}

void GraphicalObject2d::setSideColor256(Color color)
{
    _sideArray->setColor256(color.r, color.g, color.b);
}
} // namespace ample::graphics
