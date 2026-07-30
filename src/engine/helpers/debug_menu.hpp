#pragma once

#include <raylib.h>
#include <string>
#include <iostream>
#include "../types/dimensions.hpp"
#include "./vector_helpers.hpp"
class DebugMenu
{
public:
    Camera &camera;
    Dimensions &WINDOW_DIMNESIONS;
#ifndef NDEBUG
    std::string info = "Debug build\n";
#else
    std::string info = "Release build\n";
#endif
    DebugMenu(Camera &camera, Dimensions &WINDOW_DIMNESIONS) : camera(camera), WINDOW_DIMNESIONS(WINDOW_DIMNESIONS)
    {
    }

    void draw_menu(int *cam_mode)
    {
        DrawText(info.c_str(), (this->WINDOW_DIMNESIONS.width - 10 - MeasureText(info.c_str(), 20)), 10, 20, GRAY);

        auto cam_pos{vec_to_str(camera.position)};
        auto cam_target{vec_to_str(camera.target)};
        DrawText(cam_pos.c_str(), (this->WINDOW_DIMNESIONS.width - 10 - MeasureText(cam_pos.c_str(), 12)), 30, 12, GRAY);
        DrawText(cam_target.c_str(), (this->WINDOW_DIMNESIONS.width - 10 - MeasureText(cam_target.c_str(), 12)), 30 + 12, 12, GRAY);
    }
    void log_menu(int *cam_mode)
    {
        std::cout << "position" << vec_to_str(camera.position) << std::endl;
        std::cout << "target" << vec_to_str(camera.target) << std::endl;
    }
};