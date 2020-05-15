#include "gtest/gtest.h"

#include "ample/Action.h"
#include "ample/DistanceTransition.h"
#include "ample/GraphicalObject2d.h"
#include "ample/GraphicalRotateAction.h"
#include "ample/GraphicalTranslateAction.h"
#include "ample/JsonIO.h"
#include "ample/PositionTransition.h"
#include "ample/RegularPolygon.h"
#include "ample/StateMachine.h"
#include "ample/TimerTransition.h"
#include "ample/WorldObject2d.h"

TEST(ObjectIO, GraphicalEdge)
{
    auto obj1 = ample::graphics::GraphicalEdge("ObjectName",
                                               ample::geometry::RegularPolygon<float>(10.0f, 4),
                                               10.0f,
                                               3.0f,
                                               {1.0f, 2.0f},
                                               ample::graphics::normalsMode::FACE);
    auto data1 = obj1.dump();
    auto obj2 = ample::graphics::GraphicalEdge(data1);
    auto data2 = obj2.dump();
    ASSERT_EQ(data1, data2);
}

TEST(ObjectIO, GraphicalPolygon)
{
    auto obj1 = ample::graphics::GraphicalPolygon("ObjectName",
                                                  ample::geometry::RegularPolygon<float>(10.0f, 4),
                                                  10.0f,
                                                  {1.0f, 2.0f});
    auto data1 = obj1.dump();
    auto obj2 = ample::graphics::GraphicalPolygon(data1);
    auto data2 = obj2.dump();
    ASSERT_EQ(data1, data2);
}

TEST(ObjectIO, GraphicalObject2d)
{
    auto obj1 = ample::graphics::GraphicalObject2d("ObjectName",
                                                   "GraphicalObject",
                                                   ample::geometry::RegularPolygon<float>(10.0f, 4),
                                                   10.0f,
                                                   3.0f,
                                                   {1.0f, 2.0f},
                                                   {3.0f, 4.0f},
                                                   ample::graphics::normalsMode::FACE,
                                                   {0.0f, 0.0f},
                                                   1.0f);
    auto data1 = obj1.dump();
    auto obj2 = ample::graphics::GraphicalObject2d(data1);
    auto data2 = obj2.dump();
    ASSERT_EQ(data1, data2);
}

TEST(StateMachineIO, Empty)
{
    auto sm = ample::game::StateMachine("Name");
    auto run = std::make_shared<ample::game::StateMachine::State>(sm, "run");
    sm.setStartState(run);
    auto smData = sm.dump();
    std::shared_ptr<ample::game::Namespace> names = std::make_shared<ample::game::Namespace>();
    auto sameStateMachine = ample::game::StateMachine(ample::filing::JsonIO{smData}, names);
    auto sameData = sameStateMachine.dump();
    ASSERT_EQ(smData, sameData);
}

TEST(StateMachineIO, WithOneTransition)
{
    auto sm = ample::game::StateMachine("Name");
    auto run = std::make_shared<ample::game::StateMachine::State>(sm, "run");
    auto idle = std::make_shared<ample::game::StateMachine::State>(sm, "idle");
    sm.setStartState(run);
    run->addTransition(std::make_shared<ample::game::TimerTransition>(
        "transition",
        idle,
        1000));
    auto smData = sm.dump();
    std::shared_ptr<ample::game::Namespace> names = std::make_shared<ample::game::Namespace>();
    auto sameStateMachine = ample::game::StateMachine(ample::filing::JsonIO{smData}, names);
    auto sameData = sameStateMachine.dump();
    ASSERT_EQ(smData, sameData);
}

TEST(StateMachineIO, MultipleTransitions)
{
    auto sm = ample::game::StateMachine("Name");
    auto s1 = std::make_shared<ample::game::StateMachine::State>(sm, "s1");
    auto s2 = std::make_shared<ample::game::StateMachine::State>(sm, "s2");
    auto s3 = std::make_shared<ample::game::StateMachine::State>(sm, "s3");
    auto s4 = std::make_shared<ample::game::StateMachine::State>(sm, "s4");
    auto s5 = std::make_shared<ample::game::StateMachine::State>(sm, "s5");
    sm.setStartState(s1);
    s1->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t1",
        s2,
        1000));
    s1->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t2",
        s2,
        2000));
    s2->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t3",
        s1,
        3000));
    s2->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t4",
        s2,
        4000));
    s1->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t5",
        s3,
        5000));
    s1->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t6",
        s4,
        6000));
    s4->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t7",
        s2,
        7000));
    s4->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t8",
        s1,
        8000));
    s2->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t9",
        s4,
        9000));
    s1->addTransition(std::make_shared<ample::game::TimerTransition>(
        "t10",
        s5,
        10000));
    auto smData = sm.dump();
    std::shared_ptr<ample::game::Namespace> names = std::make_shared<ample::game::Namespace>();
    auto sameStateMachine = ample::game::StateMachine(ample::filing::JsonIO{smData}, names);
    auto sameData = sameStateMachine.dump();

    ASSERT_EQ(smData, sameData);
}

TEST(StateMachineIO, Actions)
{
    auto sm = ample::game::StateMachine("Name");
    auto run = std::make_shared<ample::game::StateMachine::State>(sm, "run");
    auto idle = std::make_shared<ample::game::StateMachine::State>(sm, "idle");
    sm.setStartState(run);
    run->addTransition(std::make_shared<ample::game::stateMachine::transitions::DistanceTransition>(
        "transition",
        idle,
        std::vector<std::string>{"first_body_name", "second_body_name"},
        ample::game::stateMachine::transitions::DistanceTransition::type::CLOSER_THAN,
        1000.0f));
    run->addOnActiveAction(std::make_shared<ample::game::stateMachine::actions::GraphicalRotateAction>(
        "action1",
        std::vector<std::string>{"name1", "name2"},
        ample::graphics::Vector3d<float>{1.0f, 0.0f, 0.0f},
        1.0f));
    idle->addOnStartAction(std::make_shared<ample::game::stateMachine::actions::GraphicalTranslateAction>(
        "action3",
        std::vector<std::string>{"hello", "world"},
        ample::graphics::Vector3d<float>{1.0f, 0.0f, 0.0f}));
    run->addOnStopAction(std::make_shared<ample::game::stateMachine::actions::GraphicalRotateAction>(
        "action300",
        std::vector<std::string>{"name4", "fff"},
        ample::graphics::Vector3d<float>{1.0f, 0.0f, 0.0f},
        100.0f));
    auto smData = sm.dump();
    std::shared_ptr<ample::game::Namespace> names = std::make_shared<ample::game::Namespace>();
    auto sameStateMachine = ample::game::StateMachine(ample::filing::JsonIO{smData}, names);
    auto sameData = sameStateMachine.dump();
    ASSERT_EQ(smData, sameData);
}

TEST(WorldObjectIO, Test1)
{
    auto layer = ample::physics::WorldLayer2d({0.1f, 10.0f}, 12.0f, 11.0f, 0.6f);
    auto obj1 = ample::physics::WorldObject2d("ObjectName",
                                              layer,
                                              ample::physics::BodyType::DYNAMIC_BODY,
                                              ample::geometry::RegularPolygon<float>(10.0f, 4),
                                              0.4f,
                                              {12.0f, 33.0f},
                                              {0.1f, 12.4f},
                                              ample::graphics::normalsMode::VERTEX,
                                              {11.0f, 12.0f},
                                              99.0f,
                                              {11.0f, -9.0f},
                                              123.0f,
                                              0.1f,
                                              5.0f,
                                              true,
                                              false,
                                              true,
                                              false,
                                              true,
                                              11.0f,
                                              {-0.1f, 1.0f},
                                              100.0f,
                                              2.0f);
    auto data1 = obj1.dump();
    auto obj2 = ample::physics::WorldObject2d(data1, layer);
    auto data2 = obj2.dump();
    ASSERT_EQ(data1, data2);
}
