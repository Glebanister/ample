#include <GL/gl.h>
#include <iostream>

#include "GraphicalObject2d.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d> &graphicalShape)
    : _graphicalShape(graphicalShape) {}

void GraphicalObject2d::draw()
{
    glPushMatrix();
    glScaled(getScaleX(), getScaleY(), 1);
    glRotated(getAngle(), 0, 0, 1);
    glTranslated(getX(), getY(), 0);
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
    glColor3d(0.3, 0.3, 0.3);
    for (auto vert : _graphicalShape)
    {
        glVertex2d(vert.x, vert.y);
    }
    glEnd();
}
} // namespace ample::graphics
