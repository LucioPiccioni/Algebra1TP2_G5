#include <iostream>
#include "raylib.h"
#include "raymath.h"

using namespace std;

void SetCamera(Camera& camera, Vector3 startPos);
void ShowMenu(float magnitudeA,float perimeter, float area, float volume);
void CameraHandler(Camera3D& camera, int& cameraMode);
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

	

	Vector3 startPos = { 0.0f, 0.0f, 0.0f };
	Vector3 vectorA;
	Vector3 vectorB;
	Vector3 vectorC;
	float magnitudeA = 1.0f;
	float magnitudeB = 1.0f;
	float magnitudeC = 1.0f;

	InitWindow(screenWidth, screenHeight, "Algebra_TP02_Grupo5");

	Camera camera = { 0 };
	SetCamera(camera, startPos);
	int cameraMode = CAMERA_FIRST_PERSON;

	DisableCursor();

	GenerateVectorA(vectorA, magnitudeA);
	GenerateVectorB(vectorA, vectorB, magnitudeA, magnitudeB);
	GenerateVectorC(vectorA, vectorB, vectorC, startPos);


	while (!WindowShouldClose())
	{
		int auxInput = 0;

		float perimeter{};
		float area{};
		float volume{};

		UpdateCamera(&camera, CAMERA_FREE);

		CameraHandler(camera, cameraMode);

		BeginDrawing();
		ClearBackground(WHITE);


		BeginMode3D(camera);

		DrawPiramid(startPos, vectorA, vectorB, vectorC, magnitudeC, userInput, perimeter, area, volume);
		
		EndMode3D();

		ShowMenu(magnitudeA, perimeter, area, volume);
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

		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();

}

void SetCamera(Camera& camera, Vector3 startPos)
{
	camera.position = { 0.0f, 2.0f, 4.0f };    // Camera position
	camera.target = { 0.0f, 2.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 100.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

	camera.position = startPos;

	camera.position.x += 2.0f;
	camera.position.y += 2.0f;
	camera.position.z += 2.0f;

	camera.target = startPos;
}
void ShowMenu(float magnitudeA, float perimeter, float area, float volume)
{
	Vector2 magnitudeTextPos = { 10, 30 };
	Vector2 vectorATextPos = { 10, 50 };
	Vector2 vectorBTextPos = { 10, 70 };
	Vector2 vectorCTextPos = { 10, 90 };


	DrawText(TextFormat("Vector A and B magnitude: %.2f", magnitudeA), magnitudeTextPos.x, magnitudeTextPos.y, 10, BLACK);
	DrawText("Vector A: RED", vectorATextPos.x, vectorATextPos.y, 10, DARKGRAY);
	DrawText("Vector B: GREEN", vectorBTextPos.x, vectorBTextPos.y, 10, DARKGRAY);
	DrawText("Vector C: BLUE", vectorCTextPos.x, vectorCTextPos.y, 10, DARKGRAY);

	DrawText("---------VALUES---------", 10, 110, 10, BLACK);
	DrawText(TextFormat("Perimeter: %.2f", perimeter), 10, 130, 10, DARKGRAY);
	DrawText(TextFormat("Area: %.2f", area), 10, 150, 10, DARKGRAY);
	DrawText(TextFormat("Volume: %.2f", volume), 10, 170, 10, DARKGRAY);
}
void CameraHandler(Camera3D& camera, int& cameraMode)
{
	if (IsKeyPressed(KEY_F))
	{
		cameraMode = CAMERA_FREE;
		camera.up = { 0.0f, 1.0f, 0.0f };
	}

	if (IsKeyPressed(KEY_G))
	{
		cameraMode = CAMERA_FIRST_PERSON;
		camera.up = { 0.0f, 1.0f, 0.0f };
	}

	if (IsKeyPressed(KEY_H))
	{
		cameraMode = CAMERA_THIRD_PERSON;
		camera.up = { 0.0f, 1.0f, 0.0f };
	}

	if (IsKeyPressed(KEY_J))
	{
		cameraMode = CAMERA_ORBITAL;
		camera.up = { 0.0f, 1.0f, 0.0f };
	}

	if (IsKeyPressed(KEY_P))
	{
		if (camera.projection == CAMERA_PERSPECTIVE)
		{
			cameraMode = CAMERA_THIRD_PERSON;
			camera.position = { 0.0f, 2.0f, -100.0f };
			camera.target = { 0.0f, 2.0f, 0.0f };
			camera.up = { 0.0f, 1.0f, 0.0f };
			camera.projection = CAMERA_ORTHOGRAPHIC;
			camera.fovy = 20.0f;
		}
		else if (camera.projection == CAMERA_ORTHOGRAPHIC)
		{
			cameraMode = CAMERA_THIRD_PERSON;
			camera.position = { 0.0f, 2.0f, 10.0f };
			camera.target = { 0.0f, 2.0f, 0.0f };
			camera.up = { 0.0f, 1.0f, 0.0f };
			camera.projection = CAMERA_PERSPECTIVE;
			camera.fovy = 60.0f;
		}
	}

	UpdateCamera(&camera, cameraMode);
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

		perimeter += ((actualMagnitude * 8.0f) + (magnitudeC * 4.0f));

		Vector3 crossProduct = Vector3CrossProduct(vectorA, vectorB);
		float baseArea = Vector3Length(crossProduct); // Área del paralelogramo como base
		//area += baseArea;
		area += (actualMagnitude * 4.0f) * magnitudeC;
		volume += ((actualMagnitude * actualMagnitude) * magnitudeC);

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