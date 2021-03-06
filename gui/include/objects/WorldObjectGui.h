#pragma once

#include <memory>
#include <unordered_map>

#include "ample/WorldObject2d.h"

#include "ObjectStorageGui.h"
#include "objects/ObjectGui.h"
#include "Observer.h"

namespace ample::gui
{
class Observer;
class ObjectStorageGui;
class ObjectGui;
class WorldObjectGui : public ObjectGui
{
public:
    WorldObjectGui(std::shared_ptr<filing::NamedObject>, std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);
    WorldObjectGui(std::shared_ptr<game::game2d::Game2dEditor>, ObjectStorageGui *);

    void onCreate() override;
    void onSubmitCreate() override;
    void onEdit() override;
    void onSubmitEdit() override;
    void onView() override;
    void onInspect() override;
    void onPreview() override;

    std::string name() const override;
    std::string className() const override;

    void setLevel(std::shared_ptr<game::game2d::Level> level);

private:
    std::shared_ptr<game::game2d::Game2dEditor> _game2dEditor;
    ObjectStorageGui *_objectStorageGui;
    Observer _observer;

    std::shared_ptr<physics::WorldObject2d> _object;

    char nameBuffer[255] = {0};
    std::shared_ptr<game::game2d::Level> selectedLevel = nullptr;
    std::shared_ptr<filing::Scene2d> selectedScene = nullptr;
    std::string bodyType = "static";

    std::string formType = "rectangle";
    graphics::Vector2d<float> size = {10.0f, 10.0f};
    float radius = 5.0f;
    uint32_t nVert = 6;

    float relativeThickness = 0.3f;
    graphics::Vector2d<float> faceTextureRep = {1.0f, 1.0f};
    graphics::Vector2d<float> sideTextureRep = {1.0f, 1.0f};
    std::string textureSizeFace = "fit";
    std::string textureSizeSide = "fit";
    std::string normalsMode = "face";
    graphics::Vector2d<float> position = {0.0f, 0.0f};
    float angle = 0.0f;
    graphics::Vector2d<float> linearVelocity = {0.0f, 0.0f};
    float angularVelocity = 0.0f;
    float linearDamping = 0.0f;
    float angularDamping = 0.0f;
    bool allowSleep = true;
    bool awake = true;
    bool fixedRotation = false;
    bool bullet = false;
    bool enabled = true;
    float gravityScale = 1.0f;
    graphics::Vector2d<float> center = {0.0f, 0.0f};
    float mass = 0.0f;
    float inertia = 1.0f;
    std::shared_ptr<graphics::Texture> _faceTexture = nullptr;
    std::shared_ptr<graphics::Texture> _sideTexture = nullptr;
    std::string faceTextureSizeInput = "auto";
};
} // namespace ample::gui
