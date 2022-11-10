#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <ctime>


#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}



void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    srand(time(0));
    vitezaCadere = 5;
    vitezaEvadare = 5;
    
    gameplay = 0;
    timeElapsed = 0;
    lives = 3;
    bullets = 3;
    speed = 5;
    shot = 0;
    speedCounter = 0;
    birdCounter = 1;

    wingSide = 70;
    triangleSide = 100;
    wingX = 500;
    wingY = 500;
    headX = 900;
    headY = 200;
    pasareR = M_PI / 4;
    tX = 5;
    tY = 5;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;
    addt = 1;
    t = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;
    sgn = 1;

    // Initialize angularStep
    angularStep = 0;

    glm::vec3 color = glm::vec3(1, 0, 0);

   
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* triangle1 = object2D::CreateTriangle("body", corner, triangleSide, glm::vec3(1, 0, 0));
    AddMeshToList(triangle1);

    Mesh* triangle2 = object2D::CreateTriangle("wing", corner, wingSide, glm::vec3(0, 0, 1));
    AddMeshToList(triangle2);

    Mesh* triangle3 = object2D::CreateTriangle("cioc", corner, 10, glm::vec3(1, 0.5f, 0));
    AddMeshToList(triangle3);


    Mesh* circle1 = object2D::CreateCircle("head", corner, 100, glm::vec3(1, 1, 0));
    AddMeshToList(circle1);

    Mesh* circle2 = object2D::CreateCircle("life", corner, 100, glm::vec3(1, 0, 0));
    AddMeshToList(circle2);
    
    Mesh* triangle4 = object2D::CreateTriangle("bullet", corner, 25, glm::vec3(1, 1, 0.5f));
    AddMeshToList(triangle4);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

   


    //++++++++++++++++++++++++++++++++++++miscare dupa pozitia capului, fac ca in ocw tema cresc in mod egal x y la translatie => unghi de 45 de grade
    
    //de disparut
    //sus
    //if (shot == 1)
        //cout << "CPLM CHIORETE!!!" << endl;
    timeElapsed += deltaTimeSeconds;
    if ((gameplay == 1 && headY >= 720) || (gameplay == 2 && headY <= 0)) { //am nev de pasarte noua, a evadat pasarea curenta
        //cout << "PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP" << endl;
        if (gameplay == 1)
            lives--;
        if (birdCounter % 5 == 0) {
            speedCounter++;
            speed = speed + speedCounter * speed / 5;
        }
        
        //trebuie cu random
        headX = rand() % 1100 + 100;
        headY = 200;
        //headX = 900;
        poz = rand() % 2;
        if (poz == 0) { //dreapta
            pasareR = M_PI / 4;
            tX = speed;
        }
        else {
            pasareR = 3 * M_PI / 4;
            tX = -speed;
        }
        tY = speed;
        timeElapsed = 0;
        gameplay = 0;
        shot = 0;
        bullets = 3;
        birdCounter++;
        cout << "birdCounter= " << birdCounter << "speed= " << speed << endl;
    }
    //cout << "counter: " << counter << " sht: " << shot << endl;
    if (gameplay == 0) {
        if (tY > 0) {
            if (tX > 0) { //dreapta
                if (timeElapsed >= 5 || bullets == 0) { //evadare
                    pasareR += M_PI / 4;
                    tX = 0;
                    tY = vitezaEvadare;
                    gameplay = 1;
                }
                else if (timeElapsed < 5 && shot == 0) {
                    if (headX >= 1280) { //perete drept
                        pasareR += M_PI / 2; //pozitionare
                        tX *= -1; // shimbare directie
                    }

                    if (headY >= 720) { //tavan
                        pasareR -= M_PI / 2; // += ...
                        tY *= -1;
                    }
                }
                else if (shot == 1) {  //cade moarta
                    //cout << "DAAAAAAAAAAAAAAAAAAA" << endl;
                    pasareR -= 3 * M_PI / 4;
                    tX = 0;
                    //tY *= -1;
                    tY = -vitezaCadere;
                    gameplay = 2;
                }
            }

            if (tX < 0) { //stanga
                if (timeElapsed >= 5 || bullets == 0) { //evadare
                    pasareR -= M_PI / 4;
                    tX = 0;
                    tY = vitezaEvadare;
                    gameplay = 1;
                }
                else if (timeElapsed < 5 && shot == 0) {
                    if (headX <= 0) { //perete stang
                        pasareR -= M_PI / 2; //pozitionare
                        tX *= -1; // shimbare directie
                    }

                    if (headY >= 720) { //tavan
                        pasareR += M_PI / 2; // += ... 180 + 90
                        tY *= -1;
                    }
                }
                else if (shot == 1) {  //cade moarta
                    pasareR += 3 * M_PI / 4;
                    tX = 0;
                    //tY *= -1;
                    tY = -vitezaCadere;
                    gameplay = 2;
                }
            }
        }

        //jos
        if (tY < 0) {
            if (tX > 0) { //dreapta
                if (timeElapsed >= 5 || bullets == 0) {
                    pasareR += 3 * M_PI / 4;
                    tX = 0;
                    //tY *= -1;
                    tY = vitezaEvadare;
                    gameplay = 1;
                }
                else if (timeElapsed < 5 && shot == 0) {
                    if (headX >= 1280) { //perete drept
                        pasareR -= M_PI / 2; //pozitionare
                        tX *= -1; // shimbare directie
                    }

                    if (headY <= 0) { //podea
                        pasareR += M_PI / 2; // += ...
                        tY *= -1;
                    }
                }
                else if (shot == 1) {  //cade moarta
                    pasareR -= M_PI / 4;
                    tX = 0;
                    tY = -vitezaCadere;
                    gameplay = 2;
                }
            }

            if (tX < 0) { //stanga
                if (timeElapsed < 5 && shot == 0) {
                    if (headX <= 0) { //perete stang
                        pasareR += M_PI / 2; //pozitionare
                        tX *= -1; // shimbare directie
                    }

                    if (headY <= 0) { //podea
                        pasareR -= M_PI / 2; // += ...
                        tY *= -1;
                    }
                }
                else if (shot == 1) {  //cade moarta
                    pasareR += M_PI / 4;
                    tX = 0;
                    tY = -vitezaCadere;
                    gameplay = 2;
                }
                else {
                    pasareR -= 3 * M_PI / 4;
                    tX = 0;
                    //tY *= -1;
                    tY = vitezaEvadare;
                    gameplay = 1;
                }
            }
        }
    }
    
    
    //problemqa colt stanga jos cand vine pe x+ y-

    //coord poigon functie poate?
    //coord poigon functie poate?
    L = 200;
    l = 120;
    //(rectX1, rectY) (rectX, rectY)
    //(rectX1, rectY1) (rectX, rectY1)
    rectX = headX - 100 - 40;
    rectY = headY - 100 - 50;
    rectX1 = rectX - L;
    rectY1 = rectY - l;

    d1 = 0.71 * L;
    d2 = 0.71 * l; //d3 foaie

    //(rectX11, rectY2) (rectX, rectY)
         //(rectX12, rectY11) (rectX2, rectY12)
    rectX11 = L - d1 + rectX1;
    rectY2 = rectY - d1;
    rectX12 = rectX11 + d2;
    rectY11 = rectY2 - d2;
    rectX2 = rectX + d2;
    rectY12 = rectY - d2;

    //miscare continua
    headX += tX;
    headY += tY;

    //vieti
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 700);
    modelMatrix *= transform2D::Scale(15, 15);
    if (lives > 0)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(2, 0);
    if (lives > 1)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(2, 0);
    if (lives > 2)
        RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);

    //gloante !!!! de gasit cuiloarea VERDE !!!!!!!!!!!!!!!!!!!!!!!!!!!
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(10, 650);
    if (bullets > 0)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(30, 0);
    if (bullets > 1)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(30, 0);
    if (bullets > 2)
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);


    //rata
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(headX, headY);

    angularStep += M_PI * deltaTimeSeconds*0.5; // animare aripi de mutat langa atipi poate????????????
    if (angularStep >= M_PI / 12)
        angularStep = 0;

    //modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Rotate(pasareR); // rotatie cioara
    modelAux = modelMatrix;
    modelMatrix *= transform2D::Scale(30, 30);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    modelMatrix = modelAux;
    //!!!!!!!!!!!!!!! fac dreptunch care acopera rata si nus se roteste odata cu rata, dar isi schimba poz dupa rotatie sa poata incadra mai bine rata => f. simplu
    modelMatrix *= transform2D::Translate(40, 50);
    modelMatrix *= transform2D::Scale(2, 1.2);
    modelMatrix *= transform2D::Translate(-100, -100);

    //RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);  //rectangle coliziune din patrat scalat cu latura 100

    //modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(-70, -60);
    modelMatrix = modelAux;
    //modelMatrix *= transform2D::Scale((float)1 / 30, (float)1 / 30);
    modelMatrix *= transform2D::Translate(-70, -60);
    //modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Rotate(M_PI / 4);
    modelAux = modelMatrix;
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

    
    modelMatrix *= transform2D::Translate(115, -35);
    modelMatrix *= transform2D::Rotate(M_PI/2);
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = modelAux;


    //modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Scale(1.4, 1.4);
    modelMatrix *= transform2D::Translate(20, 50);
    
    modelMatrix *= transform2D::Rotate(-M_PI / 4);

    modelAux = modelMatrix;
    modelMatrix *= transform2D::Translate(50, 0);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-50, 0);

    

    RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);


    modelMatrix = modelAux;
    modelMatrix *= transform2D::Translate(-20, -20);
    modelMatrix *= transform2D::Rotate(-M_PI/2);
    modelMatrix *= transform2D::Translate(0, 100);
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(0, -100);
    RenderMesh2D(meshes["wing"], shaders["VertexColor"], modelMatrix);

    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(headX - 50, headY);
    modelMatrix *= transform2D::Translate(50, 50);
    modelMatrix *= transform2D::Scale(3, 3);
    modelMatrix *= transform2D::Translate(-50, -50);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);*/

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    
    // Add mouse button press event
    mouseY2 = 720 - mouseY;
    cout << "MouseX: " << mouseX << endl;
    cout << "MouseY: " << mouseY2 << endl;
    /*cout << rectX11 << " " << rectX2 << " " << rectY11 << " " << rectY << ": ";
    if (mouseX > rectX11 && mouseX < rectX2 && mouseY2 > rectY11 && mouseY2 < rectY) {
        cout << "DAAAAAAAAAAAA" << endl;
    }
    else
        cout << "NUUUUUUUUUUUU" << endl;*/

    if (mouseX > 640 && shot == 0) {
        shot = 1;
        bullets--;
    }
    if (shot == 0)
        bullets--;





}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
