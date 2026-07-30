#include "../engine/scenes/ThreeDScene.hpp"
#include <vector>

class Default3dScene : public ThreeDScene
{
private:
    std::vector<int> _runtime_models;

public:
    Default3dScene()
    {
    }
};
