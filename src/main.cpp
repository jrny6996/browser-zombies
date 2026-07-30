#include <iostream>
#include <cassert>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "engine/scenes/ThreeDScene.hpp"
#include "engine/camera/helpers.hpp"
#include "engine/types/dimensions.hpp"
#include "engine/helpers/debug_menu.hpp"
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

Camera3D camera{0};
Dimensions WINDOW_DIMENSIONS{800, 450};
DebugMenu debugMenu(camera, WINDOW_DIMENSIONS);
int camera_mode = CAMERA_FIRST_PERSON;

void UpdateDrawFrame(void)
{

    BeginDrawing();

    ClearBackground(RAYWHITE);
    UpdateCamera(&camera, camera_mode);
    BeginMode3D(camera);
    DrawGrid(100, 1.0f);
    EndMode3D();

    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GRAY);
    debugMenu.draw_menu(&camera_mode);
    EndDrawing();
}

int main()
{
    InitWindow(WINDOW_DIMENSIONS.width, WINDOW_DIMENSIONS.height, "zGame");
    setup_camera(&camera);
    DisableCursor();
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
    SetTargetFPS(120);

    // Traditional desktop loop
    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
#endif
}