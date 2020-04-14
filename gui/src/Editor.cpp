#include <algorithm>

#include "ample/Utils.h"
#include "ample/WorldObject2d.h"
#include "ample/RegularPolygon.h"
#include "ample/VectorRectangle.h"

#include "Editor.h"

namespace ample::gui
{
void Editor::drawInterface()
{
    ImGui::Begin("Editor");
    ImGui::InputText("Name", worldObject2d.nameBuffer, 255);
    ImGui::Combo("Body type", &worldObject2d.currentBodyType, worldObject2d.bodyTypes, IM_ARRAYSIZE(worldObject2d.bodyTypes));
    ImGui::InputScalar("Width", ImGuiDataType_U32, &worldObject2d.size.x, &worldObject2d.sizeStep);
    ImGui::InputScalar("Height", ImGuiDataType_U32, &worldObject2d.size.y, &worldObject2d.sizeStep);
    utils::limit(worldObject2d.relativeThickness, 0.0f, 1.0f);
    ImGui::InputScalar("Relative thickness", ImGuiDataType_Float, &worldObject2d.relativeThickness, &worldObject2d.relativeThicknessStep);
    utils::limit(worldObject2d.textureRepeatsFront.x, 0.0f, 100.0f);
    utils::limit(worldObject2d.textureRepeatsFront.y, 0.0f, 100.0f);
    utils::limit(worldObject2d.textureRepeatsSide.x, 0.0f, 100.0f);
    utils::limit(worldObject2d.textureRepeatsSide.y, 0.0f, 100.0f);
    ImGui::InputScalar("Texture repeats front x", ImGuiDataType_Float, &worldObject2d.textureRepeatsFront.x, &worldObject2d.textureRepeatsStep);
    ImGui::InputScalar("Texture repeats front y", ImGuiDataType_Float, &worldObject2d.textureRepeatsFront.y, &worldObject2d.textureRepeatsStep);
    ImGui::InputScalar("Texture repeats side x", ImGuiDataType_Float, &worldObject2d.textureRepeatsSide.x, &worldObject2d.textureRepeatsStep);
    ImGui::InputScalar("Texture repeats side y", ImGuiDataType_Float, &worldObject2d.textureRepeatsSide.y, &worldObject2d.textureRepeatsStep);
    ImGui::Combo("Side normals mode", &worldObject2d.currentNormalMode, worldObject2d.normalsMode, IM_ARRAYSIZE(worldObject2d.normalsMode));
    ImGui::InputScalar("X", ImGuiDataType_Float, &worldObject2d.position.x, &worldObject2d.positionStep, &worldObject2d.positionStepFast);
    ImGui::InputScalar("Y", ImGuiDataType_Float, &worldObject2d.position.y, &worldObject2d.positionStep, &worldObject2d.positionStepFast);
    utils::limit(worldObject2d.angle, -180.0f, 180.0f);
    ImGui::InputScalar("Angle", ImGuiDataType_Float, &worldObject2d.angle, &worldObject2d.angleStep);
    if (ImGui::Button("Create"))
    {
        if (currentLayer)
        {
            physics::BodyType bodyType = physics::BodyType::DYNAMIC_BODY;
            if (worldObject2d.currentBodyType == 1)
            {
                bodyType = physics::BodyType::KINEMATIC_BODY;
            }
            if (worldObject2d.currentBodyType == 2)
            {
                bodyType = physics::BodyType::STATIC_BODY;
            }
            std::string name(worldObject2d.nameBuffer);
            graphics::normalsMode normalsMode = worldObject2d.currentNormalMode == 0 ? graphics::normalsMode::FACE : graphics::normalsMode::VERTEX;
            currentLayer->addWorldObject(std::make_shared<physics::WorldObject2d>(
                name,
                currentLayer,
                bodyType,
                geometry::VectorRectangle<float>({worldObject2d.size.x * cellSize, worldObject2d.size.y * cellSize}),
                worldObject2d.relativeThickness,
                worldObject2d.textureRepeatsFront,
                worldObject2d.textureRepeatsSide,
                normalsMode,
                worldObject2d.position,
                worldObject2d.angle));
        }
    }
    ImGui::End();
}

void Editor::setCurrentLayer(std::shared_ptr<ample::physics::WorldLayer2d> layer)
{
    currentLayer = layer;
}
} // namespace ample::gui
