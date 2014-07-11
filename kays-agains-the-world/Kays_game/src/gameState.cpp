#include "gameState.h"

void StateGame::load(int stack)
{
    timerDead.stop();
    ///QUESTS
    Quest* q1 = new Quest("2. Mate 5 Slimes!",5);
    //q1->setActive(true);
    //q1->setComplete(true);
    q1->setActive(false);
    q1->setComplete(false);

    q1->addLists();

    Quest* q2 = new Quest("3. Mate 5 Boomers", 5);
    //q2->setActive(true);
    //q2->setComplete(true);
    q2->setActive(false);
    q2->setComplete(false);
    q2->addLists();

    Quest* q3 = new Quest("1. Pegue 1 energias.",1);
    //q3->setActive(true);
    //q3->setComplete(true);
    q3->setActive(false);
    q3->setComplete(false);
    q3->addLists();

    Quest* q4 = new Quest("4. Mate o mid-boss(grande slime).",1);
    //q4->setActive(true);
    //q4->setComplete(true);
    q4->setActive(false);
    q4->setComplete(false);
    q4->addLists();

    Quest* q5 = new Quest("Kill the Necromancer",1);
    //q4->setActive(true);
    //q4->setComplete(true);
    q5->setActive(false);
    q5->setComplete(false);
    q5->addLists();



/// FIM TESTES

    SpriteManager::SpriteControl.loadSprite("data/enemy/KaysTeste.png",SPRITE_PLAYER);
    SpriteManager::SpriteControl.loadSprite("data/enemy/Mercenario.png",SPRITE_BOOMER);
    //SpriteManager::SpriteControl.loadSprite("data/tileset/basic_tileset_32.png",SPRITE_TILESET);
    SpriteManager::SpriteControl.loadSprite("data/tileset/tile_Kays.png",SPRITE_TILESET);
    SpriteManager::SpriteControl.loadSprite("data/enemy/Mago1.png",SPRITE_SLIME_SIMPLE);
    SpriteManager::SpriteControl.loadSprite("data/enemy/Esqueleto.png",SPRITE_ESQUELETO);
    SpriteManager::SpriteControl.loadSprite("data/enemy/Mago2.png",SPRITE_MAGO_CORROMPIDO);



    SpriteManager::SpriteControl.loadSprite("data/enemy/npc1.png", SPRITE_NPC1);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc2.png", SPRITE_NPC2);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc3.png", SPRITE_NPC3);
    SpriteManager::SpriteControl.loadSprite("data/enemy/npc4.png", SPRITE_NPC4);

    //SDLBase::sfx.playMusic(PLAY_ORIENTAL);

    SpriteManager::SpriteControl.loadSprite("data/enemy/Boss.png", SPRITE_CYBORG_SLIME);

    if (!Map::MapControl.loadSprite(SpriteManager::SpriteControl.getSprite(SPRITE_TILESET))){
        printf("Nao carregou imagem de tileset\n");
    }

//    if(!Map::MapControl.loadBackground(sp_bg = new Sprite("data/bg/bg1.png"))){
//        printf("Nao carregou background\n");
//    }

     if(!Map::MapControl.loadBackground(sp_bg = new Sprite("data/bg/bg_lvl2.png"))){
        printf("Nao carregou background\n");
    }

    sp_player = SpriteManager::SpriteControl.getSprite(SPRITE_PLAYER);
    SpriteManager::SpriteControl.loadSprite("data/tiro/magiaStun.png", SPRITE_TIRO);
    SpriteManager::SpriteControl.loadSprite("data/tiro/animTerra.png", SPRITE_TERRA);
    SpriteManager::SpriteControl.loadSprite("data/tiro/melee.png", SPRITE_AR);
    SpriteManager::SpriteControl.loadSprite("data/tiro/fmagiaFogo.png", SPRITE_FOGO);
    SpriteManager::SpriteControl.loadSprite("data/tiro/magiaGelo.png", SPRITE_GELO);
    SpriteManager::SpriteControl.loadSprite("data/tiro/ball_32.png", SPRITE_BALL);

    sp_item = new Sprite("data/item/itens.png");
    sp_bar = new Sprite("data/interface/SandStorm_Coracao.png");

    sp_magiaFogo = new Sprite("data/interface/magiaFogo.png");
    sp_magiaGelo = new Sprite("data/interface/magiaGelo.png");


    InterfaceMenu::InterfaceControl.spriteSheet = sp_bar;
    InterfaceMenu::InterfaceControl.spriteFogo = sp_magiaFogo;
    InterfaceMenu::InterfaceControl.spriteGelo = sp_magiaGelo;

    Player::PlayerControl.resetPlayer();
    Player::PlayerControl.setPos(2*TILE_SIZE,11*TILE_SIZE);//32, 256);boss
    Player::PlayerControl.setSprite(sp_player,64,64);
    Player::PlayerControl.spr_tiroComum = SpriteManager::SpriteControl.getSprite(SPRITE_TIRO);
    Player::PlayerControl.spr_tiroTerra = SpriteManager::SpriteControl.getSprite(SPRITE_TERRA);
    Player::PlayerControl.spr_tiroAr =  SpriteManager::SpriteControl.getSprite(SPRITE_AR);
    Player::PlayerControl.spr_tiroFogo =  SpriteManager::SpriteControl.getSprite(SPRITE_FOGO);
    Player::PlayerControl.spr_tiroGelo = SpriteManager::SpriteControl.getSprite(SPRITE_GELO);

    Player::PlayerControl.setAnimation(100,8);
    //Player::PlayerControl.setCollisionBox(12,14,8,18);
    Player::PlayerControl.setCollisionBox(0,0,40,64);
    Player::PlayerControl.addToEntidadeList();

    ItemObject::spr_itens = sp_item;

    if(stack==3){

    Player::PlayerControl.setPos(2*TILE_SIZE, 11*TILE_SIZE);


        if(Map::MapControl.checkpointMap=="data/map/lvlBoss.map"){
            q5->setActive(true);
            Player::PlayerControl.setPos(1504, 704);
        }

        if(Map::MapControl.checkpointMap=="data/map/lvl4.map"){
            Player::PlayerControl.setPos(250*TILE_SIZE, 8*TILE_SIZE);
        }



        if (!Map::MapControl.loadMap(Map::MapControl.checkpointMap) )
            printf("Arquivo .map nao encontrado: data/map/Casa.map\n");

    }else

    if(stack == 1) {//faz load
        if (!Map::MapControl.loadMap("data/map/lvlBoss.map") )
            printf("Arquivo .map nao encontrado: data/map/lvl3.map\n");
        Save::loadGame();

        //Player::PlayerControl.setPos(2*TILE_SIZE, 11*TILE_SIZE);
        //Player::PlayerControl.setPos(250*TILE_SIZE, 8*TILE_SIZE); ///POSICAO LVL4
        Player::PlayerControl.setPos(1504, 704); ///POSICAO LVLBOSS
        q5->setActive(true);
    } else { // novo jogo
        if (!Map::MapControl.loadMap("data/map/lvl1.map") )
            printf("Arquivo .map nao encontrado: data/map/lvl1.map\n");

        Vetor p9(8,200);
        ItemObject* item = new ItemObject(p9,ITEM_TYPE_HP,22);
        item->addLists();

        cutscene.load(1);
        cutscene.stack = 1;
    }
    Camera::CameraControl.setTarget(&Player::PlayerControl.pos.x, &Player::PlayerControl.pos.y);
    Camera::CameraControl.targetMode = TARGET_MODE_CENTER;



}

void StateGame::destroyObjetos() {

    //===== Arruma erro de ponteiro de linux =======/
    Player::PlayerControl.removeLifeBarLists();

//Entidades
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
            if(Entidade::EntidadeList[i] != &Player::PlayerControl ) //Player não é deletado
                delete Entidade::EntidadeList[i];
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        delete Tiro::TiroList[i];
//Deleta instancias das Listas das interfaces
    for(unsigned int i = 0; i < LoopList.size(); i++)
        delete LoopList[i];
    for(unsigned int i = 0; i < DrawListBefore.size(); i++)
        delete DrawListBefore[i];
    for(unsigned int i = 0; i < DrawListAfter.size(); i++)
        delete DrawListAfter[i];

//Limpa listas
    LoopList.clear();
    DrawListBefore.clear();
    DrawListAfter.clear();
    Entidade::EntidadeList.clear();
    Tiro::TiroList.clear();

    //===== Arruma erro de ponteiro de linux =======/
    Player::PlayerControl.addLifeBarLists();
}
int StateGame::unload()
{
    destroyObjetos();
    //Deleta sprites
    delete sp_item;
    SpriteManager::SpriteControl.deleteSprite(SPRITE_BOOMER);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TILESET);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_PLAYER);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_SLIME_SIMPLE);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_ESQUELETO);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TIRO);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_TERRA);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_AR);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_FOGO);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_SLIME_GOD);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC1);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC2);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_NPC3);
    SpriteManager::SpriteControl.deleteSprite(SPRITE_MAGO_CORROMPIDO);
    //Deleta quests somente quando sair do jogo ou estado.
    for(unsigned int i = 0; i < Quest::QuestList.size(); i++)
        delete Quest::QuestList[i];
    Quest::QuestList.clear();
    SDLBase::sfx.stopMusic();
    return stack;
}

eStateType StateGame::update(unsigned int dt)
{
    if(cutscene.stack != 0) {
        eStateType estado = cutscene.update(dt);
        if(estado != GST_NONE)
        {
           cutscene.unload();
           cutscene.stack = 0;
        }else{
            return GST_NONE;
        }
    }
    static bool pause = false;

    if(pause) dt = 0;

    if(InputManager::getInstance()->isKeyDown(SDLK_p) || InputManager::getInstance()->getButtonState(0, 9)) pause = !pause;

    for(unsigned int i = 0; i < LoopList.size(); i++)
        LoopList[i]->update(dt);
///CALCULA POSIÇÃO
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        Entidade::EntidadeList[i]->update(dt);
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        Tiro::TiroList[i]->update(dt);
///EXECUTA COLISÕES
    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        Entidade::EntidadeList[i]->executaColisao();
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
        Tiro::TiroList[i]->executaColisao();

    Player::PlayerControl.handle_events();

    //Teleporta proximo mapa.... apaga entidades existentes
    if(Map::MapControl.isNextMap())
    {
        destroyObjetos();
        Player::PlayerControl.addToEntidadeList();
        Map::MapControl.loadNextMap();
        if(Map::MapControl.nextMapName == "data/map/lvlBoss.map")
              Quest::QuestList[4]->setActive(true);


        if(Map::MapControl.nextMapName == "data/map/lvl2.map"){
            cutscene.load(2);
            cutscene.stack = 2;
        }else
        if(Map::MapControl.nextMapName == "data/map/lvl3.map"){
            cutscene.load(3);
            cutscene.stack = 3;
        }else
        if(Map::MapControl.nextMapName == "data/map/lvl4.map"){
            cutscene.load(4);
            cutscene.stack = 4;
        } else
        if(Map::MapControl.nextMapName == "data/map/lvlBoss.map"){
            cutscene.load(5);
            cutscene.stack = 5;
        }


    }

///VERIFICA DERROTA
    if(((Player::PlayerControl.dead == true) && (Player::PlayerControl.an.isReady())) || ((Player::PlayerControl.an.getFrameY()==8) && (Player::PlayerControl.morte.is_started()))){
        stack = -1;
        return GST_WINLOSE;
    }
///VERIFICA VITORIA
    unsigned int n = 0;
    for(unsigned int i = 0; i < Quest::QuestList.size();i++){
        //Se não ativa e completada... fez a quest e entregou.... vence!
        if(Quest::QuestList[i]->isActive() == false && Quest::QuestList[i]->isCompleted() == true){
            n++;
        }
    }
    //cout << timerDead.getTime() << endl;
    if(timerDead.getTime() > 3000) {
        stack = 1;
        return GST_WINLOSE;
    }
    if(Quest::QuestList[4]->isCompleted() == true){
            if(timerDead.is_started() == false) {
                timerDead.start();
            }
        }

    if (n >= Quest::QuestList.size()){
        stack = 1;
        return GST_WINLOSE;
    }
//FIM

    for(unsigned int i = 0; i < EventList.size(); i++) {
      //  if(EventList[i]->isActive()) {

        //}
    }

    return GST_NONE;
}
void StateGame::render()
{
    if(cutscene.stack != 0) {
        cutscene.render();
        return;
    }
    Map::MapControl.render(0,0);

    for(unsigned int i = 0; i < DrawListBefore.size(); i++)
        DrawListBefore[i]->render();

    for(unsigned int i = 0; i < Entidade::EntidadeList.size(); i++)
        if(Entidade::EntidadeList[i] != &Player::PlayerControl ) //Garante que player é o ultimo a ser desenhado.
            Entidade::EntidadeList[i]->render();
    for(unsigned int i = 0; i < Tiro::TiroList.size(); i++)
            Tiro::TiroList[i]->render();

    Player::PlayerControl.render();

    //somente para testar se a posição está correta.
    for(unsigned int i = 0; i < Teleporte::TeleporteList.size(); i++)
        Teleporte::TeleporteList[i]->render();

    Map::MapControl.renderLastLayer(0,0);


    for(unsigned int i = 0; i < DrawListAfter.size(); i++)
        DrawListAfter[i]->render();

    InterfaceMenu::InterfaceControl.render();

    //menu.render();
}

