#include "gtest/gtest.h"
#include "ample/GraphicalObject2d.h"
#include "ample/RegularPolygon.h"
#include "ample/JsonIO.h"
#include "ample/StateMachine.h"
#include "ample/Action.h"

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
    auto sameStateMachine = ample::game::StateMachine(ample::filing::JsonIO{smData});
    auto sameData = sameStateMachine.dump();
    ASSERT_EQ(smData, sameData);
}
