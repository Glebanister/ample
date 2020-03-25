#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>

#include "Vector3d.h"
#include "Vector2d.h"
#include "VertexArraySide2d.h"
#include "Debug.h"
#include "VertexArray.h"

namespace ample::graphics
{
static std::vector<Vector3d<float>> generateSideCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                       const float z,
                                                       const float depth)
{
    std::vector<Vector3d<float>> sideArray;
    size_t verts = graphicalShape.size();
    for (size_t vId = 0; vId < verts; ++vId)
    {
        int nvt = (vId + 1) % verts;
        sideArray.emplace_back(graphicalShape[vId].x, graphicalShape[vId].y, z);
        sideArray.emplace_back(graphicalShape[vId].x, graphicalShape[vId].y, depth + z);
        sideArray.emplace_back(graphicalShape[nvt].x, graphicalShape[nvt].y, depth + z);

        sideArray.emplace_back(graphicalShape[vId].x, graphicalShape[vId].y, z);
        sideArray.emplace_back(graphicalShape[nvt].x, graphicalShape[nvt].y, depth + z);
        sideArray.emplace_back(graphicalShape[nvt].x, graphicalShape[nvt].y, z);
    }
    return sideArray;
}

static std::vector<Vector3d<float>> generateSideNormals(const std::vector<Vector2d<float>> &graphicalShape,
                                                        normalsMode mode,
                                                        const float z,
                                                        const float depth)
{
    auto vert = generateSideCoords(graphicalShape, z, depth);
    ASSERT(vert.size() % 3 == 0);
    size_t verts = vert.size();
    std::vector<Vector3d<float>> normals;
    std::vector<glm::vec3> triangleNormals;
    std::vector<int> normId;
    for (size_t i = 0; i < verts; i += 3)
    {
        glm::vec3 first{vert[i + 0].x, vert[i + 0].y, vert[i + 0].z};
        glm::vec3 secon{vert[i + 1].x, vert[i + 1].y, vert[i + 1].z};
        glm::vec3 third{vert[i + 2].x, vert[i + 2].y, vert[i + 2].z};
        auto norm = glm::triangleNormal(std::move(first),
                                        std::move(secon),
                                        std::move(third));
        triangleNormals.emplace_back(norm);
        triangleNormals.emplace_back(norm);
        triangleNormals.emplace_back(norm);
        for (int i = 0; i < 3; ++i)
        {
            normals.emplace_back(norm.x, norm.y, norm.z);
        }
    }
    if (mode == normalsMode::VERTEX)
    {
        auto normalsCopy{triangleNormals};
        for (size_t i = 2; i < verts; i += 6)
        {
            size_t f = (i + 2) % verts;
            size_t s = (i + 5) % verts;
            auto mid = (normalsCopy[i] + normalsCopy[f] + normalsCopy[s]) * (1.0f / 3.0f);
            normals[i] = normals[f] = normals[s] = {mid.x, mid.y, mid.z};
        }
        for (size_t i = 5; i < verts; i += 6)
        {
            size_t f = (i + 1) % verts;
            size_t s = (i + 4) % verts;
            auto mid = (normalsCopy[i] + normalsCopy[f] + normalsCopy[s]) * (1.0f / 3.0f);
            normals[i] = normals[f] = normals[s] = {mid.x, mid.y, mid.z};
        }
    }
    return normals;
}

static std::vector<Vector2d<float>> generateSideUVCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                         const float z,
                                                         const float depth,
                                                         const Vector2d<float> &size,
                                                         const Vector2d<float> &position,
                                                         const textureMode &texModeX,
                                                         const textureMode &texModeY)
{
    auto shape = generateSideCoords(graphicalShape, z, depth);
    std::vector<Vector2d<float>> uvCoords(shape.size());
    // TODO
    return uvCoords;
}

VertexArraySide2d::VertexArraySide2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float z,
                                     const float depth,
                                     const std::string &texturePath,
                                     const Vector2d<float> &textureSize,
                                     const Vector2d<float> &texturePos,
                                     const Vector2d<textureMode> &texMode,
                                     const normalsMode &normMode)
    : VertexArray(generateSideCoords(graphicalShape, z, depth),
                  generateSideUVCoords(graphicalShape, z, depth, textureSize, texturePos, texMode.x, texMode.y),
                  generateSideNormals(graphicalShape, normMode, z, depth),
                  texturePath,
                  textureSize,
                  texturePos) {}
} // namespace ample::graphics
