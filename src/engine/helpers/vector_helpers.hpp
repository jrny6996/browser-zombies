#pragma
#include <string>
#include <raylib.h>
#include <format>

std::string vec_to_str(const Vector3 &vec, std::string seperator = "\n")
{
    return std::format("x:{:.2f}, y:{:.2f}, z:{:.2f}", vec.x, vec.y, vec.z);
}