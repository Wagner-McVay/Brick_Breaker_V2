#include "mathLib.h"
#include "sfwdraw.h"
#include <iostream>
using namespace sfw;

float GameWidth = 1600;
float GameHeight = 1000;
int Loose = 0;

void drawBox(const Vec2 &a, const Vec2 &b, unsigned int color)
{
	drawLine(a.x + b.x, a.y + b.y, a.x - b.x, a.y + b.y, color);
	drawLine(a.x + b.x, a.y + b.y, a.x + b.x, a.y - b.y, color);
	drawLine(a.x - b.x, a.y - b.y, a.x - b.x, a.y + b.y, color);
	drawLine(a.x - b.x, a.y - b.y, a.x + b.x, a.y - b.y, color);
}

void main()
{
	initContext(GameWidth, GameHeight, "Brick Blaster");

	class Player
	{
	public:
		float scale = 12;
		float moveSpeed = 500;
		Vec2 pos = { GameWidth / 2, GameHeight / 10 };
		//unsigned P = loadTextureMap("./Textures/oscillating fan.png");
		//unsigned int color = WHITE;
		unsigned P = loadTextureMap("./Textures/Paddle.png");
		unsigned int color = RED;
		Vec2 dim = { (getTextureWidth(P) / scale) / 2, (getTextureHeight(P) / scale) / 2 };

		void drawPlayer()
		{
			drawTexture(P, pos.x, pos.y, dim.x * 2, dim.y * 2, 0, true, 0, color);
			//drawBox(pos, dim, WHITE);
			if ((getKey(KEY_D) || getKey(KEY_RIGHT)) && ((pos.x + dim.x) < GameWidth))
			{
				pos.x += (getDeltaTime() * moveSpeed);
			}
			if ((getKey(KEY_A) || getKey(KEY_LEFT)) && ((pos.x - dim.x) > 0))
			{
				pos.x -= (getDeltaTime() * moveSpeed);
			}
		}
	};
	Player Paddle;

	class Brick
	{
	public:
		float scale = 12;
		Vec2 pos = { GameWidth / 2, (GameHeight / 2) + 100 };
		int HP = 3;
		unsigned T1 = loadTextureMap("./Textures/Brick01.png");
		unsigned T2 = loadTextureMap("./Textures/Brick02.png");
		unsigned T3 = loadTextureMap("./Textures/Brick03.png");
		unsigned T = T1;
		Vec2 dim = { (getTextureWidth(T) / (scale / 2)) / 2, (getTextureHeight(T) / scale) / 2 };
		unsigned int color = SKY_BLUE;
		bool Broken = false;
		void drawBrick()
		{
			if (Broken == false)
			{
				drawTexture(T, pos.x, pos.y, dim.x * 2, dim.y * 2, 0, true, 0, color);
				if (HP == 3) { color = SKY_BLUE; T = T1; }
				if (HP == 2) { color = PURPLE; T = T2; }
				if (HP == 1) { color = BLUE; T = T3; }
			}
			if (HP == 0) Broken = true;
		}
	};
	const int Bricks = 55;
	Brick Brick[Bricks];
	int y = -5;
	int z = 0;
	for (int x = 0; x < Bricks; x++)
	{
		Brick[x].pos.x = { Brick[x].pos.x + (Brick[x].dim.x * 2) * y };
		Brick[x].pos.y = { Brick[x].pos.y + (Brick[x].dim.y * 2) * z };
		y++;
		if (y == 6) { y = -5; z++; }
	}
	Vec2 q;

A:

	class BlastBall
	{
	public:
		float scale = 18;
		Vec2 pos = { GameWidth/2, (GameHeight/10) + 50 };
		Vec2 vel = { 0, 0 };
		float moveSpeed = 500;
		//unsigned B = loadTextureMap("./Textures/david hasselhoff.png");
		//vec2 dim = { (getTextureWidth(B) / 3.0f) / 2, (getTextureHeight(B) / 3.0f) / 2 };
		//unsigned int color = WHITE;
		unsigned B = loadTextureMap("./Textures/Ball.png");
		Vec2 dim = { (getTextureWidth(B) / scale) / 2, (getTextureHeight(B) / scale) / 2 };
		unsigned int color = RED;
		bool Active = false;
		void Bounce(float angle)
		{
			vel.x = cos(angle) * getDeltaTime() * moveSpeed;
		}
		void drawBall()
		{		
			drawTexture(B, pos.x, pos.y, dim.x * 2, dim.y * 2, 0, true, 0, color);
			//drawBox(pos, dim, WHITE);
			if (Active == true)
			{
				pos.x += vel.x;
				pos.y += vel.y;
			}
		}
	};
	BlastBall Ball;

	bool collision[Bricks];
	for (int x = 0; x < Bricks; x++)
	{
		collision[x] = false;
	}
	int c = -1;
	unsigned Z = loadTextureMap("./Textures/Background1.jpg");

	// Main Game
	while (stepContext())
	{
		
		drawTexture(Z, 0, GameHeight, GameWidth, GameHeight, 0, false, 0, WHITE);

		bool Win = true;
		for (int x = 0; x < Bricks; x++)
		{
			Brick[x].drawBrick();
			if (Brick[x].HP > 0) { Win = false; }
		}
		if (Win == true) goto END;
		Paddle.drawPlayer();
		Ball.drawBall();


		if (Ball.Active == false) { Ball.pos.x = Paddle.pos.x; }

		// paddle collision
		if ((BoxCollision(Ball.pos, Ball.dim, Paddle.pos, Paddle.dim) == true) && (Ball.vel.y < 0))
		{
			Vec2 v = { Paddle.pos.x, 0 };
			c = -1;
			//float temp = Paddle.pos.y;
			Ball.vel.y *= -1;
			//Paddle.pos.y = 35;
			Ball.Bounce(get2DAngle(v, Ball.pos));
			//Paddle.pos.y = temp;
		}

		// brick collision
		
		for (int x = 0; x < Bricks; x++)
		{
			if (Brick[x].Broken == false)
			{
				if (BoxCollision(Ball.pos, Ball.dim, Brick[x].pos, Brick[x].dim) == true)
				{
					collision[x] = true;
					for (int y = 0; y < Bricks; y++)
					{
						if (y == x) ++y;
						if (Brick[y].Broken == false)
						{
							if (magnitude2(Ball.pos, Brick[x].pos) > magnitude2(Ball.pos, Brick[y].pos) || c == x)
							{
								collision[x] = false;
							}
						}
					}
					if (collision[x] == true)
					{
						Vec2 t = Ball.pos - Brick[x].pos;
						// if right or left box
						if (((t.y <= t.x - Brick[x].dim.x / 2) && (t.y >= -t.x + Brick[x].dim.x / 2) && (Ball.vel.x < 0)) || ((t.y >= t.x + Brick[x].dim.x / 2) && (t.y <= -t.x - Brick[x].dim.x / 2)) && (Ball.vel.x > 0))
						{
							Brick[x].HP -= 1;
							Ball.vel.x = -Ball.vel.x;
						}
						// if below or above box
						else if (((t.y > t.x - Brick[x].dim.x / 2) && (t.y > -t.x - Brick[x].dim.x / 2) && (Ball.vel.y < 0)) || ((t.y < t.x + Brick[x].dim.x / 2) && (t.y < -t.x + Brick[x].dim.x / 2)) && (Ball.vel.y > 0))
						{
							Brick[x].HP -= 1;
							Ball.vel.y = -Ball.vel.y;
						}
						c = x;
					}
				}
			}
		}

		
		
		
		if (Ball.Active == false) 
		{ 
			if (getKey(KEY_DOWN) || getKey(KEY_SPACE))
			{
				Ball.Active = true;
			}
			Ball.vel.y = getDeltaTime() * Ball.moveSpeed;
		}
		
		// if the top of the ball goes above the game screen & is moving up {reverse vertical velocity}
		if ((Ball.pos.y + Ball.dim.y >= GameHeight) && (Ball.vel.y > 0)) { Ball.vel.y *= -1; c = -1;; }

		// if the right of the ball goes right beyond the game screen & is moving right {reverse horizontal velocity}
		if ((Ball.pos.x + Ball.dim.x >= GameWidth) && (Ball.vel.x > 0)) { Ball.vel.x *= -1; c = -1;; }

		// if the left of the ball goes left beyond the game screen & is moving right {reverse horizontal velocity}
		if ((Ball.pos.x - Ball.dim.x <= 0) && (Ball.vel.x < 0)) { Ball.vel.x *= -1; c = -1;; }

		// if the top of the ball goes above the game screen & is moving up {reverse vertical velocity}
		if (Ball.pos.y - Ball.dim.y <= 0) { Loose++; if (Loose == 3) {goto END; } goto A;
	}
	}
	END:
	termContext();
}
