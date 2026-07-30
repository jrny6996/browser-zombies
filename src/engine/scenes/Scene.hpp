#pragma once

#include "raylib.h"

class Scene
{
private:
    /* data */
public:
    virtual Scene *listen() const = 0;
    virtual void update(Scene &scene, Camera cam) = 0;

    virtual ~Scene() = default;
};
