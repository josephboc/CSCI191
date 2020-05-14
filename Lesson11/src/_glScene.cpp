
#include "_glScene.h"
#include <_glLight.h>
#include <_Model.h>
#include <_inputs.h>
#include <_parallax.h>
#include <_player.h>
#include <_enms.h>
#include <_checkCollision.h>
#include <_sound.h>
#include <iostream>
#include <_food.h>
#include <_npc.h>
#include <_MenuManager.h>
#include <_texts.h>

_Model *myModel = new _Model();
_inputs *kBMs = new _inputs();
_parallax *plxForest = new _parallax();
_player *ply = new _player();
_texts *txp = new _texts();
_texts *txp2 = new _texts();
_checkCollision *hit= new _checkCollision();
_sound *snds = new _sound();
_npc *npc = new _npc();
_parallax *cred = new _parallax(1);
_parallax *menu = new _parallax(1);


//menu stuffs
_MenuManager *menuManager = new _MenuManager;

_textureLoader *enmsTex = new _textureLoader();
_textureLoader *foodTex = new _textureLoader();
_textureLoader *NPCTex = new _textureLoader();
_textureLoader *textTex = new _textureLoader();
_textureLoader *textTex2 = new _textureLoader();
_enms enms[20];
_food food[20];

_glScene::_glScene()
{
    //ctor
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
}

_glScene::~_glScene()
{
    //dtor
}

//Function for the main so that the game exits when escaped key clicked on the correct MenuStates
MenuStates _glScene::sendScreen(){
    return menuManager->currState;
}

GLint _glScene::initGL()
{

   glShadeModel(GL_SMOOTH);    // to make graphics nicer
   glClearColor(1.0f,0.5f,0.0f,1.0f); // background color R,G,B,Alpha
   glClearDepth(1.0f);          // Depth Clearance
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);




   _glLight Light(GL_LIGHT0);





   //main game images
   myModel->initModel();
   enmsTex->loadTexture("images/smallblackcat.png");
   foodTex->loadTexture("images/frutis.png");
   NPCTex->loadTexture("images/npcs.png");
   textTex->loadTexture("images/numbersprites.png");
   textTex2->loadTexture("images/skills.png");
   plxForest->parallaxInit("images/forest.jpg");
   ply->initPlayer("images/ply2.png");
   ply->yPos = -0.3;
   ply->zPos = -3.0;

   txp2->inittext(textTex2->tex);
   txp2->placetext(-1.1,-.65,-2.0);

   txp2->xSize = .08;
   txp2->ySize = .08;
   txp->inittext(textTex->tex);
   txp->placetext(-1.0,-.7,-2.2);

   txp->xSize = .08;
   txp->ySize = .08;

   npc->initNPC(NPCTex->tex);
   npc->xSize = npc->ySize = 0.25;

    //menu state images
    cred->parallaxInit("images/group_credits_x_w.png");
    menu->parallaxInit("images/menu_screen.png");



   for(int i=0; i<20;i++)
   {
       enms[i].initEnemy(enmsTex->tex);
       if(i < 10){ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(rand() % 10) / 10.0,-2.5);}
       else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = float(rand()%12)/85.0;

       food[i].initFood(foodTex->tex);
       food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
       food[i].xSize = food[i].ySize = .02;

   }




  //glEnable(GL_COLOR_MATERIAL);

   //snds->initSounds();
   //snds->playMusic("sounds/karasquare.mp3");
   //snds->tmr->start();
   return true;
}



GLint _glScene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();



   // glColor3f(1.0,0.0,0.0);              // setting colors

    menuManager->currState;
    switch(menuManager->currState){
    case LANDING:
        //starts as first thing when game loads, have no idea how the hell
        //it's just drawing an frigging square.
        glPushMatrix();
        glScaled(0.33, 1.0, 1.0);
        //glTranslated(0,0,-4.0);              //placing objects
        //glScalef(6.3 ,6.3 , 1.0);
        cred->drawBacking(screenWidth,screenHeight);
        //cred->scroll(false,"right",0.0005);
        glPopMatrix();
        break;

    case MENU:
        glPushMatrix();
        glScaled(.33, 1, 1.0);
        //glScalef(6.3,6.3,1);//trying something differnt
        menu->drawBacking(screenWidth,screenHeight);
        glPopMatrix();
        break;

    //there should be a "help" state case here
    //we're low on time, it's probably not gonna get implemented.

    case GAME:


        glPushMatrix();

        glTranslated(0,0,-4.0);              //placing objects
        glScalef(6.3,6.3,1);
        plxForest->drawSquare(screenWidth,screenHeight); // draw background
        plxForest->scroll(false,"right",0.0005);            // Automatic background movement

        glPopMatrix();




        /*	glPushMatrix();                      // grouping starts
            glTranslated(0,0,-8.0);              //placing objects
            myModel->drawModel();             //Teapot model

            glPopMatrix();                       // grouping ends*/


        glPushMatrix();             //draw player
         ply->actions();
         ply->drawPlayer();
        glPopMatrix();

        glPushMatrix();             // draw NPC
         //npc->action = rand() % 5 + 1;
         npc->actions();
         npc->drawNPC();
        glPopMatrix();

        glPushMatrix();
          txp->drawtexts();
          txp2->drawtexts();
        glPopMatrix();

        //initializing the hunger stat?
        ply->hungerlower();
        cout << ply->hunger << endl;

        //start of food mechanic visual draw, the for loop
        for(int i =0; i<20;i++) {
            food[i].action = 0;
            if(enms[i].xPos<-2.0)
            {
                enms[i].action =0;
                enms[i].yPos =-0.2;
                enms[i].xMove =0.01;

            }
            else if(enms[i].xPos >2.0)
            {
                enms[i].action =1;
                enms[i].xMove = -0.01;
                //enms[i].yPos =-0.2;
            }

        enms[i].xPos +=enms[i].xMove;

        if(ply->action == 0 && ply->xPos > enms[i].xPos)
        {
            if(hit->isCollisionRadius(ply->xPos,ply->yPos,enms[i].xPos, enms[i].yPos,0.1,0.11))

            if(fabs(enms[i].xPos - ply->xPos)<0.1)
            enms[i].action =2;
        }

        if(ply->action == 1 && ply->xPos < enms[i].xPos)
        {
            if(hit->isCollisionRadius(ply->xPos,ply->yPos,enms[i].xPos, enms[i].yPos,0.1,0.11))
            enms[i].action =3;
        }

        if(hit->isCollisionRadius(ply->xPos,ply->yPos,food[i].xPos, food[i].yPos,0.1,0.11)){
            food[i].action  = 4;
            ply->hunger = ply->hunger + .5;
            ply->skillpoints = ply->skillpoints + .1;
            if(ply->skillpoints == 0.0){
              txp->action = 0;
            }
            else if(ply->skillpoints > 1.0 && ply->skillpoints< 2.0){
              txp->action = 1;
            }
            else if(ply->skillpoints > 2.0 && ply->skillpoints< 3.0){
               txp->action = 2;
            }
            else if(ply->skillpoints > 3.0 && ply->skillpoints< 4.0){
              txp->action = 3;
            }
            else if(ply->skillpoints > 4.0 && ply->skillpoints< 5.0){
              txp->action = 4;
            }
            else if(ply->skillpoints > 5.0){
             txp->action = 5;
            }
            cout <<"Acorn collision" << endl;
        }
        if((ply->action == 6|| ply->action == 7 || ply->action == 8 || ply->action == 9) && ply->skillpoints > 1){
        ply->skillpoints = ply->skillpoints - 1;
               if(ply->skillpoints < 1.0){
        txp->action = 0;
       }
       else if(ply->skillpoints > 1.0 && ply->skillpoints< 2.0){
        txp->action = 1;
       }
       else if(ply->skillpoints > 2.0 && ply->skillpoints< 3.0){
        txp->action = 2;
       }
        else if(ply->skillpoints > 3.0 && ply->skillpoints< 4.0){
        txp->action = 3;
       }
        else if(ply->skillpoints > 4.0 && ply->skillpoints< 5.0){
        txp->action = 4;
       }
        else if(ply->skillpoints > 5.0){
        txp->action = 5;
       }
       }
//cout << "Skill points:" << ply->skillpoints;

       enms[i].actions();
       food[i].actions();
       txp->actions();
        }
    // end of for loop
        break;

    case PAUSED:
        glPushMatrix();
        glScaled(.75, .75, 1.0);
        glPopMatrix();
        break;

        default:
        break;

        //there should be a "pause" menu state here.
        //we'll see if that gets implemented, no promises.



    }


}

GLvoid _glScene::reSizeScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width/(GLfloat) height; // ratio for window mode
    glViewport(0,0,width,height);                          // setting view port
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,aspectRatio,0.1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int _glScene::winMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_KEYDOWN:

             kBMs->wParam = wParam;
             kBMs->keyPressed(myModel, menuManager); //handling Model Movements


             kBMs->keyPressed(ply);     // handling player movement
             kBMs->keyEnv(plxForest, 0.01);   //handling environment
             //kBMs->keyEnv(cred, 0.01);
             kBMs->keyPressed(snds);

              break;

        case WM_KEYUP:
             kBMs->keyUp(ply);
             break;

       case WM_LBUTTONDOWN:
            kBMs->wParam = wParam;
            kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_RBUTTONDOWN:
            kBMs->wParam = wParam;
            kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;
        case WM_MBUTTONDOWN:
            kBMs->wParam = wParam;
            kBMs->mouseEventDown(myModel,LOWORD(lParam),HIWORD(lParam));
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            kBMs->mouseEventUp();
            break;

        case WM_MOUSEMOVE:
              kBMs->mouseMove(myModel,LOWORD(lParam),HIWORD(lParam));
             break;
        case WM_MOUSEWHEEL:
             kBMs->mouseWheel(myModel,(double)GET_WHEEL_DELTA_WPARAM(wParam));
            break;
    }
}
