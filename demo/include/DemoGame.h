#pragma once

#include <memory>

#include "Game2d.h"
#include "KeyboardControlCamera.h"
#include "Texture.h"
#include "StateMachine.h"
#include "ControlledObject.h"
#include "Debug.h"
#include "WorldRevoluteJoint2d.h"
#include "WorldDistanceJoint.h"
#include "RegularPolygon.h"

class Braid : public ample::graphics::GraphicalObject2d
{
public:
    Braid()
        : GraphicalObject2d("Braid",
                            ample::geometry::RegularPolygon<float>(10.0f, 6),
                            10.0f,
                            0.0f,
                            {1.0f, 1.0f},
                            {1.0f, 1.0f},
                            ample::graphics::normalsMode::FACE,
                            {0.0f, 0.0f},
                            0.0f)
    {
        auto texture = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw("../../demo/textures/braid.jpg",
                                                                                              "Braid textre",
                                                                                              {820UL / 7 - 1, 546UL / 4 - 1},
                                                                                              {2L, 2L},
                                                                                              {7, 4},
                                                                                              ample::graphics::channelMode::RGBA,
                                                                                              ample::graphics::texturePlayback::NORMAL,
                                                                                              27,
                                                                                              {
                                                                                                  ample::graphics::textureOrigin::REVERSED,
                                                                                                  ample::graphics::textureOrigin::REVERSED,
                                                                                              }));
        bindTexture(texture);
        face().bindTexture(texture);
        side().bindTexture(texture);
    }
};

class BraidIdle : public ample::game::ControlledObject::ObjectState<Braid>
{
public:
    BraidIdle(const std::string &name, std::shared_ptr<Braid> braid)
        : ObjectState(name, braid) {}

    void onActive() override
    {
        ObjectState::onActive();
    }
};

class BraidRun : public ample::game::ControlledObject::ObjectState<Braid>
{
public:
    BraidRun(const std::string &name, std::shared_ptr<Braid> braid)
        : ObjectState(name, braid) {}

    void onActive() override
    {
        ObjectState::onActive();
        object()->texture()->nextFrame();
    }
};

struct Rope
{
    Rope(std::shared_ptr<ample::physics::WorldLayer2d> layer,
         std::string name,
         float len,
         float width,
         size_t countNodes,
         ample::graphics::Vector2d<float> pos,
         float relativeThickness,
         float massNode,
         const ample::graphics::Vector2d<float> &limitAngle = {-45, 45},
         float dampingRatio = 0.2) : length(len)
    {
        float nodeLen = len / countNodes;
        std::vector<ample::graphics::Vector2d<float>> shape = {{width / 2, nodeLen / 2},
                                                               {width / 2, -nodeLen / 2},
                                                               {-width / 2, -nodeLen / 2},
                                                               {-width / 2, nodeLen / 2}};
        {
            nodes.emplace_back(new ample::physics::WorldObject2d(name + "_m%a%i%n%",
                                                                 *layer,
                                                                 ample::physics::BodyType::STATIC_BODY,
                                                                 ample::geometry::RegularPolygon<float>(width / 2, 30),
                                                                 relativeThickness,
                                                                 {1.0f, 1.0f},
                                                                 {1.0f, 1.0f},
                                                                 ample::graphics::normalsMode::FACE,
                                                                 pos));
            layer->addWorldObject(nodes[0]);
            auto fixture = nodes[0]->addFixture(shape);
            fixture.setDensity(1.0f);
            fixture.setFriction(1.0f);
            ample::physics::MassData d = nodes[0]->getMassData();
            d.I = 1;
            d.mass = massNode;
            nodes[0]->setMassData(d);
        }
        pos.y -= nodeLen / 2;
        for (size_t i = 1; i <= countNodes; i++)
        {
            nodes.emplace_back(new ample::physics::WorldObject2d(name + "_%" + std::to_string(i),
                                                                 *layer,
                                                                 ample::physics::BodyType::DYNAMIC_BODY,
                                                                 shape,
                                                                 relativeThickness,
                                                                 {1.0f, 1.0f},
                                                                 {1.0f, 1.0f},
                                                                 ample::graphics::normalsMode::FACE,
                                                                 pos));
            layer->addWorldObject(nodes[i]);
            ample::physics::MassData d = nodes[i]->getMassData();
            d.I = 1;
            d.mass = massNode;
            nodes[i]->setMassData(d);
            auto fixture = nodes[i]->addFixture(shape);
            fixture.setDensity(1.0f);
            fixture.setFriction(1.0f);
            pos.y -= nodeLen;
            revoluteJoints.emplace_back(new ample::physics::WorldRevoluteJoint2d(*nodes[i - 1],
                                                                                 *nodes[i],
                                                                                 nodes[i]->getWorldPoint({0, nodeLen / 2 - 1})));
            distanceJoints.emplace_back(new ample::physics::WorldDistanceJoint2d(*nodes[i - 1],
                                                                                 *nodes[i],
                                                                                 nodes[i - 1]->getWorldCenter(),
                                                                                 nodes[i]->getWorldCenter()));
            distanceJoints.back()->setDampingRatio(dampingRatio);
            revoluteJoints.back()->setLimits(limitAngle.x * M_PI / 180, limitAngle.y * M_PI / 180);
            revoluteJoints.back()->enableLimit(true);
        }
    }
    std::vector<std::shared_ptr<ample::physics::WorldObject2d>> nodes;
    std::vector<std::shared_ptr<ample::physics::WorldRevoluteJoint2d>> revoluteJoints;
    std::vector<std::shared_ptr<ample::physics::WorldDistanceJoint2d>> distanceJoints;
    const float length;
};

class DemoGame : public ample::game::game2d::Game2d
{
public:
    DemoGame(ample::window::Window &window);
    void onActive() override;

private:
    //std::shared_ptr<Braid> braid;
    std::shared_ptr<ample::physics::WorldObject2d> box;
    std::shared_ptr<ample::physics::WorldObject2d> ground;
    std::shared_ptr<ample::physics::WorldObject2d> fixed;
    std::shared_ptr<Rope> ropeToHeavyBall;
    std::shared_ptr<ample::physics::WorldObject2d> heavyBall;
    std::shared_ptr<KeyboardControlCamera> cameraRemote;
    std::shared_ptr<Rope> rope;
    std::shared_ptr<ample::physics::WorldObject2d> ball;
    std::shared_ptr<ample::graphics::Texture> braid = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw{"../../demo/textures/braid.jpg",
                                                                                                                             "braid",
                                                                                                                             {820 / 7 - 1, 546 / 4 - 1},
                                                                                                                             {0, 0},
                                                                                                                             {7, 4},
                                                                                                                             ample::graphics::channelMode::RGBA,
                                                                                                                             ample::graphics::texturePlayback::NORMAL,
                                                                                                                             27});
    std::shared_ptr<ample::graphics::Texture> grass = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw{"../../demo/textures/grass.jpg",
                                                                                                                             "braid",
                                                                                                                             {626, 626},
                                                                                                                             {0, 0},
                                                                                                                             {1, 1},
                                                                                                                             ample::graphics::channelMode::RGBA,
                                                                                                                             ample::graphics::texturePlayback::NORMAL});
    std::shared_ptr<ample::graphics::Texture> dirt = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw{"../../demo/textures/dirt.png",
                                                                                                                             "braid",
                                                                                                                             {200, 200},
                                                                                                                             {0, 0},
                                                                                                                             {1, 1},
                                                                                                                             ample::graphics::channelMode::RGB,
                                                                                                                             ample::graphics::texturePlayback::NORMAL});
    std::shared_ptr<ample::graphics::Texture> lena = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw{"../../demo/textures/lena512.png",
                                                                                                                             "braid",
                                                                                                                             {512, 512},
                                                                                                                             {0, 0},
                                                                                                                             {1, 1},
                                                                                                                             ample::graphics::channelMode::RGB,
                                                                                                                             ample::graphics::texturePlayback::NORMAL});
    std::shared_ptr<ample::graphics::Texture> ropeTexture = std::make_shared<ample::graphics::Texture>(ample::graphics::TextureRaw{"../../demo/textures/rope.jpg",
                                                                                                                             "braid",
                                                                                                                             {900, 900},
                                                                                                                             {0, 0},
                                                                                                                             {1, 1},
                                                                                                                             ample::graphics::channelMode::RGB,
                                                                                                                             ample::graphics::texturePlayback::NORMAL});
};
