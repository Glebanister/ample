#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "DemoGame.h"
#include "RegularPolygon.h"
#include "Texture.h"
#include "Clock.h"
#include "KeyboardTransition.h"
#include "MouseTransition.h"
#include "TimerTransition.h"
#include "Factory.h"

struct Shape : public ample::filing::NamedObject
{
    Shape(const std::string &name, const std::string &className)
        : NamedObject(name, className) {}
    virtual void speak() = 0;
};

struct Circle : public Shape
{
    Circle(int name)
        : Shape(std::to_string(name), "Circle") {}
    void speak() final
    {
        std::cout << "CIIIRCLEEE!!!" << ' ' << className() << ' ' << name() << std::endl;
    }
};

struct Rectangle : public Shape
{
    Rectangle(int name)
        : Shape(std::to_string(name), "Rectangle") {}
    void speak() final
    {
        std::cout << "RRRRRECTANGLE!" << ' ' << className() << ' ' << name() << std::endl;
    }
};

static ample::utils::Factory<Shape, int> ShapeFactory;
static ample::utils::Factory<Shape, int>::Register<Circle> CircleRegister("Circle");
static ample::utils::Factory<Shape, int>::Register<Rectangle> RectangleRegister("Rectangle");

DemoGame::DemoGame(ample::window::Window &window)
    : ample::game::game2d::Game2d(window)
{
    // auto obj1 = ample::graphics::GraphicalObject2d("ObjectName", "GraphicalObject", ample::geometry::RegularPolygon<float>(10.0f, 4), 10.0f, 3.0f, {1.0f, 2.0f}, {3.0f, 4.0f}, ample::graphics::normalsMode::FACE, {0.0f, 0.0f}, 1.0f);
    // auto data = obj1.dump();
    // auto obj2 = ample::graphics::GraphicalObject2d(data);
    // // auto run = std::make_shared<ample::game::StateMachine::State>(obj1.stateMachine(), "run");
    // // obj1.idleState()->addTransition(std::make_shared<ample::game::TimerTransition>("transition_name", run, 3000));
    // // auto obj2 = ample::graphics::GraphicalObject2d("ObjectName", "GraphicalObject", ample::geometry::RegularPolygon<float>(10.0f, 4), 10.0f, 3.0f, {1.0f, 2.0f}, {3.0f, 4.0f}, ample::graphics::normalsMode::FACE, {0.0f, 0.0f}, 1.0f);
    // // ample::filing::Scene2d s{"front scene", {0.0f, 0.0f}, 1.0f, 43.0f, 0.3f};
    // // s.addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(obj1.facePointer()));
    // // s.addObject(std::static_pointer_cast<ample::graphics::GraphicalObject>(obj2.sidePointer()));
    // // std::cout << s.dump() << std::endl;
    // // ShapeFactory.produce("Circle", 1)->speak();
    // // ShapeFactory.produce("Rectangle", 2)->speak();
}

DemoGame::~DemoGame()
{
    // std::cout << Game2d::controller().dump() << std::endl;;
}
