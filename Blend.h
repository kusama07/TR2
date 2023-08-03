#pragma once

int GetColor(unsigned int red, unsigned int  green, unsigned int  blue, int  alpha);

void AlphaTrans(int* alpha, const char keys[]);

void SetBlendMode(int* blend, const char keys[]);

void DrawSprite(int x, int y, int textureHandle, int color);

void TH(int dx, int dy, int sx, int sy, int w, int h, int textureHandle, int color);

void DrawBackground(int textureHandle);

