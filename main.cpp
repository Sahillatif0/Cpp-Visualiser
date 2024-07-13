#include <bits/stdc++.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;
void doNothing(){}

float GetScaleFactor(){
    float scaleFactorX = GetScreenWidth() / screenWidth;
    float scaleFactorY = GetScreenHeight() / screenHeight;
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
        int circle_no = 0;
        float scaleFactor = GetScaleFactor();
        float width = 100.0f*scaleFactor, height = 40.0f*scaleFactor, initialPosx = 15.0f*scaleFactor, initialPosy = 30.0f*scaleFactor;
        DrawRectangleRounded({initialPosx,initialPosy+((rowNo-1)*(height + height/10)),width, height},0.2,0,GRAY);
        DrawText(name.c_str(), initialPosx + width/2, (initialPosy+height/2)+((rowNo-1)*height), 20, WHITE);
        DrawCircle(width+5-(12.0f*scaleFactor*circle_no),initialPosy+(10.0f*scaleFactor)+height/10+((rowNo-1)*height),5*scaleFactor,colors[type]), circle_no++;
        if(isConst)DrawCircle(width+5-(12.0f*scaleFactor*circle_no),initialPosy+(10.0f*scaleFactor)+height/10+((rowNo-1)*height),5*scaleFactor,RED), circle_no++;
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
        float scaleFactor = GetScaleFactor();
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