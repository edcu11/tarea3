
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
#include<map>
#include<vector>
#include<string>

//SI LOS PERSONAJES SE TOCAN, REPRODUCIRA EL OTRO SONIDITO

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*character2;
SDL_Rect rect_background,rect_character, rect_character2;




int main( int argc, char* args[] )
{

    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }


    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }



    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje/down1.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0; rect_character.y = 100; rect_character.w = w; rect_character.h = h;

    character2 = IMG_LoadTexture(renderer, "charizard/cha2r.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character2.x = 430; rect_character2.y = 200; rect_character2.w = w; rect_character2.h = h;


    char orientation = 'd';// d u l r
    char ori2='d';
    int current_sprite = 0;
    int animation_velocity = 15;
    int velocity = 1;
    int velo=1, cont=1;
    int frame = 0;
    map<char,vector<SDL_Texture*> >charizard;
    charizard['u'].push_back(IMG_LoadTexture(renderer, "charizard/chau.png"));
    charizard['u'].push_back(IMG_LoadTexture(renderer, "charizard/cha1u.png"));
    charizard['u'].push_back(IMG_LoadTexture(renderer, "charizard/cha2u.png"));
    charizard['d'].push_back(IMG_LoadTexture(renderer, "charizard/cha.png"));
    charizard['d'].push_back(IMG_LoadTexture(renderer, "charizard/cha1d.png"));
    charizard['d'].push_back(IMG_LoadTexture(renderer, "charizard/cha2d.png"));
    charizard['l'].push_back(IMG_LoadTexture(renderer, "charizard/chal.png"));
    charizard['l'].push_back(IMG_LoadTexture(renderer, "charizard/cha1l.png"));
    charizard['l'].push_back(IMG_LoadTexture(renderer, "charizard/cha2l.png"));
    charizard['r'].push_back(IMG_LoadTexture(renderer, "charizard/char.png"));
    charizard['r'].push_back(IMG_LoadTexture(renderer, "charizard/cha1r.png"));
    charizard['r'].push_back(IMG_LoadTexture(renderer, "charizard/cha2r.png"));

    map<char,vector<SDL_Texture*> >sprites;
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up1.png"));
    sprites['u'].push_back(IMG_LoadTexture(renderer, "personaje/up2.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down1.png"));
    sprites['d'].push_back(IMG_LoadTexture(renderer, "personaje/down2.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left1.png"));
    sprites['l'].push_back(IMG_LoadTexture(renderer, "personaje/left2.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right1.png"));
    sprites['r'].push_back(IMG_LoadTexture(renderer, "personaje/right2.png"));

    SDL_Color color={255,255,255};

    TTF_Font *font= TTF_OpenFont("Sans.ttf", 24);
    SDL_Surface *ms=TTF_RenderText_Solid(font,"SOY TAN CHISTOSO",color);
    SDL_Texture *m= SDL_CreateTextureFromSurface(renderer, ms);
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0; //NO FUNCIONO EL TEXTO PROFE :,(

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2,2048);

    Mix_Music *cancion= Mix_LoadMUS("sea.mp3");
    Mix_Chunk *scream= Mix_LoadWAV("bip.wav");
    //Main Loop
    while(true)
    {

        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                TTF_Quit();
                return 0;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

        if(!Mix_PlayingMusic())
            Mix_PlayMusic(cancion,1);


//        TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size
//
//        SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
//
//        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
//
//        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
//

        if(currentKeyStates[ SDL_SCANCODE_L ])
        {
            rect_character2.x+=velocity;
            orientation='r';
        }
        if(currentKeyStates[ SDL_SCANCODE_J ])
        {
            rect_character2.x-=velocity;
            orientation='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_K ])
        {
            rect_character2.y+=velocity;
            orientation='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_I ])
        {
            rect_character2.y-=velocity;
            orientation='u';
        }
         //segunda imagen
         if(currentKeyStates[ SDL_SCANCODE_D ])
        {
            rect_character.x+=velo;
            ori2='r';
        }
         if(currentKeyStates[ SDL_SCANCODE_A ])
        {
            rect_character.x-=velo;
            ori2='l';
        }
        if(currentKeyStates[ SDL_SCANCODE_S ])
        {
            rect_character.y+=velo;
            ori2='d';
        }
        if(currentKeyStates[ SDL_SCANCODE_W ])
        {
            rect_character.y-=velo;
            ori2='u';
        }
        if(currentKeyStates[ SDL_SCANCODE_LSHIFT ])
        {
            velo=3;
            animation_velocity=10;
        }else
        {
            velo=1;
            animation_velocity=15;
        }
        if(currentKeyStates[ SDL_SCANCODE_U])
        {
                velocity=3;
                animation_velocity=10;
        }else
        {
            velocity=1;
            animation_velocity=15;
        }


        if(frame%animation_velocity==0)
        {
            current_sprite++;
            if(current_sprite>1)
                current_sprite=0;
        }

        SDL_Delay(17);


        if((rect_character.y +15 > rect_character2.y && rect_character.y - 15 < rect_character2.y) &&
         (rect_character.x -15 < rect_character2.x  &&  rect_character.x+15 > rect_character2.x)){

            Mix_PlayChannel(-1,scream,1);
            rect_character2.x=0;
            rect_character2.y=0;


            rect_character.x=400;
            rect_character.y=220;
            cout<<cont++<<endl;

        }

        //SDL_BlitSurface( ms ,NULL, ms, NULL);

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        SDL_RenderCopy(renderer, sprites[ori2][current_sprite], NULL, &rect_character);
        SDL_RenderCopy(renderer,charizard[orientation][current_sprite],NULL, &rect_character2);
        SDL_RenderCopy(renderer, m, &Message_rect, &Message_rect); //ESTO NO FUNCIONO ES DEL TEXTO
        SDL_RenderPresent(renderer);

        frame++;
    }


	return 0;
}
