#include "dialoguewindow.h"

#include "player.h"

DialogueWindow::DialogueWindow()
{
    visible = false;
    index = -1;
    pos.x = 2*TILE_SIZE;
    pos.y=0;
    txtIndex = 0;


    nChar = 0;
    delayText = 50;
    timerText.start();

    nMsgPerPage = 3;

    offsetY = 0.0f;
    transition = false;
    isReady = false;

}
void DialogueWindow::render(){
    if (visible == false) return;
    isReady = false;

//Imprime caixa de texto
    int ix, iy;
    Player::PlayerControl.getRelativePos(ix,iy);

    if(iy > 11) {
        pos.y = 2*TILE_SIZE;
    } else {
        pos.y = 14*TILE_SIZE;
    }

    pos.x = 2*TILE_SIZE;
    SDL_Rect square;
    square.x = pos.x;
    square.y = pos.y;
    square.h = 3*TILE_SIZE + TILE_SIZE/2;
    square.w = 20*TILE_SIZE;
    SDLBase::gfx.renderFillRect(square, 0,0,0, 150);
    square.x+=2;square.y+=2;square.w-=4;square.h-=4;
    SDLBase::gfx.renderFillRect(square, 240,240,240, 150);
//Fim caixa texto
    square.y+=2;
    square.x+=2;

    if(InputManager::getInstance()->isKeyPressed(SDLK_x)){
        delayText = 10;
    } else{
        delayText = 50;
    }

    if(timerText.getTime() > delayText) {
        if(transition){
            offsetY -= 1;
        } else {
            nChar++;
        }
        timerText.start();
    }

    if(offsetY <= -20){
        offsetY = 0;
        transition = false;
        txtIndex++;
    }


    int printChars = nChar;
    square.y += TILE_SIZE/2;
    square.x += TILE_SIZE/2;

    for(int i = 0; i < txtIndex;i++)
        printChars -= msgList[index][i].msgEvent.size();

    for(int i = txtIndex; (i < txtIndex+nMsgPerPage) && ((unsigned int)i < msgList[index].size() ); i++) {

        if(printChars<=0) break;

        std::string txt;
        txt.append(msgList[index][i].msgEvent, 0, printChars);


        int txtSizeX = SDLBase::txt.applyText(square.x, square.y, 16,0,0,0, txt.c_str());


        //Se ultima pagina e todos carcteres printados, pode mudar pagina
        if((unsigned int)i == (msgList[index].size()-1) ) {
            if((unsigned int)printChars >= msgList[index][i].msgEvent.size()){
                isReady = true;
            }
        }

        printChars -= txt.size();

        if(msgList[index][i].isBreakLine){
            square.y+=20;
        }else {
            square.x += txtSizeX;
        }


    }


}
void DialogueWindow::update(unsigned int dt){



}
void DialogueWindow::addText(const char*pStr, ...){
    char stringText[128];
    va_list valist; // Informações das variaveis
    va_start(valist, pStr); // Inicia a lista de argumentos das variaveis
    vsprintf(stringText, pStr, valist); // Escreve os argumentos das variaveis formatados para um string
    va_end(valist); // Precisa ser executado para finalizar o processo

    std::string str = stringText;
    if(index < 0 || index > (int)msgList.size()){
        printf("Erro: Pagina inexistente.");
        return;
    }

    DialogueEvent txt;
    txt.msgEvent = str;
    txt.isEventCall = false; txt.imgID = -1; txt.txtDelay = -1;txt.isBreakLine = true; txt.isWaitKey = false;
    msgList[index].push_back(txt);
}
int DialogueWindow::nextPage(){
    if(isReady == false)
        return -1;
    if( ++index >=(int)msgList.size())
        index = 0;
    nChar = 0;
    txtIndex = 0;
    return index;
}
int DialogueWindow::nextText(){
    if(++txtIndex >=(int)msgList[index].size()){
        txtIndex = 0;
    } else {
        if(msgList[index][txtIndex-1].isBreakLine && index >= nMsgPerPage){
            transition = true;
            txtIndex--;
        }
    }
    if(transition)
        return txtIndex+1;

    return txtIndex;
}
void DialogueWindow::resetPage(){
    if(msgList.empty() == false)
        index = 0;
}
void DialogueWindow::addPage(){
    std::vector<DialogueEvent> pag;
    msgList.push_back(pag);
    index++;
}
void DialogueWindow::setPos(Vetor posicao)
{
    pos = posicao;
}
void DialogueWindow::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}

void DialogueWindow::addLists(){
    addToDrawListAfter();
    addToLoopList();
}
void DialogueWindow::removeLists()
{
    removeFromDrawList();
    removeFromLoopList();
}
void DialogueWindow::setVisible(bool activate){
    visible=activate;

}
bool DialogueWindow::isVisible(){
    return visible;
}




