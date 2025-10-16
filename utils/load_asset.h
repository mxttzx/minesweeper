#ifndef LOAD_ASSET_H_
#define LOAD_ASSET_H_

#include "SDL.h"

#define IMAGE_DIR "../gui/Images/"
#define IMAGE_COVERED "covered.bmp"
#define IMAGE_MINE "mine.bmp"
#define IMAGE_FLAG "flagged.bmp"

char *_build_asset_path(const char *file);
SDL_Surface *_load_image(const char *);

#endif
