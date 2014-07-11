//==============================================================================
/*
    Classe responsavel por operações de música e sons.

    Declara variáveis globais:
extern Sound sfx;           --> Utilizada para reproduzir músicas e sons.


*/
//==============================================================================

#ifndef _SOUND_H__
#define _SOUND_H__

///==========================================================
/// Musicas e sons carregados
#define MUSIC_LOAD_PIANO (char*)"data/music/bgm/kaysmenutheme.ogg"

#define MUSIC_LOAD_ORIENTAL (char*)"data/music/bgm/fase1.ogg"
#define MUSIC_LOAD_DAY (char*)"data/music/bgm/fase2.ogg"
#define MUSIC_LOAD_TRIBAL (char*)"data/music/bgm/fase3.ogg"
#define MUSIC_LOAD_BOSS (char*)"data/music/bgm/boss5.ogg"
#define MUSIC_LOAD_ORCHEST (char*)"data/music/bgm/fase4.ogg"
#define MUSIC_LOAD_DERROTA (char*)"data/music/bgm/gameover.ogg"
#define MUSIC_LOAD_VITORIA (char*)"data/music/bgm/victory.ogg"

enum MusicPlayList { PLAY_PIANO, PLAY_ORIENTAL, PLAY_DAY, PLAY_TRIBAL, PLAY_ORCHEST, PLAY_BOSS, PLAY_DERROTA, PLAY_VITORIA};


#define EFFECT_LOAD_MAGIASTUN (char*)"data/music/sfx/shot1.wav"
#define EFFECT_LOAD_MAGIAFOGO (char*)"data/music/sfx/fire.ogg"
#define EFFECT_LOAD_MAGIAGELO (char*)"data/music/sfx/ice.ogg"
#define EFFECT_LOAD_MELEE (char*)"data/music/sfx/stun.wav"
#define EFFECT_LOAD_JUMP (char*)"data/music/sfx/jump.wav"


#define EFFECT_LOAD_DANO (char*)"data/music/sfx/OUCH.ogg"
#define EFFECT_LOAD_MORTEBOSS (char*)"data/music/sfx/boss_death.ogg"
#define EFFECT_LOAD_MORTEKAYS (char*)"data/music/sfx/kays_morre.ogg"
#define EFFECT_LOAD_MENU (char*)"data/music/sfx/tumum.wav"
#define EFFECT_LOAD_DANOINIMIGO (char*)"data/music/sfx/ugh1.ogg"
#define EFFECT_LOAD_MORTEMAGO (char*)"data/music/sfx/ugh2.ogg"
#define EFFECT_LOAD_MORTEMERCENARIO (char*)"data/music/sfx/ugh3.ogg"



enum EffectPlayList {PLAY_SFX_STUN, PLAY_SFX_FOGO, PLAY_SFX_GELO, PLAY_SFX_MELEE, PLAY_SFX_JUMP, PLAY_SFX_DANO, PLAY_SFX_MORTEBOSS,  PLAY_SFX_MORTEKAYS,  PLAY_SFX_MENU,
  PLAY_SFX_DANOINIMIGO,  PLAY_SFX_MORTEMAGO,  PLAY_SFX_MORTEMERCENARIO};

/// Fim de musicas e sons
///==========================================================



#include "defines.h"
#include <vector>

#include <SDL/SDL_mixer.h>

class Sound
{
    private:
        static Sound *instance;
        Sound(){}

    public:
        ~Sound(); //Destructor
        static Sound& getInstance();

        bool init(); //Inicia modulo de musica e sons
        void closeSound();

        void unloadMusic();
        void unloadSfx();

    public:

        void loadAllSounds();
        void loadMusic(char* filename);
        void loadSfxWAV(char* filename);

        void playMusic(MusicPlayList ID);
        int  playSfx(EffectPlayList ID);

        void stopMusic();
        void stopSfx(int ID = -1);

    private:
    //Lista de músicas e sound effects carregados
        std::vector<Mix_Music*> music_list;
        std::vector<Mix_Chunk*> sfx_list;
};

//variavel global
extern Sound sfx;

#endif



