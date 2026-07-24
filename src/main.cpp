#include <iostream>
#include <cassert>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#ifndef NDEBUG
const char *info = "Debug build\n";
#else
const char *infor = "Release build\n";
#endif

void UpdateDrawFrame(void)
{

    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText(info, 0, 0, 20, LIGHTGRAY);

    EndDrawing();
}

int main()
{
    InitWindow(800, 450, "zGame");
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);

    // Traditional desktop loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
}