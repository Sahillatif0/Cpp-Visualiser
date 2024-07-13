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
    public:
    Color Red = Color({173, 42, 42, 255}), Green = Color({27, 125, 25,255}), Yellow = Color({173, 165, 42, 255});
    map<string, Color> properties;
    TypeColors(){
        properties["type_int"] = Green;
        properties["type_char"] = Red;
        properties["type_float"] = ORANGE;
        properties["type_string"] = BLUE;
        properties["type_double"] = PURPLE;
        properties["type_vector"] = Yellow;
    }
    Color& operator[](const std::string& key) {
        return properties[key];
    }
};
class Variable{
    const string type, name;
    string value;
    const bool isConst, isGlobal;
    bool hasValue;
    int rowNo;
    TypeColors colors;
    public:
    Variable(string type, string name, bool isConst, bool isGlobal, int rowNo) : type(type), name(name), isConst(isConst), hasValue(false), isGlobal(isGlobal), rowNo(rowNo) {}
    Variable(string type, string name, string value, bool isConst, bool isGlobal, int rowNo) : type(type), name(name), value(value), isConst(isConst), hasValue(true), isGlobal(isGlobal), rowNo(rowNo) {}
    void setValue(const string val) { value = val; if(!hasValue)hasValue=true;}
    void draw(){
        float scaleFactor = GetScaleFactor();
        int circle_no = 0, fontSize = int (float(20)*(scaleFactor));
        string text = (hasValue)?(name + " = "+value):name;
        float width = (100.0f +  MeasureText(text.c_str(),fontSize) - MeasureText("abcdef", fontSize))*scaleFactor, height = 60.0f*scaleFactor, initialPosx = 15.0f*scaleFactor, initialPosy = 30.0f*scaleFactor;
        DrawRectangleRounded({initialPosx,initialPosy+((rowNo-1)*(height + height/5))-10,width, height},0.2,0,colors[type]);
        DrawRectangleRounded({initialPosx,initialPosy+((rowNo-1)*(height + height/5)),width, height},0.2,0,Color({40, 40, 50,255}));
        DrawText(text.c_str(), initialPosx + width/2 - MeasureText(text.c_str(), fontSize)/2, (initialPosy+height/2)+((rowNo-1)*(height + height/5))-3, fontSize, WHITE);
        DrawCircle(width+5-(12.0f*scaleFactor*circle_no),initialPosy+(10.0f*scaleFactor)+((rowNo-1)*(height + height/5)),5*scaleFactor,colors[type]), circle_no++;
        if(isConst)DrawCircle(width+5-(12.0f*scaleFactor*circle_no),initialPosy+(10.0f*scaleFactor)+((rowNo-1)*(height + height/5)),5*scaleFactor,colors.Red), circle_no++;
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
        ClearBackground(Color({30,30,36,255}));
        Variable v1("type_int", "i", "12", true,false, 1);
        Variable v2("type_char", "i", "12", true,false, 2);
        Variable v3("type_vector", "i", "12", false,false, 3);
        Variable v4("type_string", "bro teach me this", "bro", true,false, 4);
        Variable v5("type_float", "j", "1332.234", false,false, 5);
        Variable v6("type_double", "k", "1332.5434566", false,false, 6);
        v1.draw();
        v2.draw();
        v3.draw();
        v4.draw();
        v5.draw();
        v6.draw();
        DrawText("Congrats! You created your first window!", 190 * scaleFactor, 200 * scaleFactor, 20 * scaleFactor, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}