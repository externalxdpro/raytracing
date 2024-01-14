#ifndef APP_H_
#define APP_H_

#include "src/Image.hpp"
#include <SDL2/SDL.h>

class App {
  public:
    App();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

  private:
    Image m_image;

    bool isRunning;
    SDL_Window *pWindow;
    SDL_Renderer *pRenderer;
};

#endif // APP_H_
