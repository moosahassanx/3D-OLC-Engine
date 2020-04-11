// 33.53
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

struct mat4x4 
{
    float m[4][4] = { 0 };  // [row][column]
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
    mat4x4 matProj;

    void MultiplyMatrixVector(vec3d& i, vec3d& o, mat4x4& m) 
    {
        o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
        o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
        o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
        float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

        if (w != 0) 
        {
            o.x /= w, o.y /= w; o.z /= w;
        }
    }
public:
    bool OnUserCreate() override
    {
        meshCube.tris = {
            // south
            { 0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,       1.0f, 0.0f, 0.0f },

            // east
            { 1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,       1.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 0.0f, 1.0f },

            // north
            { 1.0f, 0.0f, 1.0f,     1.0f, 1.0f, 1.0f,       0.0f, 1.0f, 1.0f },
            { 1.0f, 0.0f, 1.0f,     0.0f, 1.0f, 1.0f,       0.0f, 0.0f, 1.0f },

            // west
            { 0.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 0.0f,       1.0f, 0.0f, 0.0f },

            // top
            { 0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 1.0f,       1.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 1.0f, 0.0f },

            // bottom
            { 1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f,       0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 1.0f,     0.0f, 0.0f, 0.0f,       1.0f, 0.0f, 0.0f }
        };

        // projection matrix
        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fFov = 90.0f;
        float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
        float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.1415926f);
        

        matProj.m[0][0] = fAspectRatio * fFovRad;
        matProj.m[1][1] = fFovRad;
        matProj.m[2][2] = fFar / (fFar - fNear);
        matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        matProj.m[2][3] = 1.0f;
        matProj.m[3][3] = 0.0f;

        return true;            // temporary value
    }

    bool OnUserUpdate(float fElapsedTime) override
    {   
        Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
        
        // draw triangles
        for (auto tri : meshCube.tris) {
            triangle triProjected;
            MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);
            MultiplyMatrixVector(tri.p[0], triProjected.p[0], matProj);

            DrawTriangle(triProjected.p[0].x, triProjected.p[0].y, 
                triProjected.p[1].x, triProjected.p[1].y,
                triProjected.p[2].x, triProjected.p[2].y,
                PIXEL_SOLID, FG_WHITE
                );
        }

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