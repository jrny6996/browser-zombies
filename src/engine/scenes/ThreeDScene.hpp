#pragma once
#include "Scene.hpp"
#include "raylib.h"

class ThreeDScene : public Scene
{
private:
    /* data */
public:
    ThreeDScene();
    Scene &listen()
    {
        return *this;
    }
    void update(Scene &Scene, Camera cam)
    {
    }
};
