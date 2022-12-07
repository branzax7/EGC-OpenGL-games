#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

#define M_PI 3.1415926535897932384626433832795

vector<glm::vec3> roadData;
vector<glm::vec3> points;
glm::vec3 carPos;
int aaa = 0;
float rot;



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
    glm::vec3 grassColor = glm::vec3(0.47, 1, 0.5);
    glm::vec3 trunkColor = glm::vec3(0.13, 0.12, 0.09);
    glm::vec3 leavesColor = glm::vec3(0.15, 0.27, 0.15);
    glm::vec3 carColor = glm::vec3(0.46, 0.04, 0.11);


    roadLevel = 0.009;
    roadScale = 3;
    grassLevel = 0.001;

    blue = 0.2;
    red = 0.2;
    treePos = 0.25;
    trunkSize = 0.2;
    leavesSize = 1;
    carSize = 0.2;

    angle = 0;
    
    
    
    
    glm::vec3 up = glm::vec3(0, 1, 0);

    camera = new implemented::Camera2();
    //camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

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


    roadData = {
        glm::vec3(4.86, 0, 0.29), //A
        glm::vec3(4.21, 0, 1.4), //B
        glm::vec3(2.79, 0, 2.14), //C
        glm::vec3(1.5, 0, 1.95), //D
        glm::vec3(0.59, 0, 1.25), //E
        glm::vec3(-0.48, 0, 0.6), //F
        glm::vec3(-1.76, 0, 1.15), //G
        glm::vec3(-2.83, 0, 1.43), //H
        glm::vec3(-3.79, 0, 0.81), //I
        glm::vec3(-3.93, 0, -0.19), //J
        glm::vec3(-3.45, 0, -1.05), //K
        glm::vec3(-2.11, 0, -1.55), //L
        glm::vec3(-0.68, 0, -1.62), //M
        glm::vec3(0.44, 0, -0.98), //N
        glm::vec3(1.39, 0, -0.23), //O
        glm::vec3(2.57, 0, -0.77), //P
        glm::vec3(3.47, 0, -1.42), //Q
        glm::vec3(4.58, 0, -0.92) //R
    };
    glm::vec3 cp;
    int j;
    
    {
        vector<VertexFormat> vertices = {};
        std::cout << "Maura: " << roadData.size() << endl;
        float x, y, z;
        glm::vec3 v{}, pv{};

        for (int i = 0; i < roadData.size(); i++) {
            v = roadData[i];
            if (i == 0) {
                pv = PointsToVec3(roadData[i], roadData[roadData.size() - 1]);
                //cp = CrossProduct(PointsToVec3(roadData[i], roadData[roadData.size() - 1]), up);
                cp = glm::cross(PointsToVec3(roadData[i], roadData[roadData.size() - 1]), up);
            }
            else {
                j = i - 1;
                pv = PointsToVec3(roadData[i], roadData[j]);
                //cp = CrossProduct(PointsToVec3(roadData[i], roadData[j]), up);
                cp = glm::cross(PointsToVec3(roadData[i], roadData[j]), up);
            }
            //cout << "Pct: " << v << " " << "PointsToVec3 " << pv << endl;

            
            vertices.push_back(VertexFormat(glm::vec3(v[0] + blue * cp[0], roadLevel, v[2] + blue * cp[2]), roadColor));
            points.push_back(glm::vec3(v[0] + treePos * cp[0], 0, v[2] + treePos * cp[2]));
        }

        for (int i = 0; i < roadData.size(); i++) {
            v = roadData[i];
            if (i == 0) {
                //cp = CrossProduct(PointsToVec3(roadData[i], roadData[roadData.size() - 1]), up);
                cp = glm::cross(PointsToVec3(roadData[i], roadData[roadData.size() - 1]), up);
            }
            else {
                j = i - 1;
                //cp = CrossProduct(PointsToVec3(roadData[i], roadData[j]), up);
                cp = glm::cross(PointsToVec3(roadData[i], roadData[j]), up);
            }
            vertices.push_back(VertexFormat(glm::vec3(v[0] - red * cp[0], roadLevel, v[2] - red * cp[2]), roadColor));
            points.push_back(glm::vec3(v[0] - treePos * cp[0], 0, v[2] - treePos * cp[2]));
        }

        std::cout << " Size of Vertices = " << vertices.size() << std::endl;

        
        glm::vec3 p1, p2;
        p1 = points[0];
        p2 = points[35];
       
        for (auto x : points) {
            std::cout << x << endl;
        }
        cout << endl;

        carPos = glm::vec3 ((p1[0]+p2[0])*0.5, (p1[1]+p2[1])*0.5, (p1[2]+p2[2])*0.5);
        carX = carPos[0] * roadScale;
        carY = carPos[1] * roadScale;
        carZ = carPos[2] * roadScale;
        
       
        //1   2   3   4   

        // (R2, R1, A1), (R2, A1, A2) R->A
        // (A2, A1, B1), (A2, B1, B2) A->B

        //0-17 A1-R1
        //18-35 A2-R2
        // i = 0; j = 18
        //A->B: (j, i, i+1), (j, i+1, j+1)

        vector<unsigned int> indices = {};
        int i = 0;
        int j = 18;
        for (int k = 0; k < 17; k++) {
            indices.push_back(j);
            indices.push_back(i);
            indices.push_back(i+1);

            indices.push_back(j);
            indices.push_back(i+1);
            indices.push_back(j+1);

            i++;
            j++;
        }
        //R->A
        indices.push_back(35); //R2
        indices.push_back(17); //R1
        indices.push_back(0); //A1

        indices.push_back(35); //R2
        indices.push_back(0); //A1
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

        //camera->Set(glm::vec3(carX, carY + 0.5, carZ), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        //camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        carView = 1.2;
        //camera->SetPos(glm::vec3(carX, carY + 0.5, carZ + carView));
        camera->position = glm::vec3(carX, carY + 0.5, carZ + carView);
        //camera->RotateFirstPerson_OY(-M_PI/2);
        //camera->RotateFirstPerson_OX(0);
        
        Mesh* trunk = new Mesh("trunchi");
        trunk->InitFromData(vertices3, indices3);
        AddMeshToList(trunk);
    }


    {
        vector<VertexFormat> vertices4
        {
            //VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),// fara normala acm
            VertexFormat(glm::vec3(0, 0,  leavesSize), leavesColor), //0
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(leavesSize, 0, leavesSize), leavesColor), //1
            VertexFormat(glm::vec3(0, leavesSize,  leavesSize), leavesColor), //2
            VertexFormat(glm::vec3(leavesSize, leavesSize, leavesSize), leavesColor), //3
            VertexFormat(glm::vec3(0, 0,  0), leavesColor), //4
            VertexFormat(glm::vec3(leavesSize, 0,  0), leavesColor), // 5
            VertexFormat(glm::vec3(0, leavesSize,  0), leavesColor), //6
            VertexFormat(glm::vec3(leavesSize, leavesSize,  0), leavesColor), //7


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

        //camera->RotateFirstPerson_OY(-RADIANS(45));
    }


    {
        vector<VertexFormat> vertices5
        {
            //VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)),// fara normala acm
            VertexFormat(glm::vec3(0, 0,  carSize), carColor), //0
            // TODO(student): Complete the vertices data for the cube mesh
            VertexFormat(glm::vec3(carSize, 0, carSize), carColor), //1
            VertexFormat(glm::vec3(0, carSize,  carSize), carColor), //2
            VertexFormat(glm::vec3(carSize, carSize, carSize), carColor), //3
            VertexFormat(glm::vec3(0, 0,  0), carColor), //4
            VertexFormat(glm::vec3(carSize, 0,  0), carColor), // 5
            VertexFormat(glm::vec3(0, carSize,  0), carColor), //6
            VertexFormat(glm::vec3(carSize, carSize,  0), carColor), //7


        };

        vector<unsigned int> indices5 =
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

        Mesh* car = new Mesh("masina");
        car->InitFromData(vertices5, indices5);
        AddMeshToList(car);
    }


    cout << endl;
    glm::vec3 ih = glm::vec3(0.96, 0, 0.62);
    //glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 i = glm::vec3(-3.79, 0, 0.81);

    

    glm::vec3 res = CrossProduct(ih, up);
    res = glm::vec3(i[0] + 0.2*res[0], i[1] + 0.2 * res[1], i[2] + 0.2 * res[2]);
    std::cout << "I: (" << i[0] << ", " << i[1] << ", " << i[2] << ")" << endl;
    std::cout << "res: (" << res[0] << ", " << res[1] << ", " << res[2] << ")" << endl;

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.47, 0.96, 0.96, 1);
    //glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
   
    glm::mat4 modelMatrix = glm::mat4(1);
    for (glm::vec3 x : points) {
        //modelMatrix = x;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 3, 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x[0]*3, x[1]*3, x[2]*3));
        //centrat in origine
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-trunkSize/2, 0, -trunkSize/2));
        //modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 1.2));
        RenderMesh(meshes["trunchi"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 3*trunkSize, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x[0] * roadScale, x[1] * roadScale, x[2] * roadScale));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-leavesSize / 2, 0, -leavesSize / 2));
        RenderMesh(meshes["frunze"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat4(1);

    }

    /*
    //if (aaa == 0) {
        modelMatrix = glm::mat4(1);
        carX = camera->position[0];
        carY = camera->position[1] - 0.5;
        carZ = camera->position[2] - carView;
        //camera->position = glm::vec3(carX, carY + 0.5, carZ + carView);
    //}
    
    
    //glm::mat4 rotation = glm::rotate(glm::mat4(1), RADIANS(45)*2, glm::vec3(0, 1, 0));
    //modelMatrix = camera->GetViewMatrix();
    modelMatrix = glm::translate(modelMatrix, glm::vec3(carX, carY, carZ));
    //camera->position = glm::vec3(carX, carY + 0.5, carZ + carView);
    //modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 2));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-carSize / 2, 0, -carSize / 2));
    
    //camera->position = glm::vec3(carX, carY + 0.5, carZ);
    //camera->position = glm::vec3(camera->position[0], camera->position[1], camera->position[2] + carView);
    if (aaa == 0) {
        //puts("!!!!!!!!!!!!!!");
        //camera->position = glm::vec3(carX, carY + 0.5, carZ + carView);
        //camera->RotateThirdPerson_OY(RADIANS(45));
        //camera->position = glm::vec3(carX, carY, carZ);
        //aaa = 1;
    }
    RenderMesh(meshes["masina"], shaders["VertexColor"], modelMatrix);
    */

    modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, glm::vec3(0,-0.7, 0));
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -0.47, 0.7));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 2));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-carSize / 2, 0, -carSize / 2));
    RenderMesh(meshes["masina"], shaders["VertexColor"], modelMatrix);
    

    //camera->position = glm::vec3(carX, carY + 0.5, carZ);
    /*glm::mat4 rotation = glm::rotate(glm::mat4(1), rot, glm::vec3(0, 1, 0));
    modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());

    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix *= rotation;
    //modelMatrix = glm::rotate(modelMatrix, rot, glm::vec3(0, 1, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 2));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-carSize / 2, 0, -carSize / 2));
    RenderMesh(meshes["masina"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat4(1);
    //modelMatrix = glm::translate(modelMatrix, glm::vec3(-carSize / 2, 0, -carSize / 2));
    RenderMesh(meshes["masina"], shaders["VertexColor"], modelMatrix);
    */


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
        modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 2));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-carSize / 2, 0, -carSize / 2));
        RenderMesh(meshes["masina"], shaders["VertexNormal"], modelMatrix);
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
            //camera->TranslateRight(-deltaTime * cameraSpeed);
            aaa = 1;

            camera->RotateThirdPerson_OY(deltaTime * cameraSpeed);
            angle += deltaTime * cameraSpeed;

        }
        aaa = 0;

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime * cameraSpeed);

        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            //camera->TranslateRight(deltaTime * cameraSpeed);
            aaa = 1;
            camera->RotateThirdPerson_OY(-deltaTime * cameraSpeed);
            angle += -deltaTime * cameraSpeed;
        }
        aaa = 0;

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
            rot = -deltaX * sensivityOX;
            camera->RotateFirstPerson_OY(-deltaX * sensivityOX);
            camera->RotateFirstPerson_OX(-deltaY * sensivityOY);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OY(-deltaX * sensivityOX);
            camera->RotateThirdPerson_OX(-deltaY * sensivityOY);


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

glm::vec3 Tema2::CrossProduct(glm::vec3 a, glm::vec3 b) {

    float i = (a[1] * b[2]) - (b[1] * a[2]);
    float j = -1 * ((a[0] * b[2]) - (b[0] * a[2]));
    float k = (a[0] * b[1]) - (b[0] * a[1]);
    return glm::vec3(i, j, k);
}

glm::vec3 Tema2::PointsToVec3(glm::vec3 a, glm::vec3 b) {

    float x = b[0] - a[0];
    float y = b[2] - a[2];
    return glm::vec3(x, 0, y);

}
