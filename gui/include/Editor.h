#pragma once

#include <string>
#include <vector>
#include <memory>

#include "ample/Singleton.h"
#include "ample/Vector2d.h"
#include "ample/WorldLayer2d.h"
#include "ample/VectorRectangle.h"

#include "InterfaceUnit.h"

namespace ample::gui
{
class Editor : public InterfaceUnit, public utils::Singleton<Editor>
{
public:
    void drawInterface() override;

    struct RawWO2d
    {
        const char *bodyTypes[3] = {"dynamic", "kinematic", "static"};
        int currentBodyType = 0;
        graphics::Vector2d<size_t> size = {1, 1};
        size_t sizeStep = 1;
        float relativeThickness = 0.5f;
        float relativeThicknessStep = 0.1f;
        graphics::Vector2d<float> textureRepeatsFront = {1.0f, 1.0f};
        graphics::Vector2d<float> textureRepeatsSide = {1.0f, 1.0f};
        float textureRepeatsStep = 1.0f;
        const char *normalsMode[2] = {"face", "vertex"};
        int currentNormalMode = 0;
        graphics::Vector2d<float> position = {0.0f, 0.0f};
        float positionStep = 10.0f;
        float positionStepFast = 10.0f;
        float angle = 0.0f;
        float angleStep = 1.0f;
    };

    void setCurrentLayer(std::shared_ptr<ample::physics::WorldLayer2d> layer);

private:
    RawWO2d worldObject2d;
    std::shared_ptr<ample::physics::WorldLayer2d> currentLayer;
    std::vector<std::shared_ptr<ample::physics::WorldObject2d>> objects;
    const float cellSize = 10.0f;
};
} // namespace ample::gui
