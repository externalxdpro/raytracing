#ifndef IMAGE_H_
#define IMAGE_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Image {
  public:
    Image();
    ~Image();

    void Init(const int xSize, const int ySize, SDL_Renderer *pRenderer);
    void SetPixel(const int x, const int y, const double r, const double g,
                  const double b);
    void Display();

  private:
    Uint32 ConvertColor(const double red, const double green,
                        const double blue);
    void InitTexture();

    std::vector<std::vector<double>> m_rChannel;
    std::vector<std::vector<double>> m_gChannel;
    std::vector<std::vector<double>> m_bChannel;

    int m_xSize, m_ySize;

    SDL_Renderer *m_pRenderer;
    SDL_Texture *m_pTexture;
};

#endif // IMAGE_H_
