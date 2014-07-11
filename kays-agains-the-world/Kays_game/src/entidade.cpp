#include "entidade.h"
#include "personagem.h"
#include "inimigo.h"

std::vector<Entidade*> Entidade::EntidadeList;

Entidade::Entidade() : GameObject::GameObject()
{
    pos.x = 0;
    pos.y = 0;
    vel.x = vel.y = acel.x = acel.y = 0;
    maxVel.x = maxVel.y = 10;
    col_offset.x = col_offset.y = col_offset.w = col_offset.h = 0;
    flags = ENTIDADE_FLAG_NENHUM;
    gravity_speed = walking_aceleration = stop_aceleration = 0;
    showCollision = true;
    extVel.x = extVel.y = 0;
    dead = false;
}
Entidade::Entidade(float x, float y) : GameObject::GameObject(x,y)
{
    pos.x = x;
    pos.y = y;
    vel.x = vel.y = acel.x = acel.y = 0;
    maxVel.x = maxVel.y = 10;
    col_offset.x = col_offset.y = col_offset.w = col_offset.h = 0;
    flags = ENTIDADE_FLAG_NENHUM;
    gravity_speed = walking_aceleration = stop_aceleration = 0;
    showCollision = true;
    extVel.x = extVel.y = 0;
    dead = false;
}
Entidade::~Entidade(){}
void Entidade::render()
{
    //if(dead) return;
    float posX = pos.x - Camera::CameraControl.getX();
    float posY = pos.y - Camera::CameraControl.getY();
    an.render(posX, posY);
    if(showCollision) {
        boxRGBA(SDLBase::getScreen(),
                    posX+col_offset.x, posY+col_offset.y,
                    posX+col_offset.x+col_offset.w, posY+col_offset.y+col_offset.h,
                    200, 0, 0, 50 );
    }
}
void Entidade::update(unsigned int dt)
{
    if(dead) return;
    an.update(dt);
    float tempo = float(dt)*0.001f;
    if(flags & ENTIDADE_FLAG_FISICA) {
        acel.y = gravity_speed;
    }
    vel = vel + (acel * tempo * TILE_SIZE );
    //Se certifica que não é maior que a velocidade máxima, forças externas não são consideradas.
    if (vel.x > maxVel.x)   {vel.x = maxVel.x;}
    if (vel.x < -maxVel.x)  {vel.x = -maxVel.x;}
    if (vel.y > maxVel.y)   {vel.y = maxVel.y;}
    if (vel.y < -maxVel.y)  {vel.y = -maxVel.y;}

    Vetor realVel = (vel+extVel) * tempo;//Vetor vel0 = vel;acel*pow(tempo,2)*0.5 + vel0*tempo;

    move(realVel.x, realVel.y);

    extVel.x = extVel.y = 0;

}


//=============================================================
// Faz o movimento por iterações
//-------------------------------------------------------------
void Entidade::move(float moveX, float moveY)
{

    canDoJump = false;

    float newX = 0;
    float newY = 0;
    // A cada iteração irá testar colisões para os novos X e Y independentemente,
    //caso haja colisão, zera a velocidade naquele eixo
    while(true) {
        // Pega valores para newX e newY
        // Caso move seja maior doq 1, o incremento de teste será 1
        // Caso seja menor, o incremento será o próprio valor
        if(moveX != 0) {
            if(moveX > 1)
                newX = 1;
            else
            if(moveX < -1)
                newX = -1;
            else
                newX = moveX;
        }

        if(moveY != 0) {
            if(moveY > 1)
                newY = 1;
            else
            if(moveY < -1)
                newY = -1;
            else
                newY = moveY;
        }
        //Decrementa moveXY pelo newXY utilizado
        moveX += -newX;
        moveY += -newY;

        if(isValidPosition((int)(pos.x+newX),(int)(pos.y), newX, 0 ) )
            pos.x += newX;
        else {
            onNotValidPosition(true);
            newX = 0;
        }

        if(isValidPosition((int)(pos.x), (int)(pos.y+newY), 0, newY ) )
            pos.y += newY;
        else {
            if(vel.y > 0) {
                canDoJump = true;
            } else {
                jumpTimer.stop();
            }
            onNotValidPosition(false);
            newY = 0;
        }

        if(newX > 0 && moveX <= 0) newX = 0;
        if(newX < 0 && moveX >= 0) newX = 0;
        if(newY > 0 && moveY <= 0) newY = 0;
        if(newY < 0 && moveY >= 0) newY = 0;

        if (moveX == 0) newX = 0;
        if (moveY == 0) newY = 0;


        if(moveX == 0 && moveY 	== 0) 	break;//Retirar? somente o de baixo ja é suficiente?
		if(newX  == 0 && newY 	== 0) 	break;
    }
}
void Entidade::onNotValidPosition(bool isX){
    if(isX)
        vel.x = 0;
    else
        vel.y = 0;
}
//=============================================================
// Retorna se colide caso ESTE objeto esteja em XY
//-------------------------------------------------------------
bool Entidade::isColisaoEntidade(Entidade* objeto, int posX, int posY)
{

    //Não é o mesmo objeto e não é nulo
    //Não é morto
    // É colisão
    if(this != objeto && objeto != NULL && !objeto->dead &&
       (objeto->flags & ENTIDADE_FLAG_MAP_ONLY) != ENTIDADE_FLAG_MAP_ONLY  && (objeto->flags & ENTIDADE_FLAG_NPC) != ENTIDADE_FLAG_NPC &&
        this->isInvencible() == false && objeto->isInvencible() == false &&
       objeto->isColisaoRetangulo(posX + col_offset.x, posY + col_offset.y, col_offset.w, col_offset.h))
       {
           setColisao(objeto);
           objeto->setColisao(this);
           //Se um dos objetos for somente colisão, posição valida, independente
           if(this->isFlag(ENTIDADE_FLAG_MAP_ONLY_COLIDE) || objeto->isFlag(ENTIDADE_FLAG_MAP_ONLY_COLIDE) )
                return false;

           return true;
       }
    return false;
}
//=============================================================
// Retorna se o triangulo colide com ESTA entidade.
//-------------------------------------------------------------
bool Entidade::isColisaoRetangulo(float fX, float fY, float fW, float fH)
{
    int baixo1 = pos.y + col_offset.y + col_offset.h;
    int esquerda1 = pos.x + col_offset.x;
    int direita1 = pos.x + col_offset.x + col_offset.w;
    int cima1 = pos.y + col_offset.y;

    int baixo2 = fY + fH;
    int esquerda2 = fX;
    int direita2 = fX + fW;
    int cima2 = fY;

    if (
        !(baixo1 < cima2) &&
        !(cima1 > baixo2) &&
        !(direita1 < esquerda2) &&
        !(esquerda1 > direita2)
        )
        {
            return true;
        }

    return false;
}

//=============================================================
// Retorna se o Tile é valido
//-------------------------------------------------------------
bool Entidade::isValidTile(Tile* tile)
{
    if (tile == NULL)
        return false;
    if(tile->tipo == TILE_TIPO_BLOCO)
        return false;

    return true;
}
//=================================================================
//  Primeiramente pega os indexes dos tiles que estão em contato com a área de colisão da entidade
//caso seja um bloco retorna false (precisa ajustar para tiles custom)
//
//  Depois chama isColisaoEntidade com todas as entidades para verificar se há colisões com entidades
//este método já seta as colisões
bool Entidade::isValidPosition(int newX, int newY, float goX, float goY)
{
    bool Return = true;

    //Pega indexes dos Tiles que precisam ser testados
    int startX =(newX + col_offset.x) / TILE_SIZE;
    int startY =(newY + col_offset.y) / TILE_SIZE;
    int endX = ( newX + col_offset.x + col_offset.w -1 ) / TILE_SIZE;
    int endY =( newY + col_offset.y  + col_offset.h - 1) / TILE_SIZE;

    for(int iY = startY;iY <= endY;iY++) {
		for(int iX = startX;iX <= endX;iX++) {

            Tile* tile = Map::MapControl.getTileFromIndex(iX, iY);

            if (tile == NULL) {
                Return = false;
                continue;
            }
            if(tile->tipo == TILE_TIPO_BLOCO)
            {
                Return = false;
            }

            if(tile->tipo == TILE_TIPO_SPIKE){

                if(isFlag(ENTIDADE_FLAG_PLAYER)){

                    Personagem* p = (Personagem*)this;
                    p->takeDamage(5);
                }
                if(isFlag(ENTIDADE_FLAG_INIMIGO)){
                    if(isFlag(ENTIDADE_FLAG_BOSS)){
                        Return = false;
                    }else{
                        InimigoBase* in = (InimigoBase*)this;
                        in->takeDamage(5);
                    }

                }

                Return = false;
            }

            if(tile->tipo == TILE_TIPO_AGUA_FUNDO)
            {
                if(isFlag(ENTIDADE_FLAG_PLAYER))
                {
                    Personagem* p = (Personagem*)this;
                    p->vel.y = 5;
                    p->an.pauseAnimation(8);

                if(isFlag(ENTIDADE_FLAG_INIMIGO))
                {
                    InimigoBase* in = (InimigoBase*)this;
                    in->vel.y = 5;
                }


                }
            }

            if(tile->tipo == TILE_TIPO_AGUA_DANO){

                if(isFlag(ENTIDADE_FLAG_PLAYER)){

                    Personagem* p = (Personagem*)this;
                    p->takeDamage(1);
                }
                if(isFlag(ENTIDADE_FLAG_INIMIGO)){
                     InimigoBase* in = (InimigoBase*)this;
                     in->takeDamage(1);
                }

            }

            if(tile->tipo == TILE_TIPO_PLATAFORMA && isFlag(ENTIDADE_FLAG_TIRO_INIMIGO))
                continue;
            if(tile->tipo == TILE_TIPO_PLATAFORMA && goY > 0 &&
                                (newY+col_offset.y) < (iY*TILE_SIZE)-TILE_SIZE/2 )
                Return = false;
            /// Tipo especial, rampa.
            if(tile->tipo == TILE_TIPO_SLOPE)
            {
                ///Calcula o ponto Y, isto é, o offset da rampa e cima do tile da rampa.
                bool isUp = false;
                    tile->leftOffset > tile->rightOffset? isUp = true: isUp = false;

                int lry = (pos.y+col_offset.y+col_offset.h);
                int limitX = 0;

                if(isUp)
                    limitX = (int)(pos.x+col_offset.x+col_offset.w);
                else
                    limitX = (int)(pos.x+col_offset.x);

                float diff = abs(tile->rightOffset - tile->leftOffset);

                ///novo metodo, steps
                float stepX = diff/(float)TILE_SIZE;


                int inX = limitX -(iX*TILE_SIZE) ;
                //Só trata a borda direita estiver dentro do tile
                if(inX > TILE_SIZE)
                    continue;

                int pointY = 0;
                if(isUp){
                    //pointY = (float)(TILE_SIZE-inX)*(diff/(float)TILE_SIZE);
                    pointY = tile->leftOffset - inX*stepX;
                }
                else{
                    //pointY = (float)inX*(diff/(float)TILE_SIZE);
                    pointY = tile->leftOffset + inX*stepX;
                }


                ///Inicia tratamento
                //Se estiver indo para os lados
                if(goX != 0){
                    if(lry  > (iY*TILE_SIZE)+pointY ){
                        if(Return) { // Se ainda não tiver colidido com nada
                            if( !onRampHitX(newX,newY) )
                                Return = false;
                        }
                    }

                }

                if(goY > 0){

                    if( lry  > (iY*TILE_SIZE)+pointY ) {
                        if( !onRampHitY(newX,newY) )
                            Return = false;
                    }

                }
               // tile->




            }

			///if(isValidTile(tile) == false) {
			///	Return = false;
			///	break;
			///}
		}
	}

	if(this->flags & ENTIDADE_FLAG_MAP_ONLY){

	} else {
	    for(unsigned int i = 0; i < EntidadeList.size(); i++)
            if(isColisaoEntidade(EntidadeList[i], newX, newY) ) {
                //Se tiver a flag, registra a colisão, porém, não para o objeto.
                if(flags & ENTIDADE_FLAG_MAP_ONLY_COLIDE)
                    break;
                Return = false;
            }
	}

    if(this->flags & ENTIDADE_FLAG_COLIDE_ONLY)
        return true;
    else
        return Return;

}


//=====================================
// Retorna FALSE se causar colisão e parar movimento,
// TRUE para continuar a executar movimento. EX: Rampas escorregadias
bool Entidade::onRampHitX(int newX, int newY){
    if(isValidPosition(newX, newY-1,0,-1))
        pos.y -= 1;

    return true;
}
bool Entidade::onRampHitY(int newX, int newY){
    return false;
}

void Entidade::removeFromEntidadeList()
{
    for(unsigned int i = 0; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] == this)
            EntidadeList.erase(EntidadeList.begin()+i);
    }
}

void Entidade::addToEntidadeList()
{
    for(unsigned int i = 0; i < EntidadeList.size(); i++)
    {
        if (EntidadeList[i] == this)
            return;
    }

    EntidadeList.push_back(this);
}
void Entidade::setSprite(Sprite* sp_obj,int f_width, int f_height, int col_offsetX, int col_offsetY, int col_offsetW, int col_offsetH)
{
    col_offset.x = col_offsetX;
    col_offset.y = col_offsetY;
    if(!col_offsetW) col_offset.w = f_width;
        else col_offset.w = col_offsetW;
    if(!col_offsetH) col_offset.h = f_height;
        else col_offset.h = col_offsetH;
    an.setSprite(sp_obj, f_width, f_height);
    an.setFrames(0,1,0);
}

void Entidade::setAnimation(unsigned int delay, unsigned int n_frames)
{
    an.setFrames(an.getFrameX(),n_frames,delay);
}
void Entidade::setFrames(unsigned int clipX, unsigned int n_frame, unsigned int uDelay, bool onlyOnce)
{
    an.setFrames(clipX, n_frame, uDelay, onlyOnce);
}
void Entidade::setColisao(Entidade* ent)
{
    //verifica se já está presente
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
        if(entidadeColidida[i] == ent)
            return;
    colVel = vel;
    entidadeColidida.push_back(ent);
}

void Entidade::executaColisao()
{
    for(unsigned int i = 0; i < entidadeColidida.size(); i++)
    {
        ;
    }

    entidadeColidida.clear();
}

//---- Gera velocidades para direção X, aumenta maxVel de acordo -----
void Entidade::setDirecao(float graus, float velocidade)
{
    maxVel.x = maxVel.y = velocidade;
    vel.x = cos((graus*M_PI/180))*velocidade;
    vel.y = -sin((graus*M_PI/180))*velocidade;
}

bool Entidade::isFlag(int f){
    return ((flags & f) == f);
}


bool Entidade::isInvencible(){
    return invencible;
}
void Entidade::setInvencible(int delayInv){
    if (delayInv == 0) {
        invencible = false;return;}
    if (delayInv < 0) {
        invencible = true;return;}
//se ja estiver invencivel, não acumula nem restaura o tempo.
    if(timerInvencible.is_started() == true)
        return;
    tempoInvencible = delayInv;
    timerInvencible.start();
    invencible = true;
}
