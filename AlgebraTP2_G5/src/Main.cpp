#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

void SetCamera3D(Camera3D& camera);
void drawCameraMenu(Camera3D camera);
void drawNValueMenu(int& userInput);

void GenerateVectorA(Vector3& vectorA, float& magnitudeA);
void GenerateVectorB(Vector3 vectorA, Vector3& vectorB, float magnitudeA, float& magnitudeB);
void GenerateVectorC(Vector3 vectorA, Vector3 vectorB, Vector3& vectorC, Vector3 startPos);
void SetVecMagnitude(Vector3& vector, float magnitude);
void NormaliceVector(Vector3& vector);
void GetMagnitude(Vector3 vector, float& newMagnitude);
void DrawPiramid(Vector3 startpos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC, float userInput, float& perimeter, float& area, float& volume);

void main()
{
	srand(time(NULL));
	SetTargetFPS(60);     
	const int screenWidth = 800;
	const int screenHeight = 450;

	int userInput = 0;
	bool isNValueSet = false;

	float perimeter = 0.0f;
	float area = 0.0f;
	float volume = 0.0f;

	Camera3D camera;

	Vector3 startPos = { 0.0f, 0.0f, 0.0f };
	Vector3 vectorA;
	Vector3 vectorB;
	Vector3 vectorC;
	float magnitudeA = 1.0f;
	float magnitudeB = 1.0f;
	float magnitudeC = 1.0f;

	InitWindow(screenWidth, screenHeight, "Algebra_TP02_Grupo5");

	SetCamera3D(camera);
	DisableCursor();

	GenerateVectorA(vectorA, magnitudeA);
	GenerateVectorB(vectorA, vectorB, magnitudeA, magnitudeB);
	GenerateVectorC(vectorA, vectorB, vectorC, startPos);


	while (!WindowShouldClose())
	{
		int auxInput = 0;

		UpdateCamera(&camera, CAMERA_FREE);

		BeginDrawing();
		BeginMode3D(camera);

		ClearBackground(WHITE);

		DrawPiramid(startPos, vectorA, vectorB, vectorC, magnitudeC, userInput, perimeter, area, volume);
		/*cout << "C magnitude: " << vectorC.x << endl;
		cout << "C magnitude: " << vectorC.y << endl;
		cout << "C magnitude: " << vectorC.z << endl;*/

		cout << "user input" << userInput << endl;

		if (!isNValueSet)
		{
			drawNValueMenu(userInput);
			auxInput = GetCharPressed() - 48;

			if (auxInput > 1 && auxInput < 10)
			{
				SetVecMagnitude(vectorC, (magnitudeA / auxInput));
				GetMagnitude(vectorC, magnitudeC);

				userInput = (float)auxInput;

				isNValueSet = true;
			}

		}
		else
		{
			if (IsKeyPressed('Z')) camera.target = { 0.0f, 0.0f, 0.0f };
		}

		drawCameraMenu(camera);
		EndMode3D();

		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();

}

void SetCamera3D(Camera3D& camera)
{
	camera = { 0 };
	camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
}
void drawCameraMenu(Camera3D camera)
{
	DrawGrid(10, 1.0f);

	DrawText("Free camera default controls:", 10, 35, 10, BLACK);
	DrawText("- Mouse Wheel to Zoom in-out", 20, 55, 10, DARKGRAY);
	DrawText("- Mouse Wheel Pressed to Pan", 20, 75, 10, DARKGRAY);
	DrawText("- Z to zoom to (0, 0, 0)", 20, 95, 10, DARKGRAY);
}
void drawNValueMenu(int& userInput)
{
	DrawText("---------MENU---------", 640, 35, 10, BLACK);
	DrawText("Chosse a value between 2 and 8.", 620, 55, 10, DARKGRAY);
	DrawText("Your value will change the ", 630, 75, 10, DARKGRAY);
	DrawText("amount of floor can generate", 620, 95, 10, DARKGRAY);
}

void GenerateVectorA(Vector3& vectorA, float& magnitudeA)
{
	float minRandValue = 2.0f;
	float maxRandValue = 8.0f;

	//generar valores aletorios
	vectorA.x = (float)GetRandomValue(minRandValue, maxRandValue);
	vectorA.y = (float)GetRandomValue(minRandValue, maxRandValue);
	vectorA.z = (float)GetRandomValue(minRandValue, maxRandValue);

	GetMagnitude(vectorA, magnitudeA);
}
void GenerateVectorB(Vector3 vectorA, Vector3& vectorB, float magnitudeA, float& magnitudeB)
{
	//toma como referencia datos de A y se cambia el signo de uno para lograr que rote
	vectorB.x = vectorA.z;
	vectorB.y = 0.0f;
	vectorB.z = -1 * vectorA.x;

	SetVecMagnitude(vectorB, magnitudeA);
	GetMagnitude(vectorB, magnitudeB);
}
void GenerateVectorC(Vector3 vectorA, Vector3 vectorB, Vector3& vectorC, Vector3 startPos)
{
	//hago producto cruz para sacar los valores del vectorC
	vectorC.x = ((vectorA.y * vectorB.z) - (vectorA.z * vectorB.y)) + startPos.x;
	vectorC.y = ((vectorA.x * vectorB.z) - (vectorA.z * vectorB.x)) + startPos.y;
	vectorC.z = ((vectorA.x * vectorB.y) - (vectorA.y * vectorB.x)) + startPos.z;
}

void SetVecMagnitude(Vector3& vector, float magnitude)
{
	NormaliceVector(vector);

	// Escalamos el vector a la magnitud
	vector.x *= magnitude;
	vector.y *= magnitude;
	vector.z *= magnitude;
}
void NormaliceVector(Vector3& vector)
{
	float auxMagnitude;

	GetMagnitude(vector, auxMagnitude);

	vector.x /= auxMagnitude;
	vector.y /= auxMagnitude;
	vector.z /= auxMagnitude;
}
void GetMagnitude(Vector3 vector, float& newMagnitude)
{
	newMagnitude = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

void DrawPiramid(Vector3 startPos, Vector3 vectorA, Vector3 vectorB, Vector3 vectorC, float magnitudeC, float userInput, float& perimeter, float& area, float& volume)
{
	Vector3 transformVecX; //desplazamiento en x por piso
	transformVecX.x = vectorA.x / userInput;
	transformVecX.y = vectorA.y / userInput;
	transformVecX.z = vectorA.z / userInput;

	Vector3 transformVecY; //desplazamiento en y por piso
	transformVecY.x = vectorB.x / userInput;
	transformVecY.y = vectorB.y / userInput;
	transformVecY.z = vectorB.z / userInput;

	//reduccion diagonal desde el vertice por cada piso
	Vector3 reductStartPos = Vector3Add(transformVecX, transformVecY);
	Vector3 reductA = Vector3Add(Vector3Scale(transformVecX, -1.0), transformVecY);
	Vector3 reductB = Vector3Subtract(transformVecX, transformVecY);
	Vector3 reductC = Vector3Subtract(Vector3Scale(transformVecX, -1.0), transformVecY);

	//almacenamiento de los valores originales
	Vector3 auxStartPos = startPos;
	Vector3 auxVecA = vectorA;
	Vector3 auxVecB = vectorB;
	Vector3 auxVecC = Vector3Add(vectorA, vectorB);

	DrawLine3D(startPos, vectorA, RED);
	DrawLine3D(startPos, vectorB, GREEN);
	DrawLine3D(startPos, vectorC, BLUE);

	float floorAmount = userInput / 2;
	float actualMagnitude;

	actualMagnitude = Vector3Distance(auxStartPos, Vector3Scale(reductStartPos, 0)), Vector3Add(auxVecA, Vector3Scale(reductA, 0));

	for (int i = 0; i < floorAmount; i++)
	{
		DrawLine3D(Vector3Add(auxStartPos, (Vector3Scale(reductStartPos, i))), Vector3Add(Vector3Add(auxStartPos, (Vector3Scale(reductStartPos, i))), vectorC), BLUE);
		DrawLine3D(Vector3Add(auxVecA, (Vector3Scale(reductA, i))), Vector3Add(Vector3Add(auxVecA, (Vector3Scale(reductA, i))), vectorC), BLUE);
		DrawLine3D(Vector3Add(auxVecB, (Vector3Scale(reductB, i))), Vector3Add(Vector3Add(auxVecB, (Vector3Scale(reductB, i))), vectorC), BLUE);
		DrawLine3D(Vector3Add(auxVecC, (Vector3Scale(reductC, i))), Vector3Add(Vector3Add(auxVecC, (Vector3Scale(reductC, i))), vectorC), BLUE);

		DrawLine3D(Vector3Add(auxStartPos, Vector3Scale(reductStartPos, i)), Vector3Add(auxVecA, Vector3Scale(reductA, i)), BLACK);
		actualMagnitude = Vector3Distance(auxStartPos, Vector3Scale(reductStartPos, i)), Vector3Add(auxVecA, Vector3Scale(reductA, i));

		DrawLine3D(Vector3Add(auxStartPos, Vector3Scale(reductStartPos, i)), Vector3Add(auxVecB, Vector3Scale(reductB, i)), BLACK);
		DrawLine3D(Vector3Add(auxVecC, Vector3Scale(reductC, i)), Vector3Add(auxVecA, Vector3Scale(reductA, i)), BLACK);
		DrawLine3D(Vector3Add(auxVecC, Vector3Scale(reductC, i)), Vector3Add(auxVecB, Vector3Scale(reductB, i)), BLACK);

		auxStartPos = Vector3Add(auxStartPos, vectorC);
		auxVecA = Vector3Add(auxVecA, vectorC);
		auxVecB = Vector3Add(auxVecB, vectorC);
		auxVecC = Vector3Add(auxVecC, vectorC);
		
		DrawLine3D(Vector3Add(auxStartPos, Vector3Scale(reductStartPos, i)), Vector3Add(auxVecA, Vector3Scale(reductA, i)), BLACK);
		DrawLine3D(Vector3Add(auxStartPos, Vector3Scale(reductStartPos, i)), Vector3Add(auxVecB, Vector3Scale(reductB, i)), BLACK);
		DrawLine3D(Vector3Add(auxVecC, Vector3Scale(reductC, i)), Vector3Add(auxVecA, Vector3Scale(reductA, i)), BLACK);
		DrawLine3D(Vector3Add(auxVecC, Vector3Scale(reductC, i)), Vector3Add(auxVecB, Vector3Scale(reductB, i)), BLACK);
	}
}