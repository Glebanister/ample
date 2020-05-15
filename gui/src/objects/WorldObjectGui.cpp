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
    angularDamping = _object->getAngularDamping();
    awake = _object->isAwake();
    enabled = _object->isEnabled();
    fixedRotation = _object->isFixedRotation();
    gravityScale = _object->getGravityScale();
    linearDamping = _object->getLinearDamping();
    linearVelocity = _object->getLinearVelocity();
    allowSleep = _object->isSleepingAllowed();
    angle = _object->getStartAngle();
    position = _object->getStartPosition();
    _faceTexture = _object->face().texture();
    _sideTexture = _object->side().texture();
}

WorldObjectGui::WorldObjectGui(std::shared_ptr<game::game2d::Game2dEditor> editor,
                               ObjectStorageGui *storage)
    : _game2dEditor(editor),
      _objectStorageGui(storage)
{
}

void setTextureModeFace(const std::string mode, graphics::Vector2d<float> &textureRep, const graphics::Vector2d<float> size, float blockSize)
{
    if (mode == "fit")
    {
        textureRep.x = 1.0f;
        textureRep.y = 1.0f;
    }
    else if (mode == "tile")
    {
        textureRep.x = size.x / blockSize;
        textureRep.y = size.y / blockSize;
    }
}

void setTextureModeSide(const std::string mode, graphics::Vector2d<float> &textureRep, const graphics::Vector2d<float> size, float blockSize)
{
    if (mode == "fit")
    {
        textureRep.x = 1.0f;
        textureRep.y = 1.0f;
    }
    else if (mode == "tile")
    {
        textureRep.y = 1.0f;
        textureRep.x = (size.x + size.y) * 2.0f / blockSize;
    }
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
    gui_utils::StringSelector("Normals mode", normalsMode, {"face", "vertex"});
    gui_utils::StringSelector("Texture mode face", textureSizeFace, {"fit", "tile"});
    gui_utils::StringSelector("Texture mode side", textureSizeSide, {"fit", "tile"});
    setTextureModeFace(textureSizeFace, faceTextureRep, size, 10.0f);
    setTextureModeFace(textureSizeSide, sideTextureRep, size, 10.0f);
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
    gui_utils::NamedObjectSelector("Face texture", _faceTexture, _objectStorageGui->texturesList());
    gui_utils::NamedObjectSelector("Side texture", _sideTexture, _objectStorageGui->texturesList());
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

    _object->face().bindTexture(_faceTexture);
    _object->side().bindTexture(_sideTexture);

    selectedScene->addWorldObject(_object);
}

void WorldObjectGui::onEdit()
{
    gui_utils::InputCoordinates("Position", position.x, position.y, 10.0f);
    gui_utils::InputScalar("Angle", angle, 1.0f);
    gui_utils::InputScalar("Angular damping", angularDamping, 1.0f);
    gui_utils::InputScalar("Angular velocity", angularVelocity, 1.0f);
    ImGui::Checkbox("Awake", &awake);
    ImGui::Checkbox("Enabled", &enabled);
    ImGui::Checkbox("Fixed rotation", &fixedRotation);
    gui_utils::InputScalar("Gravity scale", gravityScale, 0.1f);
    gui_utils::InputScalar("Linear damping", linearDamping, 1.0f);
    gui_utils::InputCoordinates("Linear velocity", linearVelocity.x, linearVelocity.y, 1.0f);
    ImGui::Checkbox("Allow sleep", &allowSleep);
    gui_utils::NamedObjectSelector("Face texture", _faceTexture, _objectStorageGui->texturesList());
    gui_utils::NamedObjectSelector("Side texture", _sideTexture, _objectStorageGui->texturesList());
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
    _object->setStartAngle(angle);
    _object->setStartPosition(position);
    gui_utils::NamedObjectSelector("Face texture", _faceTexture, _objectStorageGui->texturesList());
    gui_utils::NamedObjectSelector("Side texture", _sideTexture, _objectStorageGui->texturesList());
    _object->face().bindTexture(_faceTexture);
    _object->side().bindTexture(_sideTexture);
}

void WorldObjectGui::onView()
{
    ASSERT(_object);
    ImGui::BeginChild("World object view");
    _observer.setViewport({ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - 24},
                          {ImGui::GetWindowPos().x, 7});
    _observer.look(_object);
    _observer.updatePos();
    ImGui::EndChild();
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
