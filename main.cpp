#include<bits/stdc++.h>
#include "raylib.h"

using namespace std;

const int screenWidth = 800;
const int screenHeight = 450;
struct TypeColors{
    Color type_int = GREEN, type_char = RED, type_float = ORANGE, type_string = BLUE, type_double = PURPLE, type_vector = YELLOW;
};
class Variable{
    const string type, name;
    string value;
    const bool isConst, hasValue, isGlobal;
    int rowNo;
    TypeColors colors;
    public:
    Variable(string type, string name, bool isConst, bool hasValue, bool isGlobal, int rowNo):type(type), name(name), isConst(isConst), hasValue(hasValue), isGlobal(isGlobal), rowNo(rowNo){}
    Variable(string type, string name, string value, bool isConst, bool hasValue, bool isGlobal, int rowNo):type(type), name(name), value(value), isConst(isConst), hasValue(hasValue), isGlobal(isGlobal), rowNo(rowNo){}
    void setValue(const string val){value = val;}

    void draw(){
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
int main() {

    InitWindow(screenWidth, screenHeight, "Raylib Example - Basic Window");

    SetTargetFPS(60);

    while (!WindowShouldClose()) { 
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}