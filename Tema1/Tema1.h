#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        float addt, t = 0, sgn;
        glm::mat3 modelMatrix;
        glm::mat3 modelAux;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float wingSide;
        float triangleSide;
        float wingX, wingY;
        float headX, headY;
        float pasareR;
        float tX, tY;
        float rectX, rectY, l, L, rectY1, rectX1, rectY11, rectY12, rectX11, rectX12;
        float d1, d2;
        float rectY2, rectX2;
        float mouseY2;
        float timeElapsed, gameplay;
        float lives;
        float speed;
        float shot;
        int birdCounter, speedCounter;
        int poz;
        float vitezaCadere, vitezaEvadare;
        int bullets;
        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
