// 14:46
#include "olcConsoleGameEngine.h"
using namespace std;

struct vec3d 
{
    float x, y, z;      // holds coordinates in 3d space
};

struct triangle 
{
    vec3d p[3];
};

struct mesh 
{
    vector<triangle> tris;
};

class olcEngine3D : public olcConsoleGameEngine 
{
public:
    olcEngine3D() 
    {
        m_sAppName = L"3D Demo";
    }

private:
    mesh meshCube;

public:
    bool OnUserCreate() override
    {
        meshCube.tris = {
            // south                                                                    CONTINUE HERE
            { 0.0f, 0.0f, 0.1f }
        };
        
        return true;            // temporary value
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        return true;            // temporary value
    }
};

int main()
{
    olcEngine3D demo;

    if (demo.ConstructConsole(256, 240, 4, 4)) {
        demo.Start();
    }

    return 0;
}