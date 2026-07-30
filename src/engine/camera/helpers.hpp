#pragma once
#include <raylib.h>

void setup_camera(Camera *camera)
{
    camera->position = (Vector3){50.0f, 50.0f, 50.0f};
    camera->target = (Vector3){0.0f, 12.0f, 0.0f};
    camera->up = (Vector3){0.0f, 1.0f, 0.0f};
    camera->fovy = 45.0f;
    camera->projection = CAMERA_PERSPECTIVE;
}