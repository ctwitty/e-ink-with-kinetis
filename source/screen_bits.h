#ifndef SCREENBITS_H
#define SCREENBITS_H

typedef struct image {
  int x;
  int y;
  int h;
  int w;
  char *bitmap;
} image_t;

#endif
