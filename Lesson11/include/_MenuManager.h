#ifndef _MENUMANAGER_H
#define _MENUMANAGER_H

//our wonderful array of gamestates.
enum MenuStates{LANDING, MENU, GAME, PAUSED, HELP, QUIT};

class _MenuManager
{
    public:
        _MenuManager();
        virtual ~_MenuManager();

        MenuStates currState = LANDING;



    protected:

    private:
};
//Done, J
#endif // _MENUMANAGER_H
