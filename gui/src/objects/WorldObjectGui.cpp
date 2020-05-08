#include <imgui.h>

#include "ample/VectorRectangle.h"

#include "objects/WorldObjectGui.h"

namespace ample::gui
{
std::unordered_map<std::string, physics::BodyType> bodyTypeByName{
    {"static", physics::BodyType::STATIC_BODY},
    {"dynamic", physics::BodyType::DYNAMIC_BODY},
    {"kinematic", physics::BodyType::KINEMATIC_BODY},
};

std::unordered_map<std::string, graphics::normalsMode> normalsModeByName{
    {"face", graphics::normalsMode::FACE},
    {"vertex", graphics::normalsMode::VERTEX},
};

WorldObjectGui::WorldObjectGui(std::shared_ptr<filing::NamedObject> object,
                               std::shared_ptr<game::game2d::Game2dEditor> editor,
                               ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage),
      _object(std::dynamic_pointer_cast<physics::WorldObject2d>(object))
{
}

WorldObjectGui::WorldObjectGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                               ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

void WorldObjectGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::NamedObjectSelector("Level", selectedLevel, _game2dEditor->getLevelsList());
    if (selectedLevel)
    {
        gui_utils::NamedObjectSelector("Slice", selectedScene, selectedLevel->layers());
    }
    gui_utils::StringSelector("Body type", bodyType, {"static", "kinematic", "dynamic"});
    gui_utils::InputCoordinates("Size", size.x, size.y, 10.0f);
    gui_utils::InputScalar("Relative thickness", relativeThickness, 0.1f);
    faceTextureRep.x = size.x / 10.0f;
    faceTextureRep.y = size.y / 10.0f;
    sideTextureRep.x = 1.0f;
    sideTextureRep.y = (size.x + size.y) * 0.2f;
    // gui_utils::InputCoordinates("Face texture repeats", faceTextureRep.x, faceTextureRep.y, 1.0f);
    // gui_utils::InputCoordinates("Side texture repeats", sideTextureRep.x, sideTextureRep.y, 1.0f);
    gui_utils::StringSelector("Normals mode", normalsMode, {"face", "vertex"});
    gui_utils::InputCoordinates("Position", position.x, position.y, 10.0f);
    gui_utils::InputScalar("Angle", angle, 1.0f);
    gui_utils::InputCoordinates("Linear velocity", linearVelocity.x, linearVelocity.y, 1.0f);
    gui_utils::InputScalar("Angular velocity", angularVelocity, 1.0f);
    gui_utils::InputScalar("Linear damping", linearDamping, 1.0f);
    gui_utils::InputScalar("Angular damping", angularDamping, 1.0f);
    ImGui::Checkbox("Allow sleep", &allowSleep);
    ImGui::Checkbox("Awake", &awake);
    ImGui::Checkbox("Fixed rotation", &fixedRotation);
    ImGui::Checkbox("Bullet", &bullet);
    ImGui::Checkbox("Enabled", &enabled);
    gui_utils::InputScalar("Gravity scale", gravityScale, 0.1f);
    gui_utils::InputCoordinates("Center shift", center.x, center.y, 0.1f, -1.0f, 1.0f);
    gui_utils::InputScalar("Mass", mass, 1.0f);
    gui_utils::InputScalar("Inertia", inertia, 1.0f);
}

void WorldObjectGui::onSubmitCreate()
{
    if (!selectedLevel)
    {
        throw game::GameException("Level is not selected");
    }
    if (!selectedScene)
    {
        throw game::GameException("Slice is not selected");
    }
    graphics::normalsMode normMode = normalsModeByName[normalsMode];
    physics::BodyType bodyTypeEnum = bodyTypeByName[bodyType];

    _object = std::make_shared<physics::WorldObject2d>(
        nameBuffer,
        *selectedScene,
        bodyTypeEnum,
        geometry::VectorRectangle<float>(size),
        relativeThickness,
        faceTextureRep,
        sideTextureRep,
        normMode,
        position,
        angle,
        linearVelocity,
        angularVelocity,
        linearDamping,
        angularDamping,
        allowSleep,
        awake,
        fixedRotation,
        bullet,
        enabled,
        gravityScale,
        center,
        mass,
        inertia);

    selectedScene->addWorldObject(_object);
}

void WorldObjectGui::onEdit()
{
    gui_utils::InputScalar("Angular damping", angularDamping, 1.0f);
    gui_utils::InputScalar("Angular velocity", angularVelocity, 1.0f);
    ImGui::Checkbox("Awake", &awake);
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::Checkbox("Fixed rotation", &fixedRotation);
    gui_utils::InputScalar("Gravity scale", gravityScale, 0.1f);
    gui_utils::InputScalar("Linear damping", linearDamping, 1.0f);
    gui_utils::InputCoordinates("Linear velocity", linearVelocity.x, linearVelocity.y, 1.0f);
    ImGui::Checkbox("Allow sleep", &allowSleep);
}

void WorldObjectGui::onSubmitEdit()
{
    _object->setAngularDamping(angularDamping);
    _object->setAngularVelocity(angularVelocity);
    _object->setAwake(awake);
    _object->setEnabled(enabled);
    _object->setFixedRotation(fixedRotation);
    _object->setGravityScale(gravityScale);
    _object->setLinearDamping(linearDamping);
    _object->setLinearVelocity(linearVelocity);
    _object->setSleepingAllowed(allowSleep);
}

void WorldObjectGui::onView()
{
}

void WorldObjectGui::onInspect()
{
}

void WorldObjectGui::onPreview()
{
    ImGui::Text("Name: %s", _object->name().c_str());
    ImGui::Text("Body type: %s", bodyType.c_str());
}

std::string WorldObjectGui::name() const
{
    ASSERT(_object);
    return _object->name();
}

std::string WorldObjectGui::className() const
{
    return "WorldObject2d";
}
} // namespace ample::gui
