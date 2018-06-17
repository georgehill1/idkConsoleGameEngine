#include "idkConsoleGameEngine.h"

class Breakout : public idkConsoleGameEngine
{
public:
	Breakout()
	{
	}

	string level;
	int width = 16;
	int height = 15;
	int blockSize = 8*4;

	float batPos = 64.0;

	float ballX = (width*blockSize)/2.0f;
	float ballY = (height*blockSize) / 2.0f;
	float ballDX, ballDY;
	float ballRad = 8;

public:
	bool OnUserCreate()
	{
		level += "################";
		level += "#..............#";
		level += "#...11111111...#";
		level += "#...11111111...#";
		level += "#...111..111...#";
		level += "#...11....11...#";
		level += "#...1......1...#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";
		level += "#..............#";

		float ballAngle = ((float)rand() / (float)(RAND_MAX)) * 3.14159 * 2.0;
		ballAngle = 0.6;
		ballDX = cosf(ballAngle);
		ballDY = sinf(ballAngle);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		int batWidth = 10*4;
		float speed = 60.0*4;
		float batSpeed = 60.0*4;

		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		// Controls

		if (GetKey(VK_LEFT).bHeld) batPos -= batSpeed * fElapsedTime;
		if (GetKey(VK_RIGHT).bHeld) batPos += batSpeed * fElapsedTime;

		float oldX = ballX;
		float oldY = ballY;

		ballX += ballDX * fElapsedTime * speed;
		ballY += ballDY * fElapsedTime * speed;

		int cellOldX = (int)oldX / blockSize;
		int cellOldY = (int)oldY / blockSize;

		int cellNewX = (int)ballX / blockSize;
		int cellNewY = (int)ballY / blockSize;

		char newCell = level[cellNewY*width + cellNewX];
		char oldCell = level[cellOldY*width + cellOldX];

		if (newCell != '.')
		{
			if (newCell == '1')
				level[cellNewY*width + cellNewX] = '.';

			if (cellNewX != cellOldX) ballDX *= -1;
			if (cellNewY != cellOldY) ballDY *= -1;
		}

		if (ballY + ballRad > (height * blockSize - 2))
		{
			if (ballX > (batPos - batWidth) && (ballX < (batPos + batWidth)))
				ballDY *= -1;
			else
			{
				ballX = (width / 2.0f) * blockSize;
				ballY = (height / 2.0f) * blockSize;
				float ballAngle = ((float)rand() / (float)(RAND_MAX)) * 3.14159 * 2.0;
				ballDX = cosf(ballAngle);
				ballDY = sinf(ballAngle);
			}
		}

		if (batPos - batWidth < blockSize)
			batPos = blockSize + batWidth;
		if (batPos + batWidth > blockSize * (width - 1))
			batPos = blockSize * (width - 1) - batWidth;

		// Draw level
		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				switch (level[y*width + x])
				{
				case '#':
					// boundary
					Fill(x*blockSize, y*blockSize, (x + 1)*blockSize, (y + 1)*blockSize, RGB(255,255,255));
					break;
				case '1':
					// block
					Fill(x*blockSize, y*blockSize, (x + 1)*blockSize, (y + 1)*blockSize, RGB(255,0,255));
					break;
				case '.':
					// empty
					Fill(x*blockSize, y*blockSize, (x + 1)*blockSize, (y + 1)*blockSize, RGB(0,0,0));
					break;

				}
			}

		FillCircle(ballX, ballY, ballRad, RGB(255,255,0));

		DrawLine(batPos - batWidth, height * blockSize - 2, batPos + batWidth, height * blockSize - 2, RGB(255,255,255));

		return true;
	}
};

int main() {
	Breakout bo;
	bo.ConstructConsole(134*4, 130*4);
	bo.Start();

	return 0;
}