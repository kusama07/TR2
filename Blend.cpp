#include "Blend.h"

#include <Novice.h>
#define kWindowWidth 1280
#define kWindowHeight 720

int GetColor(unsigned int red, unsigned int  green, unsigned int blue, int  alpha)
{
	//unsigned char top = 0x;
	int color = (red << 24) | (green << 16) | (blue << 8) | alpha;
	return color;
}

void AlphaTrans(int* alpha, const char keys[])
{
	if (*alpha < 255)
	{
		if (keys[DIK_UP])
		{
			*alpha += 1;
		}
	}

	if (*alpha > 0)
	{
		if (keys[DIK_DOWN])
		{
			*alpha -= 1;
		}
	}
}

void SetBlendMode(int* blend, const char keys[])
{
	if (keys[DIK_1])
	{
		*blend = kBlendModeNormal;
	}

	else if (keys[DIK_2])
	{
		*blend = kBlendModeAdd;
	}

	else if (keys[DIK_3])
	{
		*blend = kBlendModeSubtract;
	}

	else if (keys[DIK_4])
	{
		*blend = kBlendModeNone;
	}
}

void DrawSprite(int x, int y, int textureHandle, int color)
{
	Novice::DrawSprite(x, y, textureHandle, 1.0f, 1.0f, 0.0f, color);
}

void DrawBackground(int textureHandle)
{
	Novice::DrawQuad(0, 0, kWindowWidth, 0, 0, kWindowHeight, kWindowWidth, kWindowHeight, 0, 0, kWindowWidth, kWindowHeight, textureHandle, BLACK);
}

void TH(int dx, int dy, int sx, int sy, int w, int h, int textureHandle, int color)
{
	Novice::DrawSpriteRect(dx, dy, sx, sy, w, h, textureHandle, 1.0f, 1.0f, 0.0f, color);
}