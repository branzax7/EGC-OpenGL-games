#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        glm::vec3 CrossProduct(glm::vec3 a, glm::vec3 b);
        glm::vec3 PointsToVec3(glm::vec3 a, glm::vec3 b);

     protected:
        implemented::Camera2 *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        int viewFlag;
        float zoom;
        float blue, red;
        float treePos;
        float leavesSize, trunkSize;
        float carSize;
        //int mata;
        float grassLevel, roadLevel;
        float carX, carY, carZ;
        float roadScale;
        float carView;
        float angle;
        //vector<glm::vec3> mata;

        // TODO(student): If you need any other class variables, define them here.

    };
}   // namespace m1
