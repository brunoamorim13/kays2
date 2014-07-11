#include "map.h"


#include "inimigo.h"
#include "npc.h"
#include <algorithm> // usado para std::replace

Map Map::MapControl;


Map::Map()
{
    tileset = NULL;
    background = NULL;
    map_height = map_width = 0;
    LayerList.clear();
    nextMap = false;

    background = NULL;

    clipMap.w = SCREEN_WIDTH;
    clipMap.h = SCREEN_HEIGHT;
    paralax_x = 0.5;
    paralax_y = 0.7;
    isParalax = true;
}
Map::~Map()
{
    destroyMap();
    if(background != NULL)
        delete background;
}
void Map::destroyMap()
{
    map_width = map_height = 0;
    for(unsigned int i = 0; i < LayerList.size(); i++) {
        delete LayerList[i]; //Chama desconstrutor de ~Sprite, que deleta a surface.
    }
    LayerList.clear();
    //Exclui teleportes existentes
    for(unsigned int i = 0; i < Teleporte::TeleporteList.size();i++){
        //delete Teleporte::TeleporteList[i];
    }
    Teleporte::TeleporteList.clear();
}

void Map::setMap(std::string map)
{
    nextMap = true;
    nextMapName = map;

}
bool Map::isNextMap(){ return nextMap;}

void Map::loadNextMap()
{
    if(Player::PlayerControl.getHP() < 3){

        Player::PlayerControl.setHP(3);
        Player::PlayerControl.setHPMax(3);

    }


        if (!loadMap(nextMapName) )
            printf("Arquivo .map nao encontrado: %s\n", nextMapName.c_str());
        nextMap = false;
}

bool Map::loadMap(std::string filename)
{
    destroyMap();

    if(filename == "data/map/lvl2.map"){
        Player::PlayerControl.setAgua(99);
        Vetor p9(42*32,68*32);
        ItemObject* item = new ItemObject(p9,ITEM_TYPE_HP,1);
        item->addToDrawListBefore();
        item->addToLoopList();
    }



    if(filename == "data/map/lvl3.map")
        Player::PlayerControl.setAgua(99);


    if(filename == "data/map/lvl4.map"){
        Player::PlayerControl.setAgua(99);
        Player::PlayerControl.setFogo(99);
    }



   if(filename == "data/map/lvlBoss.map"){
        Player::PlayerControl.setFogo(99);
        Player::PlayerControl.setAgua(99);

        Vetor p9(3*32,3*32);
        ItemObject* item = new ItemObject(p9,ITEM_TYPE_HP,1);
        item->addToDrawListBefore();
        item->addToLoopList();

        Vetor p10(47*32,3*32);
        ItemObject* heart = new ItemObject(p10,ITEM_TYPE_HP,1);
        heart->addToDrawListBefore();
        heart->addToLoopList();
    }



    std::ifstream myfile;
    myfile.open(filename.c_str());

    checkpointMap = filename;

    if(myfile.is_open() == false){
        printf("Nao foi possivel abrir o arquivo: %s.\n", filename.c_str());
        return false;
    }

    std::string tileset_path;

    myfile >> tileset_path;

    int is_background = 0;
    myfile >> is_background;
    if(is_background == 1){
        std::string background_path;
        myfile >> background_path;
        Sprite* sp = new Sprite(background_path.c_str());
        loadBackground(sp);
        myfile >> paralax_x >> paralax_y;
    }else {
        if(background)
            delete background;
        background = NULL;
    }

    if(tileset != NULL) {
        SpriteManager::SpriteControl.deleteSprite(SPRITE_TILESET);
        tileset = NULL;
    }

    SpriteManager::SpriteControl.loadSprite(tileset_path.c_str(), SPRITE_TILESET);

    tileset = (SpriteManager::SpriteControl.getSprite(SPRITE_TILESET) );

    if(tileset == NULL) {
        printf("Erro ao carregar tileset: %s.\n", tileset_path.c_str());
        return false;
    }

    int layer_width, layer_height;

    myfile >> layer_width;
    myfile.ignore(20,'-');
    myfile >> layer_height;


    //Ajusta o maior tamanho do mapa
    if(layer_width > map_width) map_width = layer_width;
    if(layer_height > map_height) map_height = layer_height;


    for(int tilemapID = 0; tilemapID < MAP_MAX_LAYER; tilemapID++)
    {
        Layer* tempLayer = new Layer(tileset);

        //Ajusta tamanho do layer
        tempLayer->TileList.resize(layer_width);
        for (unsigned int x = 0; x < tempLayer->TileList.size(); x++)
            tempLayer->TileList[x].resize(layer_height);

        for (int y = 0; y < layer_height; y++)
        {
            for (int x = 0; x < layer_width; x++)
            {   // Le Tiles e joga-os no TileList
                Tile tempTile;
                myfile >> tempTile.id; myfile.ignore(1,':');
                myfile >> tempTile.tipo;
                if(tempTile.tipo == TILE_TIPO_SLOPE){
                    myfile.ignore(1,'(');
                    myfile >> tempTile.leftOffset;
                    myfile.ignore(1,':');
                    myfile >> tempTile.rightOffset;
                    myfile.ignore(1,')');
                }

                tempLayer->TileList[x][y] = tempTile;
            }

        }
        myfile.ignore(20,'\n');
        //Faz o sprite do com o layer
        //É inefetivo fazer layer comparado a tiles separados... Retirado para economizar memória
        ///empLayer->makeLayer();
        LayerList.push_back(tempLayer);
    }
///Cria teleportes do mapa
    std::string str;
    int tx, ty, tw, th, tdx, tdy;
    while (myfile.eof() == false) //Le a linha
    {
        myfile >> str;
        if(strcasecmp(str.c_str(), "Musica:") == 0)
            break;
        myfile >> tx; myfile.ignore(3,',');
        myfile >> ty; myfile.ignore(3,',');
        myfile >> tw; myfile.ignore(3,',');
        myfile >> th; myfile.ignore(3,',');
        myfile >> tdx; myfile.ignore(3,',');
        myfile >> tdy;

        Teleporte* t = new Teleporte(str.c_str(),tx,ty,tw,th,tdx,tdy);
        t->addLists();

    }
    //Confirma que saio por achar musica e não por fim do arquivo.
    if(strcasecmp(str.c_str(), "Musica:") == 0){
        if(myfile >> tx){//Pega musica a ser tocada;
            SDLBase::sfx.playMusic((MusicPlayList)tx);
            }
    }
    myfile.close();

///CARREGA npc e inimigos do mapa
    std::string line;
    std::string token;
    std::istringstream tokenizer;
    std::stringstream text;
    std::stringstream fileEnemy;

    /// Carrega NPCs
    tokenizer.str(filename);
    getline(tokenizer, token, '.');
    fileEnemy.str(token + ".npc");
    myfile.open(fileEnemy.str().c_str());

    while(myfile.eof() == false && myfile.is_open())
    {
        int ix, iy, sp_n, frameW, frameH, n_quest, off;
        std::string nome;
        myfile >> ix >> iy  >> sp_n >> frameW >> frameH >> n_quest >> nome >> off;
        std::replace(nome.begin(), nome.end(), '_',' ');
        NPC* temp = new NPC();
        temp->setPos(ix,iy);
        if(sp_n != -1){
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH );
        } else{
            temp->setSprite(SpriteManager::SpriteControl.getSprite(SPRITE_NPC1), frameW, frameH );
            temp->setFrames(3,1);
        }
        temp->setQuest(n_quest);
        if(nome.compare("-1") == false)
            temp->setNome(" ");
        else
            temp->setNome(nome);
        temp->setOffsetXMinus(off);
        getline(myfile, line); //Pula a linha;

        int last;
        while( getline(myfile, line) ){
            if(line.find("End:") != std::string::npos){ //Se achar End: termina NPC
                break;
            }

            if(line.find("initialPage:") != std::string::npos){ // se achar Page: cria nova pagina
               temp->startTxt.addPage();
               last=0;
               continue;
            }
            if(line.find("progressPage:") != std::string::npos){ // se achar Page: cria nova pagina
               temp->progressTxt.addPage();
               last=1;
               continue;
            }
            if(line.find("endPage:") != std::string::npos){ // se achar Page: cria nova pagina
               temp->doneTxt.addPage();
               last=2;
               continue;
            }
            switch(last){
                case 0:
                  temp->startTxt.addText(line.c_str());
                  break;
                case 1:
                    temp->progressTxt.addText(line.c_str());
                  break;
                case 2:
                    temp->doneTxt.addText(line.c_str());
                  break;
            }
        }
        temp->chat=temp->startTxt;
        temp->addToEntidadeList();
    }
    myfile.close();
///Carrega INIMIGOS do mapa



    tokenizer.str(filename);
    getline(tokenizer, token, '.');

    fileEnemy << token << ".enemy";
    std::string arquivo(fileEnemy.str());
    myfile.open(fileEnemy.str().c_str());



    while(myfile.eof() == false && myfile.is_open())
    {
        int ix,iy,velx, sp_n, delay, n_frame, frameW, frameH;//,boxX, boxY, boxW, boxH;
        myfile >> ix >> iy >> velx >> sp_n >> frameW >> frameH >> delay >> n_frame;
        InimigoBase* temp;
        if(sp_n != 3 && sp_n != 8){
            temp = new InimigoBase();
        } else if(sp_n == 3){
            temp = new InimigoBoss();
        } else if(sp_n == 8){
            temp = new InimigoLastBoss();
        }
        temp->setPos(ix, iy);
        temp->maxVel.x = velx;
        if(sp_n == 1){ // EH MAGO AZUL
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,12, frameW, frameH-2-12 );
            temp->typeInimigo = 1;
        }
        else if(sp_n == 0){ // EH MERCENARIO
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,0, frameW, frameH-1 );
            temp->HPMax = 15;
            temp->HP = 15;
        } else if(sp_n == 3) { // EH SLIME_GOD
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,32, frameW, frameH-5-32 );
        } else if(sp_n == 8) { // EH CYGORG SLIME
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,12, frameW, frameH-2-12 );
        }else if(sp_n == 2){//EH ESQUELETO
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,12, frameW, frameH-2-12 );
            temp->HPMax = 10;
            temp->HP = 10;
            temp->typeInimigo = 0;
        }else if(sp_n == 17){// amgo corrompido
            temp->setSprite(SpriteManager::SpriteControl.getSprite(sp_n), frameW, frameH,0,12, frameW, frameH-2-12 );
            temp->HPMax = 20;
            temp->HP = 20;
            temp->typeInimigo = 17;
        }
        temp->setAnimation(delay, n_frame);
        temp->addToEntidadeList();

    }
    myfile.close();

    return true;
}

bool Map::loadSprite(Sprite* sp)
{
    tileset = sp;
    return tileset->isSprite();
}
bool Map::loadBackground(Sprite* sp)
{
    if(background)
        delete background;

    background = sp;
    return background->isSprite();
}

void Map::render(int mapX, int mapY, bool isLayerImg)
{
    if ( tileset == NULL )
        return;

    //Renderiza background
    if (background != NULL){
        float dx = Camera::CameraControl.getX();
        float dy = Camera::CameraControl.getY();
        if(isParalax){
            dx *= paralax_x;
            dy *= paralax_y;
        }
        background->render(mapX-dx, mapY-dy, NULL);
    }

    for(unsigned int layerID = 0; layerID < LayerList.size()-1;layerID++)
        if(isLayerImg == false){
            LayerList[layerID]->render(mapX, mapY);
            }
        else{
            clipMap.x = +Camera::CameraControl.getX();
            clipMap.y = +Camera::CameraControl.getY();
            LayerList[layerID]->renderLayer(mapX, mapY, &clipMap);
        }
}

void Map::renderLastLayer(int mapX, int mapY, bool isLayerImg)
{
    if ( tileset == NULL )
        return;

    unsigned int layerID = LayerList.size()-1;
    if(isLayerImg == false){
        LayerList[layerID]->render(mapX, mapY);
        }
    else{
        clipMap.x = +Camera::CameraControl.getX();
        clipMap.y = +Camera::CameraControl.getY();
        LayerList[layerID]->renderLayer(mapX, mapY, &clipMap);
    }
}

// Retorna Tile no (x,y) da tela independente da camera.
// Layer inicial 1
Tile* Map::getTileFromPos(int x, int y, int layer)
{
    if (layer > (int)LayerList.size() || layer <= 0)
    {
        printf("Layer nao encontrado: layer %d", layer);
        return NULL;
    }

    if(x < 0 || x >= LayerList[layer-1]->getSizeX()) {
        printf("X fora das bordas: layer %d, x: %d, y: %d", layer, x, y);
    	return NULL;
    } else
    if(y < 0 || y >= LayerList[layer-1]->getSizeY()) {
        printf("Y fora das bordas: layer %d, x: %d, y: %d", layer, x, y);
        return NULL;
    }

    return &LayerList[layer-1]->TileList[x][y];
}

//Pega o Tile* pelo index x, y
Tile* Map::getTileFromIndex(int x, int y, int layer)
{
     if (x >= LayerList[layer-1]->getSizeX() || y >= LayerList[layer-1]->getSizeY()) {
        return NULL;
    }
    if (x < 0 || y < 0) {
        return NULL;
    }
    /* caso seja somente 1 vetor
    unsigned int ID = 0;
    ID = y*map_width;
    ID += x;
    */


    return &LayerList[layer-1]->TileList[x][y];
}

void Map::Layer::makeLayer()
{
    int tilesetWidth = layerTileset->getWidth() / TILE_SIZE;
    unsigned int layer_height = getSizeY();
    unsigned int layer_width = getSizeX();

    //Cria um SpriteLayer com o tamanho igual ao mapa
    spLayer.createLayer(layer_width*TILE_SIZE, layer_height*TILE_SIZE);

    for(unsigned int y = 0;y < layer_height; y++) {
        for(unsigned int x = 0;x < layer_width; x++) {

            if ( TileList[x][y].tipo == TILE_TIPO_NENHUM )
            {
                continue;
            }

            // Lugar da tela aonde aplicar a imagem
            int destX = (x * TILE_SIZE);
            int destY = (y * TILE_SIZE);

            SDL_Rect clip;
            // Qual tile cortar dependendo do TileID
            clip.x = (TileList[x][y].id % tilesetWidth) * TILE_SIZE;
            clip.y = (TileList[x][y].id / tilesetWidth) * TILE_SIZE;
            // Tamanho do pedaço a cortar
            clip.h = TILE_SIZE;
            clip.w = TILE_SIZE;
            //int tempX = destX - Camera::CameraControl.getX();
            //int tempY = destY - Camera::CameraControl.getY();

            // Adicionar verificação caso esteja fora da tela ??
            spLayer.applySprite(layerTileset, destX, destY, &clip);
        } //FIM X
    } //FIM Y
}

//----------------------------------------------------------------------------------
// Rederiza layer após processar quais tiles deverão ou não ser impressos.
//----------------------------------------------------------------------------------
void Map::Layer::render(int mapX, int mapY)
{
    if (layerTileset == NULL) return;
    // Calcula o numeros de tiles horizontal
    int tilesetWidth = layerTileset->getWidth() / TILE_SIZE;

    unsigned int layer_height = TileList[0].size();
    unsigned int layer_width = TileList.size();
    for(unsigned int y = 0;y < layer_height; y++) {
        for(unsigned int x = 0;x < layer_width; x++) {

            if ( TileList[x][y].tipo == TILE_TIPO_NENHUM )
            {
                continue;
            }

            // Lugar da tela aonde aplicar a imagem
            int destX = mapX + (x * TILE_SIZE);
            int destY = mapY + (y * TILE_SIZE);

            SDL_Rect clip;
            // Qual tile cortar dependendo do TileID
            clip.x = (TileList[x][y].id % tilesetWidth) * TILE_SIZE;
            clip.y = (TileList[x][y].id / tilesetWidth) * TILE_SIZE;
            // Tamanho do pedaço a cortar
            clip.h = TILE_SIZE;
            clip.w = TILE_SIZE;

            // Adicionar verificação caso esteja fora da tela ??
            layerTileset->render(destX - Camera::CameraControl.getX(), destY - Camera::CameraControl.getY(), &clip);
        } //FIM X
    } //FIM Y
}

//----------------------------------------------------------------------------------
// Rederiza layer como uma imagem toda, evita o processamento dos tiles
//----------------------------------------------------------------------------------
void Map::Layer::renderLayer(int mapX, int mapY, SDL_Rect* clip)
{
    if (layerTileset->isSprite() == false) return;
    if (spLayer.isSprite() == false) return;
     spLayer.render(mapX, mapY, clip);//(mapX-Camera::CameraControl.getX(), mapY-Camera::CameraControl.getY(), clip);
}


