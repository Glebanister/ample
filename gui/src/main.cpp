#include <iostream>
#include <imgui.h>
#include <imgui_sdl.h>
#include <SDL2/SDL.h>
#include <ample/SDLEnvironment.h>
#include <ample/Window.h>
#include <ample/Clock.h>
#include <ample/WindowActivity.h>

class ImguiActivity : public ample::window::WindowActivity
{
public:
    ImguiActivity(ample::window::Window &window)
        : WindowActivity(window),
          _renderer(SDL_CreateRenderer(_window.pointer(), -1, SDL_RENDERER_ACCELERATED))
    {
        ImGui::CreateContext();
        ImGuiSDL::Initialize(_renderer, getWidth(), getHeight());

        texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
        {
            SDL_SetRenderTarget(_renderer, texture);
            SDL_SetRenderDrawColor(_renderer, 255, 0, 255, 255);
            SDL_RenderClear(_renderer);
            SDL_SetRenderTarget(_renderer, nullptr);
        }
    }

    void onActive() override
    {
        ample::window::WindowActivity::onActive();
        ImGuiIO &io = ImGui::GetIO();
        io.DeltaTime = 1.0f / std::max(20.0, std::min(120.0, ample::time::Clock::getFPS()));
        io.MousePos = ImVec2(static_cast<float>(eventManager->mouse()->getMouseX()), static_cast<float>(eventManager->mouse()->getMouseY()));
        io.MouseDown[0] = eventManager->mouse()->isLeftPressed() & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = eventManager->mouse()->isRightPressed() & SDL_BUTTON(SDL_BUTTON_RIGHT);
        io.MouseWheel = static_cast<float>(eventManager->mouse()->getWheelY());
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Begin("Image");
        ImGui::Image(texture, ImVec2(100, 100));
        ImGui::End();
        SDL_SetRenderDrawColor(_renderer, 114, 144, 154, 255);
        SDL_RenderClear(_renderer);
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
        SDL_RenderPresent(_renderer);
    }

    ~ImguiActivity()
    {
        ImGuiSDL::Deinitialize();
        SDL_DestroyRenderer(_renderer);
        ImGui::DestroyContext();
    }

private:
    SDL_Renderer *_renderer;
    SDL_Texture *texture;
};

int main()
{
    ample::window::Window window{"ample gui", 0, 0, 1024, 512, ample::window::UNDEFINED_POS, ample::window::MINIMIZED | ample::window::RESIZABLE};
    ImguiActivity ampleGui{window};
    ampleGui.loop();

    return 0;
}
