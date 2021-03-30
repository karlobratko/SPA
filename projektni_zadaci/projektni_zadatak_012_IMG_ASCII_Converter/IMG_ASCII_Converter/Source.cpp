#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char* scale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
int numScale;

typedef struct
{
  size_t width;
  size_t height;
  unsigned char* data;
} image;

unsigned char luminanceFromRGB(unsigned char r, unsigned char g, unsigned char b)
{
  return (unsigned char)(0.2126 * r + 0.7152 * g + 0.0722 * b);
}

long loadImage(image** img, char* location)
{
  FILE* f = fopen(location, "rb");

  if (f == NULL)
  {
    puts("Opening failed...");
    return 0;
  }

  unsigned char* result;
  fseek(f, 0, SEEK_END);
  long size = ftell(f);

  if (size > SIZE_MAX)
  {
    puts("Size is too big!");
    fclose(f);
    return 0;
  }

  fseek(f, 0, SEEK_SET);
  result = (unsigned char*)malloc((size_t)size);

  if (size != fread(result, sizeof(unsigned char), (size_t)size, f))
  {
    free(result);
    puts("Reading failed...");
    fclose(f);
    return 0;
  }

  fclose(f);

  if (size < 54)
  {
    free(result);
    puts("Invalid file...");
    return 0;
  }

  if (result[0] != 'B' || result[1] != 'M')
  {
    free(result);
    puts("Incorrect file header...");
    return 0;
  }

  size_t specifiedSize = result[2] | result[3] << 8 | result[4] << 16 | result[5] << 24;

  if (specifiedSize != size)
  {
    free(result);
    puts("File sizes don't match...");
    return 0;
  }

  size_t pdOffset = result[10] | result[11] << 8 | result[12] << 16 | result[13] << 24;

  unsigned long width = result[18] | result[19] << 8 | result[20] << 16 | result[21] << 24;
  unsigned long height = result[22] | result[23] << 8 | result[24] << 16 | result[25] << 24;

  unsigned long bpp = result[28] | result[29] << 8;
  int noCompression = result[30] == 0 && result[31] == 0 && result[32] == 0 && result[33] == 0;

  if (bpp != 24 || !noCompression || width < 1 || height < 1 || width > 64000 || height > 64000)
  {
    free(result);
    puts("Unsupported BMP format, only 24 bits per pixel are supported...");
    return 0;
  }

  int bytesPerPixel = (int)(bpp / 8);

  size_t rowBytes = (width * bytesPerPixel + 3) / 4 * 4;

  printf("Bytes per row: %u\n", rowBytes);

  size_t usedRowBytes = width * bytesPerPixel;
  size_t imageBytes = rowBytes * height;

  if (pdOffset > size || pdOffset + imageBytes > size)
  {
    free(result);
    puts("Invalid offset specified...");
    return 0;
  }

  *img = malloc(sizeof(image));
  (*img)->height = height;
  (*img)->width = width;

  size_t imgSize = width * height;

  (*img)->data = (unsigned char*)malloc(imgSize);

  printf("Offset: %u\n", pdOffset);

  unsigned char* ptr = (*img)->data;
  unsigned char* srcPtr = &result[pdOffset];

  for (size_t i = 0; i < imgSize; ++i)
  {
    unsigned char r = *srcPtr;
    unsigned char g = *(srcPtr + 1);
    unsigned char b = *(srcPtr + 2);

    *ptr = luminanceFromRGB(r, g, b);
    ptr++;
    srcPtr += bytesPerPixel;

    if (i % width == 0)
    {
      srcPtr += rowBytes - usedRowBytes;
    }
  }

  free(result);

  return size;
}

void asciify(image* img)
{
  for (size_t y = img->height - 1; y > 0; --y)
  {
    for (size_t x = 0; x < img->width; ++x)
    {
      unsigned char c = *(img->data + x + img->width * y);
      int rescaled = c * numScale / 256;
      putchar(scale[numScale - rescaled]);
    }

    putchar('\n');
  }
}

void release(image* img)
{
  if (img)
  {
    if (img->data)
      free(img->data);

    free(img);
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    puts("Argument needed: filename.");
    return 1;
  }

  puts(argv[1]);

  setbuf(stdout, 0);

  numScale = strlen(scale) - 1;
  printf("ASCII Brightness Scale: %d\n", numScale);

  image* img = NULL;

  if (loadImage(&img, argv[1]))
  {
    printf("Image dimensions: %ux%u\n", img->width, img->height);

    asciify(img);

    release(img);
  }

  return 0;
}