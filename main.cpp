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
bool IsPointInCircle(Vector2 point, Vector2 center, float radius){
    float dx = point.x - center.x;
    float dy = point.y - center.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

void DrawCircleRectIntersection(Rectangle rect, Vector2 circleCenter, float radius, Color clr){
    for (int y = (int)rect.y; y < (int)(rect.y + rect.height); y++)
        for (int x = (int)rect.x; x < (int)(rect.x + rect.width); x++){
            Vector2 point = { (float)x, (float)y };
            if (IsPointInCircle(point, circleCenter, radius))
                DrawPixel(x, y, clr); 
        }
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
    const string type, name, relatedFunction;
    string value;
    const bool isConst, isGlobal;
    bool hasValue;
    int rowNo, fontSize;
    TypeColors colors;
    Rectangle box;
    string text;
    public:
    Variable(string type, string name, bool isConst, bool isGlobal, int rowNo, string relatedFunc) : type(type), name(name), isConst(isConst), hasValue(false), isGlobal(isGlobal), rowNo(rowNo), relatedFunction(relatedFunc) {
        float scaleFactor = GetScaleFactor();
        fontSize = int (float(20)*(scaleFactor));
        text = (hasValue)?(name + " = "+value):name;
        box.width = (100.0f +  MeasureText(text.c_str(),fontSize) - MeasureText("abcdef", fontSize))*scaleFactor, box.height = 60.0f*scaleFactor, box.x = 15.0f*scaleFactor, box.y = 30.0f*scaleFactor+((rowNo-1)*(box.height + box.height/5));
    }
    Variable(string type, string name, string value, bool isConst, bool isGlobal, int rowNo, string relatedFunc) : type(type), name(name), value(value), isConst(isConst), hasValue(true), isGlobal(isGlobal), rowNo(rowNo), relatedFunction(relatedFunc) {
        float scaleFactor = GetScaleFactor();
        fontSize = int (float(20)*(scaleFactor));
        text = (hasValue)?(name + " = "+value):name;
        box.width = (100.0f +  MeasureText(text.c_str(),fontSize) - MeasureText("abcdef", fontSize))*scaleFactor, box.height = 60.0f*scaleFactor, box.x = 15.0f*scaleFactor, box.y = 30.0f*scaleFactor+((rowNo-1)*(box.height + box.height/5));
    }
    void setValue(const string val) { value = val; if(!hasValue)hasValue=true;}
    void draw(){
        float scaleFactor = GetScaleFactor();
        int circle_no = 0;        
        DrawRectangleRounded({box.x,box.y-10,box.width,box.height},0.2,0,colors[type]);
        DrawRectangleRounded(box,0.2,0,Color({40, 40, 50,255}));
        DrawText(text.c_str(), box.x + box.width/2 - MeasureText(text.c_str(), fontSize)/2, box.y+box.height/2-3, fontSize, WHITE);
        DrawCircle(box.width+5-(12.0f*scaleFactor*circle_no),box.y+(10.0f*scaleFactor),5*scaleFactor,colors[type]), circle_no++;
        if(isConst)DrawCircle(box.width+5-(12.0f*scaleFactor*circle_no),box.y+(10.0f*scaleFactor),5*scaleFactor,colors.Red), circle_no++;
    }
    int propertyTextWidth(){
        float scaleFactor = GetScaleFactor();
        int ffontSize = int (float(15)*(scaleFactor));
        int maxWidth = MeasureText(type.c_str(), ffontSize);
        maxWidth = max(maxWidth, MeasureText(name.c_str(), ffontSize));
        maxWidth = max(maxWidth, MeasureText(value.c_str(), ffontSize));
        maxWidth = max(maxWidth, MeasureText(relatedFunction.c_str(), ffontSize));
        maxWidth = max(maxWidth, MeasureText(to_string(rowNo).c_str(), ffontSize));
        return maxWidth;
    }
    void hoverDraw(){
        Vector2 mousePos = GetMousePosition();
        if(CheckCollisionPointRec(mousePos, box)){
            float scaleFactor = GetScaleFactor();
            int ffontSize = int (float(15)*(scaleFactor));
            float width = 140*scaleFactor + (propertyTextWidth() - MeasureText("abcdef", ffontSize))*scaleFactor, height = 220*scaleFactor, ypos = mousePos.y - (((GetScreenHeight()-mousePos.y)<height)?height-(GetScreenHeight()-mousePos.y):0);
            string yes="Yes",no="No";
            // DrawRectangleRounded({mousePos.x+5, ypos,width,height},0.2,10,colors[type]);
            DrawRectangleRounded({mousePos.x, ypos,width,height},0.2,10,DARKGRAY);
            DrawCircleRectIntersection({mousePos.x, ypos+scaleFactor,width,height}, {mousePos.x+width/2, ypos+20},100*scaleFactor,colors[type]);
            DrawText(("Type: "+type).c_str(), mousePos.x+10, ypos+(10*scaleFactor), ffontSize, WHITE);
            DrawText(("Name: "+name).c_str(), mousePos.x+10, ypos+(30*scaleFactor), ffontSize, WHITE);
            DrawText(("Value: "+value).c_str(), mousePos.x+10, ypos+(50*scaleFactor), ffontSize, WHITE);
            DrawText(("In Function: "+relatedFunction).c_str(), mousePos.x+10, ypos+(70*scaleFactor), ffontSize, WHITE);
            DrawText(("Const: "+((isConst)?yes:no)).c_str(), mousePos.x+10, ypos+(90*scaleFactor), ffontSize, WHITE);
            DrawText(("Global: "+((isGlobal)?yes:no)).c_str(), mousePos.x+10, ypos+(110*scaleFactor), ffontSize, WHITE);
            DrawText(("Row No: "+to_string(rowNo)).c_str(), mousePos.x+10, ypos+(130*scaleFactor), ffontSize, WHITE);
        }
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
        Variable v1("type_int", "i", "12", true,false, 1, "main");
        Variable v2("type_char", "i", "12", true,false, 2, "foo");
        Variable v3("type_vector", "i", "12", false,false, 3, "sortAlgo");
        Variable v4("type_string", "bro teach me this", "bro", true,false, 4, "more");
        Variable v5("type_float", "j", "1332.234", false,false, 5, "main");
        Variable v6("type_double", "k", "1332.5434566", false,false, 6, "doNothing");
        v1.draw();
        v2.draw();
        v3.draw();
        v4.draw();
        v5.draw();
        v6.draw();
        v1.hoverDraw();
        v2.hoverDraw();
        v3.hoverDraw();
        v4.hoverDraw();
        v5.hoverDraw();
        v6.hoverDraw();
        DrawText("Congrats! You created your first window!", 190 * scaleFactor, 200 * scaleFactor, 20 * scaleFactor, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}