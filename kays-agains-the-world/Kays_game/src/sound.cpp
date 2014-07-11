//==============================================================================
/*
    Classe responsavel por operações de música e sons.

    Declara variáveis globais:
extern Sound sfx;           --> Utilizada para reproduzir músicas e sons.


*/
//==============================================================================
#include "sound.h"

//Declaração da variável global sfx.
Sound sfx = Sound::getInstance();

Sound* Sound::instance;

Sound& Sound::getInstance()
{
    if (!instance)
    {
        instance = new Sound();
        instance->init();
    }

    return *instance;
}

//------------------------------------------------------------------------------
//          LISTA DE SONS A SEREM CARREGADOS. Define em sound.h
//------------------------------------------------------------------------------
void Sound::loadAllSounds()
{
    //Musicas
    loadMusic(MUSIC_LOAD_PIANO);
    loadMusic(MUSIC_LOAD_ORIENTAL);
    loadMusic(MUSIC_LOAD_DAY);
    loadMusic(MUSIC_LOAD_TRIBAL);
    loadMusic(MUSIC_LOAD_ORCHEST);
    loadMusic(MUSIC_LOAD_BOSS);
    loadMusic(MUSIC_LOAD_DERROTA);
    loadMusic(MUSIC_LOAD_VITORIA);

    //Effects
    loadSfxWAV(EFFECT_LOAD_MELEE);
    loadSfxWAV(EFFECT_LOAD_MAGIAFOGO);
    loadSfxWAV(EFFECT_LOAD_MAGIAGELO);
    loadSfxWAV(EFFECT_LOAD_MAGIASTUN);
    loadSfxWAV(EFFECT_LOAD_JUMP);

    loadSfxWAV(EFFECT_LOAD_DANO);
    loadSfxWAV(EFFECT_LOAD_MORTEBOSS);
    loadSfxWAV(EFFECT_LOAD_MORTEKAYS);
    loadSfxWAV(EFFECT_LOAD_MENU);
    loadSfxWAV(EFFECT_LOAD_DANOINIMIGO);
    loadSfxWAV(EFFECT_LOAD_MORTEMAGO);
    loadSfxWAV(EFFECT_LOAD_MORTEMERCENARIO);
}


// Inicia o módulo de som do SDL -----------------------------------------------
bool Sound::init()
{
    //22050 frequencia recomendada, 2 canais, 4096 tamanho do sample(buffer?), somente .wav
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }
    else
    {
        return true;
    }
}
// Fecha todos os Sons ---------------------------------------------------------
void Sound::closeSound()
{
    unloadMusic();
    unloadSfx();

    Mix_CloseAudio();
}
// Destructor ------------------------------------------------------------------
Sound::~Sound()
{
}

//------------------------------------------------------------------------------
//                          METODOS DE MUSICA
//------------------------------------------------------------------------------

//==============================================================================
// Carrega sons para a lista. Chamado internamente em init
void Sound::loadMusic(char* filename)
{
    //Carrega musica
    Mix_Music* temp = Mix_LoadMUS( filename );

    if ( temp == NULL )
    {
        printf("Erro ao carregar musica %s \n Arquivo nao encontrado?\n", filename);
    }
    else
    {
        music_list.push_back(temp);
    }

}

//==============================================================================
// Descarrega todas as musicas
void Sound::unloadMusic()
{
    int size = music_list.size();
    for(int i = 0; i < size; i++)
    {
        Mix_FreeMusic(music_list[i]);
    }
}

//==============================================================================
// Toca a música. Recebe um enum.
void Sound::playMusic(MusicPlayList ID)
{
    Mix_HaltMusic();
    int temp = Mix_PlayMusic( music_list[ID], -1);
    //Toca SDL_Mixer* carregada, -1 infinito, 0 para, ou x vezes
    if (temp == -1)
    {
        printf("Erro ao tocar musica: %d", ID);
    }
}
//==============================================================================
// Para de tocar a musica
void Sound::stopMusic()
{
    Mix_HaltMusic();
}
//------------------------------------------------------------------------------
//                          METODOS DE SFX
//------------------------------------------------------------------------------

//==============================================================================
// Carrega sons para a lista. Chamado internamente em init
void Sound::loadSfxWAV(char* filename)
{
    //Carrega musica
    Mix_Chunk* temp = Mix_LoadWAV(filename);

    if ( temp == NULL )
    {
        printf("Erro ao carregar sound effect %s \n Arquivo nao encontrado?\n", filename);
    }
    else
    {
        sfx_list.push_back(temp);
    }

}

//==============================================================================
// Descarrega todos os efeitos de som
void Sound::unloadSfx()
{
    int size = sfx_list.size();
    for(int i = 0; i < size; i++)
    {
        Mix_FreeChunk(sfx_list[i]);
    }
}

//==============================================================================
// Toca o efeito de som. Recebe um enum.
int Sound::playSfx(EffectPlayList ID)
{
    int retorno = -1;
    // -1 infinito, 0 = 1, 1 = 2, ...
    //primeiro valor para canal em que vai ser tocado se -1
    if( (retorno = Mix_PlayChannel(-1, sfx_list[ID], 0) )==-1)
    {
         printf("Erro ao tocar efeito de som: %d", ID);
    }

    return retorno;
}
//==============================================================================
// Para de tocar o sfx
void stopSfx(int ID)
{
    Mix_HaltChannel(ID);
}





