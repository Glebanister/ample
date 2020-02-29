#include "WorldObject2d.h"
#include <cmath>

namespace ample::physics
{
void DefWorldObject2d::setBodyType(BodyType type)
{
    switch (type)
    {
    case BodyType::staticBody:
        bodyDef.type = b2_staticBody;
        return;
    case BodyType::kinematicBody:
        bodyDef.type = b2_kinematicBody;
        return;
    case BodyType::dynamicBody:
        bodyDef.type = b2_dynamicBody;
        return;
    }
}

void DefWorldObject2d::setPosition(ample::graphics::Vector2d<float> pos)
{
    bodyDef.position.Set(pos.x, pos.y);
}

void DefWorldObject2d::setAngle(float angle)
{
    bodyDef.angle = angle;
}

void DefWorldObject2d::setLinearVelocity(ample::graphics::Vector2d<float> velocity)
{
    bodyDef.linearVelocity.Set(velocity.x, velocity.y);
}

void DefWorldObject2d::setAngularVelocity(float velocity)
{
    bodyDef.angularVelocity = velocity;
}

void DefWorldObject2d::setLinearDumping(float velocity)
{
    bodyDef.linearDamping = velocity;
}

void DefWorldObject2d::setAngularDumping(float velocity)
{
    bodyDef.angularDamping = velocity;
}

void DefWorldObject2d::setAllowSleep(bool b)
{
    bodyDef.allowSleep = b;
}

void DefWorldObject2d::setAwake(bool b)
{
    bodyDef.awake = b;
}

void DefWorldObject2d::setFixedRotation(bool b)
{
    bodyDef.fixedRotation = b;
}

void DefWorldObject2d::setBullet(bool b)
{
    bodyDef.bullet = b;
}

void DefWorldObject2d::setEnabled(bool b)
{
    bodyDef.enabled = b;
}

void DefWorldObject2d::setGravityScale(float scale)
{
    bodyDef.gravityScale = scale;
}

WorldObject2d::WorldObject2d(const DefWorldObject2d &def,
                             const std::vector<ample::graphics::Vector2d<double>> &shape) : GraphicalObject2d(shape), _bodyDef(def.bodyDef) {}

void WorldObject2d::setZIndex(double z)
{
    zIndex = z;
}

double WorldObject2d::getX() const
{
    return _body->GetPosition().x;
}

double WorldObject2d::getY() const
{
    return _body->GetPosition().y;
}

double WorldObject2d::getZ() const
{
    return zIndex;
}

double WorldObject2d::getAngleX() const
{
    return 0;
}

double WorldObject2d::getAngleY() const
{
    return 0;
}

double WorldObject2d::getAngleZ() const
{
    return _body->GetAngle() * (180 / M_PI);
}

double WorldObject2d::getScaleX() const
{
    return 1;
}

double WorldObject2d::getScaleY() const
{
    return 1;
}

double WorldObject2d::getScaleZ() const
{
    return 1;
}
} // namespace ample::physics