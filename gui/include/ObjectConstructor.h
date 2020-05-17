#pragma once

#include <memory>
#include <string>
#include <vector>

#include <imgui.h>
#include <imfilebrowser.h>

#include "ample/Level.h"
#include "ample/NamedObject.h"

#include "InterfaceUnit.h"
#include "Utils.h"

namespace ample::gui
{
namespace param
{
struct Parameter
{
    Parameter(const std::string &paramName);
    virtual void imguiInput() = 0;
    virtual void reset() = 0;
    std::string name;

    virtual ~Parameter() = default;
};

template <typename Ret>
inline Ret value(Parameter &);

struct Int : Parameter
{
    Int(const std::string &name, int value, int min, int max, int step = 1);
    Int(const std::string &name, int value, int step = 1);

    void imguiInput() override;
    void reset() override;

    int value = 0;
    int step = 1, min = 0, max = 0;
    bool unlimitedMin = false;
    bool unlimitedMax = false;

private:
    const int _begin;
};

struct Float : Parameter
{
    Float(const std::string &name, float value, float min, float max, float step = 0.1f);
    Float(const std::string &name, float value, float step = 0.1f);

    void imguiInput() override;
    void reset() override;

    float value;
    float step = 0.1f, min = 0.0f, max = 0.0f;
    bool unlimitedMin = false;
    bool unlimitedMax = false;

private:
    const float _begin;
};

struct String : Parameter
{
    String(const std::string &name);

    void imguiInput() override;
    void reset() override;

    char buffer[255] = {'\0'};
};

struct Path : Parameter
{
    Path(const std::string &name, ImGuiFileBrowserFlags_);

    void imguiInput() override;
    void reset() override;

    ImGui::FileBrowser _filebrowser;
    std::string _buffer;
};

struct LevelsList : Parameter
{
    LevelsList(const std::string &name, std::vector<std::shared_ptr<game::game2d::Level>> *list);

    void imguiInput() override;
    void reset() override;

    std::shared_ptr<game::game2d::Level> selectedObject = nullptr;
    std::vector<std::shared_ptr<game::game2d::Level>> *_list;
};
} // namespace param

class ObjectConstructor
{
public:
    class ParamsAdder
    {
    public:
        ParamsAdder(std::vector<std::unique_ptr<param::Parameter>> &list);

        template <class Param, typename... Args>
        ParamsAdder &add(Args... args);

    private:
        std::vector<std::unique_ptr<param::Parameter>> &_list;
    };

public:
    ObjectConstructor(const std::string &_buttonName = "Create",
                      bool closable = true,
                      ImGuiWindowFlags_ = ImGuiWindowFlags_None,
                      bool modal = true);

    template <class Creator>
    void drawInterface(const Creator &);
    ParamsAdder &addParameters();

private:
    std::vector<std::unique_ptr<param::Parameter>> _params;
    bool _success = false;
    std::string _errorString;
    ParamsAdder _adder;
    std::string _buttonName;
    gui_utils::MessagePopup _errorPopup;
    bool _closable = true;
    ImGuiWindowFlags_ _windowFlags;
    bool _closed = false;
    bool _modal = true;
};
} // namespace ample::gui

#include "templates/ObjectConstructor.hpp"
