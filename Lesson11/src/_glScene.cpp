#include "_glScene.h"
#include <_glLight.h>


_glScene::_glScene()
{
    //ctor
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    currentSeason = 0; // 0-summer, 1-fall, 2-winter, 3-spring
    doneLoading = false;
    secondEffectOn = false;
}

_glScene::~_glScene()
{
    //dtor
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
   enmsTex->loadTexture("images/mon.png");
   foodTex->loadTexture("images/frutis.png");
   ply->initPlayer("images/ply.png");
   ply->yPos = -0.3;
   ply->zPos = -3.0;

   for(int i=0; i<20;i++)
   {
       enms[i].initEnemy(enmsTex->tex);
       enms[i].placeEnemy((float)(rand()/float(RAND_MAX))*1-2.5,-0.2,-2.5);
       enms[i].xMove= (float)(rand()/float(RAND_MAX))/100;
       enms[i].xSize = enms[i].ySize = float(rand()%12)/85.0;

       food[i].initFood(foodTex->tex);
       food[i].placeFood((float)(rand()/float(RAND_MAX))*5-2.5,-.2,-1.0);
       food[i].xSize = food[i].ySize = .02;

   }

  //glEnable(GL_COLOR_MATERIAL);

   snds->initSounds();
   snds->engine->stopAllSounds();  //Stop sound
   snds->playMusic("sounds/mp.mp3");
   snds->tmr->start();

   if(currentSeason == 0){ //Load summer image
    Season->parallaxInit("images/0.png"); //correct parallax for summer
    SeasonEffect->xMax = 0.0;
    SeasonEffect->yMax = 0.0;
    SeasonEffect->xMin = 1.0;
    SeasonEffect->yMin = 1.0;
    SeasonEffect->parallaxInit("images/sunray.png");  //Load season effect 1
    if(currentSeason%2 == 1){ //Load season effect 2
        SeasonEffect2->parallaxInit("images/sunray3.png");
    }
    else{
        SeasonEffect2->parallaxInit("images/sunray2.png");
    }
    doneLoading = true;
   }

   if(currentSeason == 1){  //Load fall image
    Season->parallaxInit("images/1.png");
    SeasonEffect->parallaxInit("images/leavefalling.png"); //Load season effect 1
    if(secondEffectOn){ //Load season effect 2
        SeasonEffect2->parallaxInit("images/sunray3.png");
        secondEffectOn = !secondEffectOn;
    }
    else{
        SeasonEffect2->parallaxInit("images/sunray2.png");
        secondEffectOn = !secondEffectOn;
    }
    doneLoading = true;
   }

   if(currentSeason == 2){  //Load winter image
    Season->parallaxInit("images/2.png");
    SeasonEffect->parallaxInit("images/snowing.png"); //Load season effect 1
    if(secondEffectOn){ //Load season effect 2
        SeasonEffect2->parallaxInit("images/sunray3.png");
        secondEffectOn = !secondEffectOn;
    }
    else{
        SeasonEffect2->parallaxInit("images/sunray2.png");
        secondEffectOn = !secondEffectOn;
    }
   doneLoading = true;
   }

   if(currentSeason == 3){  //Load spring image
    Season->parallaxInit("images/3.png");
    SeasonEffect->parallaxInit("images/raining.png"); //Load season effect 1
    if(secondEffectOn){ //Load season effect 2
        SeasonEffect2->parallaxInit("images/sunray3.png");
        secondEffectOn = !secondEffectOn;
    }
    else{
        SeasonEffect2->parallaxInit("images/sunray2.png");
        secondEffectOn = !secondEffectOn;
    }
    doneLoading = true;
   }

   return true;
}

GLint _glScene::drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();

   // glColor3f(1.0,0.0,0.0);              // setting colors

    glPushMatrix();

     glTranslated(0,0,-4.0);              //placing objects
     glScalef(6.3,6.3,1);
     Season->drawSquare(screenWidth,screenHeight); // draw background
     Season->scroll(false,"right",0.0005);            // Automatic background movement
     if(currentSeason == 0){
        SeasonEffect->drawSquare(screenWidth,screenHeight);
        SeasonEffect->scroll(false,"left", 0.0);
     }
     else{
        SeasonEffect->drawSquare(screenWidth,screenHeight);
        SeasonEffect->scroll(true,"up", 0.003);
     }
     SeasonEffect2->drawSquare(screenWidth,screenHeight);
     SeasonEffect2->scroll(false, "right", 0.0);

    glPopMatrix();


/*	glPushMatrix();                      // grouping starts
        glTranslated(0,0,-8.0);          //placing objects
        myModel->drawModel();            //Teapot model
    glPopMatrix();                       // grouping ends */

    glPushMatrix();
     ply->actions();
     ply->drawPlayer();
    glPopMatrix();

    ply->hungerlower();
    cout << ply->hunger << endl;

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
            enms[i].yPos =-0.2;
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
        ply->hunger = ply->hunger + 1;
        cout <<"Acorn collision" << endl;
       }

       enms[i].actions();
       food[i].actions();
    }
    // end of for loop
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
             kBMs->keyPressed(myModel); //handling Model Movements
             kBMs->keyPressed(ply);     // handling player movement
             kBMs->keyEnv(Season, 0.01);   //handling environment
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
