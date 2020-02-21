#include <GL/gl.h>
#include <iostream>

#include "GraphicalObject2d.h"

namespace ample::graphics
{
GraphicalObject2d::GraphicalObject2d(const std::vector<Vector2d<pixel_t>> &graphicalShape)
    : _graphicalShape(graphicalShape) {}

void GraphicalObject2d::draw()
{
    glPushMatrix();
    glScaled(getScaleX(), getScaleY(), getScaleZ());
    glRotated(getAngleX(), 0.0, 0.0, 1.0);
    glRotated(getAngleY(), 0.0, 1.0, 0.0);
    glRotated(getAngleZ(), 1.0, 0.0, 0.0);
    glTranslated(getX(), getY(), getZ());
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
    glColor3d(0.8, 0.8, 0.8);
    for (auto vert : _graphicalShape)
    {
        glVertex2d(vert.x, vert.y);
    }
    glEnd();
}
} // namespace ample::graphics
