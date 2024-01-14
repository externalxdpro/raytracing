#include "App.hpp"

App::App() {
    isRunning = true;
    pWindow = nullptr;
    pRenderer = nullptr;
}

bool App::OnInit() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    pWindow =
        SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    if (pWindow) {
        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        m_image.Init(1280, 720, pRenderer);

        for (int x = 0; x < 1280; x++) {
            for (int y = 0; y < 720; y++) {
                double r = static_cast<double>(x) / 1280.0 * 255.0;
                double g = static_cast<double>(y) / 720.0 * 255.0;
                m_image.SetPixel(x, y, r, g, 0.0);
            }
        }
    } else {
        return false;
    }

    return true;
};

int App::OnExecute() {
    SDL_Event event;

    if (!OnInit()) {
        return -1;
    }

    while (isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }

        App::OnLoop();
        App::OnRender();
    }

    return 1;
}

void App::OnEvent(SDL_Event *event) {
    if (event->type == SDL_QUIT) {
        isRunning = false;
    }
}

void App::OnLoop() {}

void App::OnRender() {
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);

    m_image.Display();

    SDL_RenderPresent(pRenderer);
}

void App::OnExit() {
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    pWindow = nullptr;
    SDL_Quit();
}
