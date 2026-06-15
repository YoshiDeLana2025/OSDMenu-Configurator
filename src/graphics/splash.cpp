#include "graphics/graphics.h"

extern unsigned char title_png[];
extern unsigned int size_title_png;

static const uint64_t SPLASH_BG_RGBAQ =
    GS_SETREG_RGBAQ(0x4A, 0x09, 0x5A, 0x80, 0x00);

// Implemented in graphics.cpp
void showSplashScreen(void) {
  if (!getGSGLOBAL())
    return;

  clearScreen(SPLASH_BG_RGBAQ);
  const int w = getGSGLOBAL()->Width;
  const int h = getGSGLOBAL()->Height;

  GSTEXTURE *tex_title = load_png_from_memory(title_png, size_title_png, true);

  if (tex_title) {
    float tw = (float)tex_title->Width;
    float th = (float)tex_title->Height;
    float cx = (float)w * 0.5f;
    float cy = (float)h * 0.5f - 30.0f;
    drawImage(tex_title, 0, 0, tw, th, 0.0f, 0.0f, tw, th,
              GS_SETREG_RGBA(0x80, 0x80, 0x80, 0x80));
  }

  flipScreen();

  if (tex_title)
    UnloadTexture(tex_title);
}
