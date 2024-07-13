#include <bits/stdc++.h>
#include "raylib.h"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;
void doNothing(){}

float GetScaleFactor(int currentWidth, int currentHeight)
{
    float scaleFactorX = (float)currentWidth / screenWidth;
    float scaleFactorY = (float)currentHeight / screenHeight;
    return (scaleFactorX < scaleFactorY) ? scaleFactorX : scaleFactorY;
}

class TypeColors{
    map<string, Color> properties;
    public:
    TypeColors(){
        properties["type_int"] = GREEN;
        properties["type_char"] = RED;
        properties["type_float"] = ORANGE;
        properties["type_string"] = BLUE;
        properties["type_double"] = PURPLE;
        properties["type_vector"] = YELLOW;
    }
    Color& operator[](const std::string& key) {
        return properties[key];
    }
};
class Variable{
    const string type, name;
    string value;
    const bool isConst, hasValue, isGlobal;
    int rowNo;
    TypeColors colors;
    public:
    Variable(string type, string name, bool isConst, bool hasValue, bool isGlobal, int rowNo) : type(type), name(name), isConst(isConst), hasValue(hasValue), isGlobal(isGlobal), rowNo(rowNo) {}
    Variable(string type, string name, string value, bool isConst, bool hasValue, bool isGlobal, int rowNo) : type(type), name(name), value(value), isConst(isConst), hasValue(hasValue), isGlobal(isGlobal), rowNo(rowNo) {}
    void setValue(const string val) { value = val; }
    void draw(){
        float width = 100.0f, height = 100.0f;
        DrawRectangleRounded({15.0f,40.0f+((rowNo-1)*(height)),width, height},0.2,0,GRAY);
        DrawText(name.c_str(), 15.0f + width/2, (40.0f+height/2)+((rowNo-1)*height), 20, WHITE);
        DrawCircle(width-10.0f,40.0f+10.0f+((rowNo-1)*height),5,colors[type]);
        isConst?DrawCircle(width+2.0f,40.0f+10.0f+((rowNo-1)*height),5,RED):doNothing();
    }
};
class Function{
};

class Loop{
};

class Class{
};

class Structure{
};

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "Raylib Example - Basic Window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        float scaleFactor = GetScaleFactor(currentWidth, currentHeight);

        BeginDrawing();
        ClearBackground(BLACK);
        Variable v1("type_int", "i", "12", true,false, 1);
        Variable v2("type_char", "i", "12", true,false, 2);
        v1.draw();
        v2.draw();
        DrawText("Congrats! You created your first window!", 190 * scaleFactor, 200 * scaleFactor, 20 * scaleFactor, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}