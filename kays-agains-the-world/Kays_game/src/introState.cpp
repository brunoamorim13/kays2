#include "introState.h"

void IntroState::load(int stack)
{
    background = new Sprite("data/img/katw_logo-cloud.png");
    story1 = new Sprite("data/img/tecnologias.png");
    story2 = new Sprite("data/img/katw_logo-tools.png");
    logo = new Sprite("data/img/SandstormLogo.png");

    anim.setSprite(logo);
    anim.addWaiting(2000);
    sub_state = 0;
}
int IntroState::unload()
{
    delete background;
    delete story1;
    delete story2;
    delete logo;

    return 0;

}
StateType IntroState::update(unsigned int dt)
{
    if (InputManager::getInstance()->isKeyDown() )
    {
        return GST_MENU;
    }
    anim.update(dt);

    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(story1);
                anim.addWaiting(2000);
                sub_state++;
            }
            break;
//        case 2: //Passou 1.5 segundos
//            if(anim.isReady())
//            {
//                anim.setSprite(story1);
//                anim.addWaiting(2000);
//                sub_state++;
//            }
//            break;
//        case 3://Passou 1.5 segundos
//            if(anim.isReady())
//            {
//                anim.setSprite(story2);
//                anim.addWaiting(2000);
//                sub_state++;
//            }
//            break;
        case 2:
            if(anim.isReady())
                return GST_MENU; //Retorna avisando para mudar o estado do jogo
            break;
    }

    return GST_NONE;


}

void IntroState::render()
{
    anim.render();
}
