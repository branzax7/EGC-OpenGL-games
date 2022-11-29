#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


vector<glm::vec3> roadData;
float trunkSize = 0.2;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;
    viewFlag = 0;
    zoom = 60;
    glm::vec3 roadColor = glm::vec3(0.14, 0.15, 0.14);
    glm::vec3 grassColor = glm::vec3(0, 1, 0);
    glm::vec3 trunkColor = glm::vec3(0.13, 0.12, 0.09);
    glm::vec3 leavesColor = glm::vec3(0.15, 0.27, 0.15);

    roadLevel = 0.009;
    grassLevel = 0.001;


    camera = new implemented::Camera2();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //! de bagat mai intai pct-ele itr0 lista => ca sa pot pune copacii!!! si apeleati din llista cu lista[n]

    roadData= {
        glm::vec3(4.61, roadLevel, -1.5), //R1
        glm::vec3(3.34, roadLevel, -1.6),  //Q1
        glm::vec3(2.46, roadLevel, -1.01), //P1
        glm::vec3(1.54, roadLevel, -0.42), //O1
        glm::vec3(0.57, roadLevel, -1.2), //N1
        glm::vec3(-0.69, roadLevel, -1.91), //M1
        glm::vec3(-2.21, roadLevel, -1.82), //L1
        glm::vec3(-3.62, roadLevel, -1.15), //K1
        glm::vec3(-4.13, roadLevel, -0.16), //J1
        glm::vec3(-3.91, roadLevel, 1), //I1
        glm::vec3(-2.77, roadLevel, 1.64), //H1
        glm::vec3(-1.65, roadLevel, 1.41), //G1
        glm::vec3(-0.61, roadLevel, 0.81), //F1
        glm::vec3(0.45, roadLevel, 1.43), //E1
        glm::vec3(1.46, roadLevel, 2.21), //D1
        glm::vec3(2.94, roadLevel, 2.42), //C1
        glm::vec3(4.43, roadLevel, 1.53), //B1
        glm::vec3(5.17, roadLevel, 0.23), //A1
        glm::vec3(4.7, roadLevel, 0.32), //A2
        glm::vec3(4.1, roadLevel, 1.34), //B2
        glm::vec3(2.72, roadLevel, 2), //C2
        glm::vec3(1.52, roadLevel, 1.82), //D2
        glm::vec3(0.66, roadLevel, 1.16), //E2
        glm::vec3(-0.42, roadLevel, 0.49), //F2
        glm::vec3(-1.82, roadLevel, 1.02), //G2
        glm::vec3(-2.86, roadLevel, 1.32), //H2
        glm::vec3(-3.73, roadLevel, 0.71), //I2
        glm::vec3(-3.83, roadLevel, -0.2), //J2
        glm::vec3(-3.36, roadLevel, -1), //K2
        glm::vec3(-2.06, roadLevel, -1.42), //L2
        glm::vec3(-0.67, roadLevel, -1.48), //M2
        glm::vec3(0.38, roadLevel, -0.87), //N2
        glm::vec3(1.32, roadLevel, -0.13), //O2
        glm::vec3(2.63, roadLevel, -0.65), //P2
        glm::vec3(3.53, roadLevel, -1.33), //Q2
        glm::vec3(4.56, roadLevel, -1.16) //R2
    };
    
    
    //mata.push_back(glm::vec3(4.56, 0, -1.16));
    {
        vector<VertexFormat> vertices = {};

        for (glm::vec3 x : roadData) {
            
            vertices.push_back(VertexFormat(x, roadColor));
        }
        /*vector<VertexFormat> vertices // patrat
        {
            VertexFormat(glm::vec3(4.61, 0, -1.5), roadColor), //R1 //---0---
            VertexFormat(glm::vec3(3.34, 0, -1.6), roadColor), //Q1
            VertexFormat(glm::vec3(2.46, 0, -1.01), roadColor), //P1
            VertexFormat(glm::vec3(1.54, 0, -0.42), roadColor), //O1
            VertexFormat(glm::vec3(0.57, 0, -1.2), roadColor), //N1
            VertexFormat(glm::vec3(-0.69, 0, -1.91), roadColor), //M1
            VertexFormat(glm::vec3(-2.21, 0, -1.82), roadColor), //L1
            VertexFormat(glm::vec3(-3.62, 0, -1.15), roadColor), //K1
            VertexFormat(glm::vec3(-4.13, 0, -0.16), roadColor), //J1
            VertexFormat(glm::vec3(-3.85, 0, 0.91), roadColor), //I1
            VertexFormat(glm::vec3(-2.77, 0, 1.64), roadColor), //H1
            VertexFormat(glm::vec3(-1.65, 0, 1.41), roadColor), //G1
            VertexFormat(glm::vec3(-0.61, 0, 0.81), roadColor), //F1
            VertexFormat(glm::vec3(0.45, 0, 1.43), roadColor), //E1
            VertexFormat(glm::vec3(1.46, 0, 2.21), roadColor), //D1
            VertexFormat(glm::vec3(2.94, 0, 2.42), roadColor), //C1
            VertexFormat(glm::vec3(4.43, 0, 1.53), roadColor), //B1
            VertexFormat(glm::vec3(5.17, 0, 0.23), roadColor), //A1 //---17---
            VertexFormat(glm::vec3(4.7, 0, 0.32), roadColor), //A2   //18
            VertexFormat(glm::vec3(4.1, 0, 1.34),roadColor), //B2
            VertexFormat(glm::vec3(2.72, 0, 2), roadColor), //C2
            VertexFormat(glm::vec3(1.52, 0, 1.82), roadColor), //D2
            VertexFormat(glm::vec3(0.66, 0, 1.16), roadColor), //E2
            VertexFormat(glm::vec3(-0.42, 0, 0.49), roadColor), //F2
            VertexFormat(glm::vec3(-1.82, 0, 1.02), roadColor), //G2
            VertexFormat(glm::vec3(-2.86, 0, 1.32), roadColor), //H2
            VertexFormat(glm::vec3(-3.67, 0, -0.62), roadColor), //I2
            VertexFormat(glm::vec3(-3.83, 0, -0.2), roadColor), //J2
            VertexFormat(glm::vec3(-3.36, 0, -1), roadColor), //K2
            VertexFormat(glm::vec3(-2.06, 0, -1.42), roadColor), //L2
            VertexFormat(glm::vec3(-0.67, 0, -1.48), roadColor), //M2
            VertexFormat(glm::vec3(0.38, 0, -0.87), roadColor), //N2
            VertexFormat(glm::vec3(1.32, 0, -0.13), roadColor), //O2
            VertexFormat(glm::vec3(2.63, 0, -0.65), roadColor), //P2
            VertexFormat(glm::vec3(3.53, 0, -1.33), roadColor), //Q2
            VertexFormat(glm::vec3(4.56, 0, -1.16), roadColor), //R2 //35
            
        };*/

        // (R2, R1, A1), (R2, A1, A2) R->A
        // (A2, A1, B1), (A2, B1, B2) A->B

        //0-17 R1-A1
        //18-35 A2-R2
        // i = 17; j = 18
        //A->B: (j, i, i-1), (j, i-1, j+1)

        vector<unsigned int> indices = {};
        int i = 17;
        int j = 18;
        for (int k = 0; k < 17; k++) {
            indices.push_back(j);
            indices.push_back(i);
            indices.push_back(i-1);

            indices.push_back(j);
            indices.push_back(i-1);
            indices.push_back(j+1);

            i--;
            j++;
        }
        //R->A
        indices.push_back(35); //R2
        indices.push_back(0); //R1
        indices.push_back(17); //A1

        indices.push_back(35); //R2
        indices.push_back(17); //A1
        indices.push_back(18); //A2

        Mesh* pista = new Mesh("pista");
        pista->InitFromData(vertices, indices);
        AddMeshToList(pista);

    }

    {
        vector<VertexFormat> vertices2 // patrat
        {
            VertexFormat(glm::vec3(-1, grassLevel, -1), grassColor), //R1 //---0---
            VertexFormat(glm::vec3(-1,  grassLevel, 1), grassColor), //R1 //---0---
            VertexFormat(glm::vec3(1,  grassLevel, 1), grassColor), //R1 //---0---
            VertexFormat(glm::vec3(1,  grassLevel, -1), grassColor), //R1 //---0
            //glm::vec3(0, 1, 0)
            //glm::vec3(0.14, 0.15, 0.14)
        };

        vector<unsigned int> indices2 = {0, 1, 2, 0, 2, 3};

        Mesh* grass = new Mesh("iarba");
        grass->InitFromData(vertices2, indices2);
        AddMeshToList(grass);

    }

    {
        vector<VertexFormat> vertices3
        {
            //VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),// fara normala acm
            VertexFormat(glm::vec3(0, 0,  trunkSize), trunkColor), //0
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(trunkSize, 0, trunkSize), trunkColor), //1
            VertexFormat(glm::vec3(0, trunkSize,  trunkSize), trunkColor), //2
            VertexFormat(glm::vec3(trunkSize, trunkSize, trunkSize), trunkColor), //3
            VertexFormat(glm::vec3(0, 0,  0), trunkColor), //4
            VertexFormat(glm::vec3(trunkSize, 0,  0), trunkColor), // 5
            VertexFormat(glm::vec3(0, trunkSize,  0), trunkColor), //6
            VertexFormat(glm::vec3(trunkSize, trunkSize,  0), trunkColor), //7


        };

        vector<unsigned int> indices3 =
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            // TODO(student): Complete indices data for the cube mesh
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4



        };

        Mesh* trunk = new Mesh("trunchi");
        trunk->InitFromData(vertices3, indices3);
        AddMeshToList(trunk);
    }


    {
        vector<VertexFormat> vertices4
        {
            //VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),// fara normala acm
            VertexFormat(glm::vec3(0, 0,  1), leavesColor), //0
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(1, 0, 1), leavesColor), //1
            VertexFormat(glm::vec3(0, 1,  1), leavesColor), //2
            VertexFormat(glm::vec3(1, 1, 1), leavesColor), //3
            VertexFormat(glm::vec3(0, 0,  0), leavesColor), //4
            VertexFormat(glm::vec3(1, 0,  0), leavesColor), // 5
            VertexFormat(glm::vec3(0, 1,  0), leavesColor), //6
            VertexFormat(glm::vec3(1, 1,  0), leavesColor), //7


        };

        vector<unsigned int> indices4 =
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            // TODO(student): Complete indices data for the cube mesh
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4



        };

        Mesh* leaves = new Mesh("frunze");
        leaves->InitFromData(vertices4, indices4);
        AddMeshToList(leaves);
    }
    

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
   
    glm::mat4 modelMatrix = glm::mat4(1);
    for (glm::vec3 x : roadData) {
        //modelMatrix = x;
        
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x[0]*3, x[1]*3, x[2]*3));
        //modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 1.2));
        RenderMesh(meshes["trunchi"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
    }

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
    RenderMesh(meshes["frunze"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(16, 16, 16));
    RenderMesh(meshes["iarba"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(3, 3, 3));
    RenderMesh(meshes["pista"], shaders["VertexColor"],modelMatrix);
    
    
   

    if (viewFlag == 0)
        projectionMatrix = glm::perspective(RADIANS(zoom), window->props.aspectRatio, 0.01f, 200.0f);
    else
        projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);



    // TODO(student): Draw more objects with different model matrices.
    // Attention! The `RenderMesh()` function overrides the usual
    // `RenderMesh()` that we've been using up until now. This new
    // function uses the view matrix from the camera that you just
    // implemented, and the local projection matrix.

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_Z) && viewFlag == 0) {
            // TODO(student): Translate the camera upward
            zoom += 2;

        }

        if (window->KeyHold(GLFW_KEY_X) && viewFlag == 0) {
            // TODO(student): Translate the camera upward
            zoom -= 2;

        }


    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections

    if (key == GLFW_KEY_O)
    {
        viewFlag = 1;
    }

    if (key == GLFW_KEY_P)
    {
        viewFlag = 0;
    }


}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
            camera->RotateFirstPerson_OX(-deltaY * sensivityOY);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
            camera->RotateFirstPerson_OX(-deltaY * sensivityOY);


        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
