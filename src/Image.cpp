#include "Image.hpp"

Image::Image() {
    m_xSize = 0;
    m_ySize = 0;
    m_pTexture = nullptr;
}

Image::~Image() {
    if (m_pTexture) {
        SDL_DestroyTexture(m_pTexture);
    }
}

void Image::Init(const int xSize, const int ySize, SDL_Renderer *pRenderer) {
    m_rChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_gChannel.resize(xSize, std::vector<double>(ySize, 0.0));
    m_bChannel.resize(xSize, std::vector<double>(ySize, 0.0));

    m_xSize = xSize;
    m_ySize = ySize;

    m_pRenderer = pRenderer;

    InitTexture();
}

void Image::SetPixel(const int x, const int y, const double r, const double g,
                     const double b) {
    m_rChannel[x][y] = r;
    m_gChannel[x][y] = g;
    m_bChannel[x][y] = b;
}

void Image::Display() {
    Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];

    memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));

    for (int x = 0; x < m_xSize; x++) {
        for (int y = 0; y < m_ySize; y++) {
            tempPixels[y * m_xSize + x] = ConvertColor(
                m_rChannel[x][y], m_gChannel[x][y], m_gChannel[x][y]);
        }
    }

    SDL_UpdateTexture(m_pTexture, nullptr, tempPixels,
                      m_xSize * sizeof(Uint32));

    delete[] tempPixels;

    SDL_Rect srcRect, bounds;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = m_xSize;
    srcRect.h = m_xSize;
    bounds = srcRect;
    SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);
}

void Image::InitTexture() {
    Uint32 rMask, gMask, bMask, aMask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rMask = 0xff000000;
    gMask = 0x00ff0000;
    bMask = 0x0000ff00;
    aMask = 0x000000ff;
#else
    rMask = 0x000000ff;
    gMask = 0x0000ff00;
    bMask = 0x00ff0000;
    aMask = 0xff000000;
#endif

    if (m_pTexture) {
        SDL_DestroyTexture(m_pTexture);
    }

    SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32,
                                                    rMask, gMask, bMask, aMask);
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
}

Uint32 Image::ConvertColor(const double red, const double green,
                           const double blue) {
    auto r = static_cast<unsigned char>(red);
    auto g = static_cast<unsigned char>(green);
    auto b = static_cast<unsigned char>(blue);

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 pixelColor = (r << 24) + (g << 16) + (b << 8) + 255;
#else
    Uint32 pixelColor = (255 << 24) + (r << 16) + (g << 8) + b;
#endif

    return pixelColor;
}
