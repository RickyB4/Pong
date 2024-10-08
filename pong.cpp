#include <raylib.h>
// the ball
struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, WHITE);
	}

};
// the paddles
struct Paddle
{
	float x, y; 
	float speed; 
	float width, height; 

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2 , 10 , 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}

};

int main(void) {
	InitWindow(1000, 600, "Pong");

	Ball ball; 
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.speedX = -350; 
	ball.speedY = 1; 
	ball.radius = 5; 

	Paddle leftPaddle; 
	leftPaddle.x = 50; 
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 15; 
	leftPaddle.height = 100; 
	leftPaddle.speed = 800; 

	Paddle rightPaddle; 
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 15;
	rightPaddle.height = 100;
	rightPaddle.speed = 800;

	const char* winnerText = nullptr; 

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1; 
		}

		if (ball.y > GetScreenHeight()) 
		{
			ball.y = GetScreenHeight(); 
			ball.speedY *= -1; 
		}
		// controls
		if (IsKeyDown(KEY_W))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}

		// collision
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f; 
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		// bounds
		if (leftPaddle.y < GetScreenHeight() / 12)
		{
			leftPaddle.y = GetScreenHeight() / 12;
		}

		if (rightPaddle.y < GetScreenHeight() / 12)
		{
			rightPaddle.y = GetScreenHeight() / 12;
		}

		if (leftPaddle.y > GetScreenHeight() - 50)
		{
			leftPaddle.y = GetScreenHeight() - 50;
		}

		if (rightPaddle.y > GetScreenHeight() - 50)
		{
			rightPaddle.y = GetScreenHeight() - 50;
		}

		// win screen
		if (ball.x < 0)
		{
			winnerText = "Right Player wins!"; 
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
		}

		// restart game 
		if (winnerText == "Left Player Wins!" && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2; 
			ball.y = GetScreenHeight() / 2; 
			ball.speedX = -350; 
			ball.speedY = 1; 
			winnerText = nullptr;
		}
		else if (winnerText == "Right Player wins!" && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 350;
			ball.speedY = 1;
			winnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw(); 
		leftPaddle.Draw();
		rightPaddle.Draw(); 
		
		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60); 
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawFPS(10, 10); 
		EndDrawing();
	}

	CloseWindow(); 

	return 0; 
}