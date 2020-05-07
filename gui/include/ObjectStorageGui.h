#pragma once

#include "ample/Singleton.h"

namespace ample::gui
{
class ObjectStorageGui : public ample::utils::Singleton<ObjectStorageGui>
{
public:
    void Browser();
    void Viewer();
    void Editor();
};
}
