#include "VertexArrayFace2d.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "Debug.h"

namespace ample::graphics
{
static std::vector<Vector3d<float>> generateFaceCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                       const float z)
{
    std::vector<Vector3d<float>> faceArray;
    size_t verts = graphicalShape.size();
    for (size_t i = 1; i < verts - 1; ++i)
    {
        faceArray.emplace_back(graphicalShape[0].x, graphicalShape[0].y, z);
        faceArray.emplace_back(graphicalShape[i].x, graphicalShape[i].y, z);
        faceArray.emplace_back(graphicalShape[i + 1].x, graphicalShape[i + 1].y, z);
    }
    return faceArray;
}

static std::vector<Vector3d<float>> generateFaceNormals(const std::vector<Vector2d<float>> &graphicalShape, const float z)
{
    return {generateFaceCoords(graphicalShape, z).size(), {0, 0, -1}};
}

static std::vector<Vector2d<float>> generateFaceUVCoords(const std::vector<Vector2d<float>> &graphicalShape,
                                                         const Vector2d<float> &size,
                                                         const Vector2d<float> &position,
                                                         const textureMode &texModeX,
                                                         const textureMode &texModeY,
                                                         const float z)
{
    auto vert = generateFaceCoords(graphicalShape, z);
    std::vector<Vector2d<float>> uvCoords(vert.size());
    ASSERT(vert.size() > 0);
    Vector2d<float> leftDown{vert[0].x, vert[0].y};
    Vector2d<float> rightTop{vert[0].x, vert[0].y};
    for (size_t i = 1; i < vert.size(); ++i)
    {
        leftDown.x = std::min(leftDown.x, vert[i].x);
        leftDown.y = std::min(leftDown.y, vert[i].y);
        rightTop.x = std::max(rightTop.x, vert[i].x);
        rightTop.y = std::max(rightTop.y, vert[i].y);
    }
    switch (texModeX)
    {
    case textureMode::TILE:
        ASSERT(false);

        // TODO: implement this

        break;

    case textureMode::STRETCH:
        for (size_t i = 0; i < vert.size(); ++i)
        {
            uvCoords[i].x = ((vert[i].x - leftDown.x) / (rightTop.x - leftDown.x)) + position.x / size.x;
        }
        break;
    }
    switch (texModeY)
    {
    case textureMode::TILE:
        ASSERT(false);

        // TODO: implement this

        break;

    case textureMode::STRETCH:
        for (size_t i = 0; i < vert.size(); ++i)
        {
            uvCoords[i].y = ((vert[i].y - leftDown.y) / (rightTop.y - leftDown.y)) + position.y / size.y;
        }
        break;
    }
    return uvCoords;
}

VertexArrayFace2d::VertexArrayFace2d(const std::vector<Vector2d<float>> &graphicalShape,
                                     const float z,
                                     const std::string &texturePath,
                                     const Vector2d<float> &textureSize,
                                     const Vector2d<float> &texturePos,
                                     const Vector2d<textureMode> &texMode)
    : VertexArray(generateFaceCoords(graphicalShape, z),
                  generateFaceUVCoords(graphicalShape, textureSize, texturePos, texMode.x, texMode.y, z),
                  generateFaceNormals(graphicalShape, z),
                  texturePath,
                  textureSize,
                  texturePos)
{
    DEBUG("VertexArrayFace2d : VertexArrayFace2d") << textureSize.x << ' ' << textureSize.y << std::endl;
}
} // namespace ample::graphics
