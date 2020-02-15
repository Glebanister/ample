#include <GL/gl.h>
#include <iostream>

#include "GraphicShape.h"
#include "WindowObject.h"
#include "Clock.h"

namespace graphics
{
GraphicShape::GraphicShape(const std::vector<std::pair<int, int>> &verts)
    : _verts(verts) {}

void GraphicShape::draw()
{
    //create test checker image
    unsigned char texDat[64];
    for (int i = 0; i < 64; ++i)
        texDat[i] = ((i + (i / 5)) % 7) * 1221 + 123;

    //upload to GPU texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 8, 8, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texDat);
    glBindTexture(GL_TEXTURE_2D, 0);

    //match projection to window resolution (could be in reshape callback)

    //clear and draw quad with texture (could be in display callback)
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, 0);
    glTexCoord2i(0, 1);
    glVertex2i(0, 1080);
    glTexCoord2i(1, 1);
    glVertex2i(1920, 1080);
    glTexCoord2i(1, 0);
    glVertex2i(1920, 0);
    glEnd();
    std::cout << os::Clock::getFPS() << std::endl;
}
} // namespace graphics
