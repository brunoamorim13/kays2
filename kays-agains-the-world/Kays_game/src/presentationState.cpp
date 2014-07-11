#include "presentationState.h"


void PresentationState::load(int stack)
{
// TROCAR de acordo com stack
    background = new Sprite("data/img/Village.png");
    story1 = new Sprite("data/img/Story1.jpg");
    story2 = new Sprite("data/img/Story2.jpg");
    lvl1_1 = new Sprite("data/img/1.png");
    lvl1_2 = new Sprite("data/img/2.png");
    lvl1_3 = new Sprite("data/img/3.png");
    lvl1_4 = new Sprite("data/img/4.png");
    lvl1_5 = new Sprite("data/img/5.png");
    lvl1_6 = new Sprite("data/img/6.png");
    lvl1_7 = new Sprite("data/img/7.png");
    lvl1_8 = new Sprite("data/img/8.png");
    lvl2 = new Sprite("data/img/lvl2.png");
    lvl3 = new Sprite("data/img/lvl3.png");
    lvl4 = new Sprite("data/img/lvl4.png");


    anim.setSprite(background);
    anim.addWaiting(1);
    sub_state = 0;

    m_stack = stack;



}
int PresentationState::unload()
{
    delete background;
    delete story1;
    delete story2;
    delete lvl1_1;
    delete lvl1_2;
    delete lvl1_3;
    delete lvl1_4;
    delete lvl1_5;
    delete lvl1_6;
    delete lvl2;
    delete lvl3;
    delete lvl4;

    return 0;

}
StateType PresentationState::update(unsigned int dt)
{
    if (InputManager::getInstance()->isKeyDown() )
    {
        return GST_GAME;
    }
    anim.update(dt);

    if(m_stack == 1){
        return animationStage1(dt);
    }
    if(m_stack == 2){
        return animationStage2(dt);
    }
    if(m_stack == 3){
        return animationStage3(dt);
    }
    if(m_stack == 4){
        return animationStage4(dt);
    }
    if(m_stack == 5)
        return animationStageBoss(dt);



    return GST_NONE;


}

StateType PresentationState::animationStage2(unsigned int dt)
{
    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl2);
                anim.setPos(0,0);
                anim.addWaiting(8000);

                sub_state++;
            }
            break;
//        case 2: //Passou 1.5 segundos
//            if(anim.isReady())
//            {
//                anim.setSprite(story1);
//                anim.setPos(100,15);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(-234,15, 350);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(95,-174, 450);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-140,-174, 400);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-317,-174, 300);
//                anim.addWaiting(3000);
//                sub_state++;
//            }
//            break;
        case 2:
            if(anim.isReady())
                return GST_GAME; //Retorna avisando para mudar o estado do jogo
            break;
    }
    return GST_NONE;
}


StateType PresentationState::animationStage3(unsigned int dt)
{
    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl3);
                anim.setPos(0,0);
                anim.addWaiting(8000);

                sub_state++;
            }
            break;

        case 2:
            if(anim.isReady())
                return GST_GAME; //Retorna avisando para mudar o estado do jogo
            break;
    }
    return GST_NONE;
}


StateType PresentationState::animationStage4(unsigned int dt)
{
    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl4);
                anim.setPos(0,0);
                anim.addWaiting(8000);
                anim.addMoveToXY(0,-400, 350);
                anim.addWaiting(8000);
                sub_state++;
            }
            break;
        case 2:
            if(anim.isReady())
                return GST_GAME; //Retorna avisando para mudar o estado do jogo
            break;
    }
    return GST_NONE;
}


StateType PresentationState::animationStageBoss(unsigned int dt)
{
//    switch(sub_state)
//    {
//        case 0:
//            sub_state = 1;
//            break;
//        case 1: //Passou 1.5 segundos
//            if(anim.isReady())
//            {
//                anim.setSprite(story1);
//                anim.setPos(128,24);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(-200,24, 350);
//                anim.addWaiting(800);
//                anim.addMoveToXY(88,-191, 450);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-259,-191, 400);
//                anim.addWaiting(1000);
//                sub_state++;
//            }
//            break;
//        case 2: //Passou 1.5 segundos
//            if(anim.isReady())
//            {
//                anim.setSprite(story1);
//                anim.setPos(100,15);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(-234,15, 350);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(95,-174, 450);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-140,-174, 400);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-317,-174, 300);
//                anim.addWaiting(3000);
//                sub_state++;
//            }
//            break;
//        case 3:
//            if(anim.isReady())
//                return GST_GAME; //Retorna avisando para mudar o estado do jogo
//            break;
//    }
    return GST_NONE;
}


StateType PresentationState::animationStage1(unsigned int dt)
{
    switch(sub_state)
    {
        case 0:
            sub_state = 1;
            break;
        case 1: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_1);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 2: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_2);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(-234,15, 350);
//                anim.addWaiting(2000);
//                anim.addMoveToXY(95,-174, 450);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-140,-174, 400);
//                anim.addWaiting(1500);
//                anim.addMoveToXY(-317,-174, 300);
//                anim.addWaiting(3000);
                sub_state++;
            }
            break;
        case 3: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_3);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 4: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_4);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 5: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_5);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 6: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_6);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 7: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_7);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 8: //Passou 1.5 segundos
            if(anim.isReady())
            {
                anim.setSprite(lvl1_8);
                anim.setPos(0,0);
                anim.addWaiting(4000);
//                anim.addMoveToXY(0,-400, 350);
//                anim.addWaiting(4000);

                sub_state++;
            }
            break;
        case 9:
            if(anim.isReady())
                return GST_GAME; //Retorna avisando para mudar o estado do jogo
            break;
    }
    return GST_NONE;
}

void PresentationState::render()
{
    anim.render();
}

