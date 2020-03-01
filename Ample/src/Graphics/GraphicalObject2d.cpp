#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include "GraphicalObject2d.h"
#include "Debug.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<double>> &graphicalShape)
    : _graphicalShape(graphicalShape) {}

void GraphicalObject2d::draw()
{
    glPushMatrix();
    glTranslated(getX() * _ratio, getY() * _ratio, getZ() * _ratio);
    glRotated(getAngleX(), 1.0, 0.0, 0.0);
    glRotated(getAngleY(), 0.0, 1.0, 0.0);
    glRotated(getAngleZ(), 0.0, 0.0, 1.0);
    glScaled(getScaleX(), getScaleY(), getScaleZ());
    drawSelf();
    for (auto subObject : _subObjects)
    {
        subObject->draw();
    }
    glPopMatrix();
}

void GraphicalObject2d::drawSelf()
{
    glBegin(GL_POLYGON);
    glColor3d(_r, _g, _b);
    for (auto vert : _graphicalShape)
    {
        glVertex2d(vert.x, vert.y);
    }
    glEnd();
}

void GraphicalObject2d::setRatio(double ratio)
{
    _ratio = ratio;
}

double GraphicalObject2d::getRatio() const
{
    return _ratio;
}

void GraphicalObject2d::setColor256(double r, double g, double b)
{
    _r = r / 256.0;
    _g = g / 256.0;
    _b = b / 256.0;
}
} // namespace ample::graphics
