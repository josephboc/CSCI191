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
#include <_timer.h>
#include <_texts.h>
_Model *myModel = new _Model();
_inputs *kBMs = new _inputs();
_parallax *plxForest = new _parallax();
_parallax *plxAtmo = new _parallax();
_player *ply = new _player();
_texts *txp = new _texts();
_texts *txp2 = new _texts();
_checkCollision *hit= new _checkCollision();
_sound *snds = new _sound();
_sound *snds2 = new _sound();
_npc *npc = new _npc();
_parallax *cred = new _parallax(1);
_parallax *menu = new _parallax(1);
_parallax *help = new _parallax(1);

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
    currentSeason = 0; // 0-summer, 1-fall, 2-winter, 3-spring
    doneLoading = false;
    foodstack = 0;
    prev = 4;
    switching = false;
    switching1 = false;
    switching2 = false;
    switching3 = false;
    startover = 0;
    ply->health = 100;
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

   myModel->initModel();
   enmsTex->loadTexture("images/smallblackcat.png");
   foodTex->loadTexture("images/frutis.png");
   NPCTex->loadTexture("images/npcs.png");
   textTex->loadTexture("images/percent sprites.png");
   textTex2->loadTexture("images/health sprites.png");
   plxForest->parallaxInit("images/fresnostate4.png");
   plxAtmo->parallaxInit("images/png.png");
   ply->initPlayer("images/ply2.png");
   ply->yPos = -0.3;
   ply->zPos = -2.5;

   txp2->inittext(textTex2->tex);
   txp2->placetext(-1.04,-.645,-2.0);

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
    help->parallaxInit("images/help_page.png");


   snds->initSounds();
   snds->engine->stopAllSounds();  //Stop sound
   snds->tmr->start();
   snds2->initSounds();
   snds2->engine->stopAllSounds();  //Stop sound
   snds2->tmr->start();

   if(currentSeason == 0){ //Load summer image
    food[0].action = 0;
    plxForest->parallaxInit("images/fresnostate3.png");
       snds->playMusic("sounds/tobyfox4.mp3");
       snds2->playSound("sounds/joseph2.mp3");

    doneLoading = true;
    switching = false;
    switching1 = false;
       switching2 = false;
       switching3 = false;

        counter = 1;
   for(int i=0; i<counter;i++)
   {

       enms[i].initEnemy(enmsTex->tex);
        if(i < (counter / 2)){ enms[i].placeEnemy((float)(rand()%20)/10.0,(rand() % 9) / 10.0,-2.5);}
        else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(float)(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = .5;
       // food[i].initFood(foodTex->tex);
      // food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
      // food[i].xSize = food[i].ySize = .02;

   }

   for(int u=0; u<counter; u++)
   {


       food[u].initFood(foodTex->tex);
       if(u == 0){food[u].placeFood(0,.3,-2.5);}
    else if(u < (counter / 2)){
    food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / 10.0),-2.5);
}

        else{food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / -10.0),-2.5);}
       food[u].xSize = food[u].ySize = .02;
        food[u].action = 0;
   }
   }

   if(currentSeason == 1){  //Load fall image
    plxForest->parallaxInit("images/fresnostate5.png");
    plxAtmo->parallaxInit("images/leaves.png");
    snds->playMusic("sounds/mattflores.mp3");
    doneLoading = true;
    switching =true;
        ply->health = 100;
            counter = 6;
   for(int i=0; i<counter;i++)
   {
       enms[i].initEnemy(enmsTex->tex);
if(i < (counter / 2)){ enms[i].placeEnemy((float)(rand()%20)/10.0,(rand() % 9) / 10.0,-2.5);
}
        else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(float)(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = .5;
       // food[i].initFood(foodTex->tex);
      // food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
      // food[i].xSize = food[i].ySize = .02;

   }

   for(int u=0; u<counter; u++)
   {


       food[u].initFood(foodTex->tex);
       if(u == 0){food[u].placeFood(0,.3,-2.5);}
    else if(u < (counter / 2)){
    food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / 10.0),-2.5);
}

        else{food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / -10.0),-2.5);}
       food[u].xSize = food[u].ySize = .02;
        food[u].action = 0;
   }
   }

   if(currentSeason == 2){  //Load winter image
    plxForest->parallaxInit("images/fresnostate6.png");
    plxAtmo->parallaxInit("images/rain.png");
    snds->playMusic("sounds/tobyfox.mp3");
    ply->health = 100;
   doneLoading = true;
           counter = 12;
  for(int i=0; i<counter;i++)
   {
       if(i > 5){enms[i].initEnemy(enmsTex->tex);}
if(i < (counter / 2)){ enms[i].placeEnemy((float)(rand()%20)/10.0,(rand() % 9) / 10.0,-2.5);
}
        else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(float)(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = float(rand()%12)/85.0;
       // food[i].initFood(foodTex->tex);
      // food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
      // food[i].xSize = food[i].ySize = .02;

   }

   for(int u=0; u<counter; u++)
   {


       food[u].initFood(foodTex->tex);
       if(u == 0){food[u].placeFood(0,.3,-2.5);}
    else if(u < (counter / 2)){
    food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / 10.0),-2.5);
}

        else{food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / -10.0),-2.5);}
       food[u].xSize = food[u].ySize = .02;
        food[u].action = 0;
   }
   }

   if(currentSeason == 3){  //Load spring image
    plxForest->parallaxInit("images/fresnostate4.png");
    plxAtmo->parallaxInit("images/snow.png");
    snds->playMusic("sounds/karasquare.mp3");
    doneLoading = true;
            counter = 20;
                ply->health = 100;
            switching = true;
 for(int i=0; i<counter;i++)
   {
        if(i > 11){enms[i].initEnemy(enmsTex->tex);}
if(i < (counter / 2)){ enms[i].placeEnemy((float)(rand()%20)/10.0,(rand() % 9) / 10.0,-2.5);
}
        else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(float)(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = float(rand()%12)/85.0;
       // food[i].initFood(foodTex->tex);
      // food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
      // food[i].xSize = food[i].ySize = .02;

   }

   for(int u=0; u<counter; u++)
   {


       food[u].initFood(foodTex->tex);
       if(u == 0){food[u].placeFood(0,.3,-2.5);}
    else if(u < (counter / 2)){
    food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / 10.0),-2.5);
}

        else{food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / -10.0),-2.5);}
       food[u].xSize = food[u].ySize = .02;
        food[u].action = 0;
   }
   }

   if(currentSeason == 5){  //Load fall image
    plxForest->xMax = 1.0;
    plxForest->xMin = 0.0;
    plxForest->scroll(false,"right",0.5);
    plxForest->drawSquare(screenWidth,screenHeight);
    plxForest->parallaxInit("images/groupcredits2.png");
    doneLoading = true;
    switching =true;
            counter = 0;
   for(int i=0; i<counter;i++)
   {
       enms[i].initEnemy(enmsTex->tex);
if(i < (counter / 2)){ enms[i].placeEnemy((float)(rand()%20)/10.0,(rand() % 9) / 10.0,-2.5);
}
        else{ enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,(float)(rand() % 10) / -10.0,-2.5);}
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = float(rand()%12)/85.0;
       // food[i].initFood(foodTex->tex);
      // food[i].placeFood((float)(rand()/float(RAND_MAX))*4-2.5,-.2,-2.0);
      // food[i].xSize = food[i].ySize = .02;

   }

   for(int u=0; u<counter; u++)
   {


       if(u  >11){food[u].initFood(foodTex->tex);}


       if(u == 0){food[u].placeFood(0,.3,-2.5);}
    else if(u < (counter / 2)){
    food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / 10.0),-2.5);
}

        else{food[u].placeFood((float)((rand() % 20) / 10.0),(((rand() % 9)+1) / -10.0),-2.5);}
       food[u].xSize = food[u].ySize = .02;
        food[u].action = 0;
   }
   }

  //glEnable(GL_COLOR_MATERIAL);

 //  snds->initSounds();
 //  snds->playMusic("sounds/karasquare.mp3");
 //  snds->tmr->start();
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

    case HELP:
        glPushMatrix();
        glScaled(0.33, 1.0, 1.0);
        help->drawBacking(screenWidth, screenHeight);
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
     plxForest->drawSquare(screenWidth*2.5,screenHeight); // draw background
     plxForest->scroll(false,"right",0.0005);
     plxAtmo->drawSquare(screenWidth,screenHeight); // draw background
     plxAtmo->scroll(true,"up",0.0005);            // Automatic background movement
           // Automatic background movement

    glPopMatrix();


/*	glPushMatrix();                      // grouping starts
    glTranslated(0,0,-8.0);              //placing objects
    myModel->drawModel();             //Teapot model

    glPopMatrix();                       // grouping ends*/
    glPushMatrix();
     ply->actions();
     ply->drawPlayer();
    glPopMatrix();

    glPushMatrix();
     npc->action= rand() % 5 +1;
     npc->actions();
     npc->drawNPC();
    glPopMatrix();
    txp->drawtexts();
    txp2->drawtexts();
    ply->hungerlower();
  //  cout << foodstack << endl;

    for(int i =0; i<counter;i++) {
        if(!switching){food[i].action == 0;}
        if(enms[i].xPos<-2.0)
        {
            enms[i].action =0;
       //     enms[i].yPos =-0.2;
            enms[i].xMove =0.01;

        }
        else if(enms[i].xPos >2.0)
        {
            enms[i].action =1;
            enms[i].xMove = -0.01;
          //  enms[i].yPos =-0.2;
        }

       enms[i].xPos +=enms[i].xMove;

       if(ply->xPos > enms[i].xPos)
       {
           if(hit->isCollisionRadius(ply->xPos,ply->yPos,enms[i].xPos, enms[i].yPos,0.1,0.15)){ //ply->strength > 1)
           if(ply->cuteness > 10.0){

           }
           else if(ply->xMove > 1.0){
                ply->health = ply->health - 2.5;
                ply->xPos = ply->xPos + .5;
            }
            else if(ply->strength > 25.0){
            ply->health = ply->health - .5;
           if(fabs(enms[i].xPos - ply->xPos)<0.1)
           enms[i].action =2;
           }
           else if(ply->strength > 15.0){
            ply->health = ply->health - 1.5;
            if(fabs(enms[i].xPos - ply->xPos)<0.1)
           enms[i].action =2;

           }

           else if(ply->strength > 5.0){
            ply->xPos = ply->xPos + .5;
            ply->health = ply->health -3.5;
           }
           else{ply->xPos = ply->xPos + .5;
           ply->health = ply->health - 5;}
           }

       }


       if(ply->xPos < enms[i].xPos){
             if(hit->isCollisionRadius(ply->xPos,ply->yPos,enms[i].xPos, enms[i].yPos,0.1,0.15)){
                  if(ply->cuteness > 10.0){

                  }
             else if(ply->xMove > 1.0){
                ply->health = ply->health - 2.5;
                ply->xPos = ply->xPos - .5;
            }
             else if(ply->strength > 25.0){
            ply->health = ply->health - .5;
           if(fabs(enms[i].xPos - ply->xPos)<0.1)
           enms[i].action =3;
           }
           else if(ply->strength > 15.0){
            ply->health = ply->health - 1.5;
            if(fabs(enms[i].xPos - ply->xPos)<0.1)
           enms[i].action =3;

           }

           else if(ply->strength > 5.0){
            ply->xPos = ply->xPos - .5;
            ply->health = ply->health -3.5;
           }
           else{ply->xPos = ply->xPos - .5;
           ply->health = ply->health - 5;}
           }}




       if(hit->isCollisionRadius(ply->xPos,ply->yPos,food[i].xPos, food[i].yPos,0.1,0.09)&& (ply->action==4 || ply->action ==5)){
        if((fabs(food[i].yPos-ply->yPos)<.5 || ((fabs(food[i].yPos-ply->yPos)<1.2) && ply->yPos < 0.0)) && (fabs(food[i].xPos-ply->xPos)<.06)){

        prev = food[i].action;



        food[i].action  = 4;
        if(prev != food[i].action && food[i].action == 4){
            foodstack = foodstack+1;
        }
        ply->hunger = ply->hunger + .5;
        ply->skillpoints = ply->skillpoints + 1;
        }

   //    cout << ply->skillpoints << " ";

//        cout <<"Acorn collision" << endl;
       }
               if(ply->health >= 95){
            txp->action = 0;
        }
        else if(ply->health >= 90){
            txp->action = 1;
          }
          else if(ply->health >= 80){
            txp->action = 2;
          }
          else if(ply->health >= 70){
            txp->action = 3;
          }
          else if(ply->health >= 60){
            txp->action = 4;
          }
          else if(ply->health >= 50){
            txp->action = 5;
          }
         else if(ply->health >= 40){
            txp->action = 6;
          }
         else if(ply->health >= 30){
            txp->action = 7;
          }
         else if(ply->health >= 20){
            txp->action = 8;
          }
         else if(ply->health <= 19){
            txp->action = 9;
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
if(food[0].action == 4){
switching = true;
}else{switching = false;}
if(food[0].action == 4 && food[1].action == 4 && food[2].action == 4 && food[3].action == 4 && food[4].action == 4){// food[5].action == 4){
    switching1 = true;
//    cout <<"True" << endl;
}
if(food[0].action == 4 &&food[1].action == 4 && food[2].action == 4 && food[3].action == 4 && food[4].action == 4 && food[5].action == 4 && food[6].action == 4 && food[7].action == 4 && food[8].action == 4&& food[9].action == 4&& food[10].action == 4&& food[11].action == 4){
switching2 = true;
}
if(food[0].action == 4 &&food[1].action == 4 && food[2].action == 4 && food[3].action == 4 && food[4].action == 4 && food[5].action == 4 && food[6].action == 4 && food[7].action == 4 && food[8].action == 4&& food[9].action == 4&& food[10].action == 4&& food[11].action == 4 && food[12].action == 4 &&
   food[13].action == 4 && food[14].action == 4 && food[15].action == 4){
switching3 = true;
}
if(ply->health <= 0){
    startover = 1;
}
//cout <<food[1].action << " " << food[2].action;



//cout << food[i].xPos << " " << ply->xPos;



    }
    // end of for loop
        break;

        default:
        break;

}}
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
             kBMs->keyEnv(plxForest, 0.001);   //handling environment
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
