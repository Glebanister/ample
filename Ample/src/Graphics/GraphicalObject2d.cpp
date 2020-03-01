#include <GL/gl.h>
#include <memory>

#include "GraphicalObject2d.h"
#include "Debug.h"

namespace ample::graphics
{
void GraphicalObject2d::draw()
{
    glPushMatrix();
    glScaled(getScaleX(), getScaleY(), getScaleZ());
    glTranslated(getX() * _ratio, getY() * _ratio, getZ() * _ratio);
    glRotated(getAngleX(), 1.0, 0.0, 0.0);
    glRotated(getAngleY(), 0.0, 1.0, 0.0);
    glRotated(getAngleZ(), 0.0, 0.0, 1.0);
    drawSelf();
    for (auto subObject : _subObjects)
    {
        subObject->draw();
    }
    glPopMatrix();
}

void GraphicalObject2d::drawSelf()
{
    _vertexArray->execute();
}

void GraphicalObject2d::setRatio(double ratio)
{
    _ratio = ratio;
}

double GraphicalObject2d::getRatio() const
{
    return _ratio;
}
} // namespace ample::graphics
