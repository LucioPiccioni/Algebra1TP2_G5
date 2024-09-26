#include <iostream>
#include "raylib.h"

using namespace std;

void SetCamera3D(Camera3D& camera);
void drawCamera(Camera3D camera);
void drawNValueMenu(int& userInput);

void GenerateVectorA(Vector3& vectorA, float& magnitudeA);
void GenerateVectorB(Vector3 vectorA, Vector3& vectorB, float& magnitudeB);
void GenerateVectorC(Vector3 vectorA, Vector3 vectorB, Vector3& vectorC);

void main()
{
    srand(time(NULL));
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    const int screenWidth = 800;
    const int screenHeight = 450;

    int userInput = 0;
    bool isNValueSet = false;

    float minRandValue = 1.0f;
    float maxRandValue = 10.0f;

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
 
    // Define the camera to look into our 3d world
    

    InitWindow(screenWidth, screenHeight, "Algebra_TP02_Grupo5");
    DisableCursor();

    GenerateVectorA(vectorA,magnitudeA);
    GenerateVectorB(vectorA, vectorB, magnitudeB);
    GenerateVectorC(vectorA, vectorB, vectorC);


    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FREE);
       
        if (IsKeyPressed('Z')) camera.target ={ 0.0f, 0.0f, 0.0f };

        BeginDrawing();

        ClearBackground(WHITE);
        drawCamera(camera);


        if (isNValueSet)
        {
            drawNValueMenu(userInput);
            userInput = GetCharPressed() - 48;

            if (userInput > 1 || userInput < 9)
            {

                isNValueSet = true;
            }

        }
        else
        {

        }


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
void drawCamera(Camera3D camera)
{
    BeginMode3D(camera);

    //DrawGrid(10, 1.0f);

    EndMode3D();

    DrawFPS(10, 10);

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
    float minRandValue = 1.0f;
    float maxRandValue = 10.0f;

    //generar valores aletorios
    vectorA.x = GetRandomValue(minRandValue, maxRandValue);
    vectorA.y = GetRandomValue(minRandValue, maxRandValue);
    vectorA.z = GetRandomValue(minRandValue, maxRandValue);
   
    //magnitudeA = GetRandomValue(minRandValue, maxRandValue);
    float magnitude = sqrt(vectorA.x * vectorA.x + vectorA.y * vectorA.y + vectorA.z * vectorA.z);
    magnitudeA = magnitude;

    //normalizar el vector
    vectorA.x /= magnitudeA;
    vectorA.y /= magnitudeA;
    vectorA.z /= magnitudeA;

    // Escalamos el vector a la magnitud
    vectorA.x *= magnitudeA;
    vectorA.y *= magnitudeA;
    vectorA.z *= magnitudeA;
}
void GenerateVectorB(Vector3 vectorA, Vector3& vectorB, float& magnitudeB)
{
    //toma como referencia datos de A y se cambia el signo de uno para lograr que rote
    vectorB.x = vectorA.z;
    vectorB.z = -1 * vectorA.x;

    //magnitudeA = GetRandomValue(minRandValue, maxRandValue);
    float magnitude = sqrt(vectorB.x * vectorB.x + vectorB.y * vectorB.y + vectorB.z * vectorB.z);
    magnitudeB = magnitude;

    //normalizar el vector
    vectorB.x /= magnitudeB;
    vectorB.y /= magnitudeB;
    vectorB.z /= magnitudeB;

    // Escalamos el vector a la magnitud
    vectorB.x *= magnitudeB;
    vectorB.y *= magnitudeB;
    vectorB.z *= magnitudeB;
}
void GenerateVectorC(Vector3 vectorA, Vector3 vectorB, Vector3& vectorC)
{
    //hago producto cruz para sacar los valores del vectorC
    vectorC.x = ((vectorA.y * vectorB.z) - (vectorA.z * vectorB.y));
    vectorC.y = ((vectorA.x * vectorB.z) - (vectorA.z * vectorB.x));
    vectorC.z = ((vectorA.x * vectorB.y) - (vectorA.y * vectorB.x));
}