/**
 * \file main.c
 * \brief Programme principal initial du niveau 1
 * \author Mathieu Constant
 * \version 1.0
 * \date 18 mars 2020
 */

#include "sdl2-light.h"


/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8
/**
 * @brief vitesse verticale de l'ennemi
 */
#define ENEMY_SPEED 2
/**
 * @brief vitesse verticale du missile
 */
#define MISSILE_SPEED 2

/**
 * \brief Représentation pour stocker les textures nécessaires à l'affichage graphique
*/

struct textures_s{
    SDL_Texture* background; /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* skin_ship; /*! apparence du vaisseau*/
    SDL_Texture* skin_ennemy; /*! apparende de l'ennemi*/
    SDL_Texture* missile; /*apparence du missile*/
};


/**
 * \brief Type qui correspond aux textures du jeu
*/

typedef struct textures_s textures_t;

/**
 * @brief representations des entités du jeu
 * @param x position de x par rapport au centre
 * @param y position de y par rapport au centre du sprite
 * @param h la  hauteur du sprite
 * @param w la largeur du sprite 
 * @param v la vitesse vertical du sprite 
 * 
 */
struct sprite_s
{
    /* data */
    int x;
    int y;
    int h;
    int w;
    int v;
    int is_visible; 
};

/**
 * @brief type qui correspond aux entités du jeu
 * 
 */
typedef struct sprite_s sprite_t;



/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    sprite_t ship;
    sprite_t ennemi;
    sprite_t missile;
    
    int gameover; /*!< Champ indiquant si l'on est à la fin du jeu */

};

/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;



/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    init_sprite(&(world->ship), SCREEN_WIDTH/2-SHIP_SIZE/2, SCREEN_HEIGHT-3*SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, 0);
    print_sprite(&(world->ship));
    init_sprite(&(world->ennemi), SCREEN_WIDTH/2-SHIP_SIZE/2,SHIP_SIZE,SHIP_SIZE,SHIP_SIZE,ENEMY_SPEED);
    init_sprite(&(world->missile),SCREEN_WIDTH/2-MISSILE_SIZE/2, SCREEN_HEIGHT-3*SHIP_SIZE/2+MISSILE_SIZE-SHIP_SIZE/2, SHIP_SIZE, SHIP_SIZE, MISSILE_SPEED);
    set_invisible(&(world->missile));
    //on n'est pas à la fin du jeu
    world->gameover = 0;    
}
/**
 * @brief afficher les données d'un sprite
 * 
 * @param sprite le sprite examiné
 */

void print_sprite(sprite_t* sprite){
    printf("X: %d \n y: %d \n h: %d \n w: %d \n v: %d",sprite->x,sprite->y,sprite->h,sprite->w,sprite->v);
}



/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    
}



/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}



/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
    world->ennemi.y+= world->ennemi.v;
    if(world->missile.is_visible){  
    world->missile.y-= MISSILE_SPEED;   /*!< Si le missile est visible, c'est qu'il doit se déplacer */
    }
    else{
         world->missile.x= world->ship.x+SHIP_SIZE/2-MISSILE_SIZE/2; /*!< sinon il doit être placer au dessus du vaisseau*/
    }
}

/**
 * @brief rend visible l'objet
 * 
 * @param sprite 
 */
void set_visible(sprite_t* sprite){
    sprite->is_visible=1;
}

/**
 * @brief rend invisible le sprite
 * 
 * @param sprite 
 */
void set_invisible(sprite_t* sprite){
    sprite->is_visible=0;
}

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */

void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
             //si la touche appuyée est 'D'
             if(event->key.keysym.sym == SDLK_d){
                 printf("La touche D est appuyée\n");
                 world->ship.x+=1;
              }
              else if (event->key.keysym.sym == SDLK_RIGHT)
              {
                  world->ship.x+=10;
              }
              else if (event->key.keysym.sym == SDLK_LEFT)
              {
                  world->ship.x-=10;
              }
              if(event->key.keysym.sym == SDLK_ESCAPE){
                 world->gameover = 1;
              }
              if(event->key.keysym.sym == SDLK_SPACE){
                  set_visible(&(world->missile));
              }
              
              
         }
    }
}
/**
 * @brief Fonction pour initialiser les valeurs des coordonnées d'un vaisseau
 * 
 * @param sprite la structure de type struct_t
 * @param x abscisse
 * @param y ordonnée
 * @param w largeur
 * @param h hauteur
 * @param v vitesse verticale
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v){
    sprite->x=x;
    sprite->y=y;
    sprite->w=w;
    sprite->h=h;
    sprite->v=v;
    sprite->is_visible=1;
}

/**
 * \brief La fonction nettoie les textures
 * \param textures les textures
*/

void clean_textures(textures_t *textures){
    clean_texture(textures->background);
    clean_texture(textures->skin_ship);
    clean_texture(textures->skin_ennemy);
    clean_texture(textures->missile);
}



/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param textures les textures du jeu
*/

void  init_textures(SDL_Renderer *renderer, textures_t *textures){
    textures->background = load_image( "ressources/space-background.bmp",renderer);
    
    textures->skin_ship = load_image("ressources/spaceship.bmp",renderer);

    textures->skin_ennemy = load_image("ressources/enemy.bmp",renderer);

    textures->missile = load_image("ressources/missile.bmp", renderer);

    
}

void apply_sprite(SDL_Renderer* renderer, SDL_Texture* texture, sprite_t* sprite){
    if(sprite->is_visible==1){
        SDL_Rect dst = {0, 0, 0, 0};
    
        SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
        dst.x = sprite->x; dst.y=sprite->y;
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
}

/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param textures les textures du jeu
*/

void apply_background(SDL_Renderer *renderer, textures_t *textures){
    if(textures->background != NULL){
      apply_texture(textures->background, renderer, 0, 0);
    }
}





/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param textures les textures
 */

void refresh_graphics(SDL_Renderer *renderer, world_t *world,textures_t *textures){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des textures dans le renderer
    apply_background(renderer, textures);
    apply_sprite(renderer,textures->skin_ship,&(world->ship));
    apply_sprite(renderer,textures->skin_ennemy,&(world->ennemi));
    apply_sprite(renderer,textures->missile,&world->missile);
   

    
    
    // on met à jour l'écran
    update_screen(renderer);
}



/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des textures, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param textures les textures
* \param world le monde
*/

void clean(SDL_Window *window, SDL_Renderer * renderer, textures_t *textures, world_t * world){
    clean_data(world);
    clean_textures(textures);
    clean_sdl(renderer,window);
}



/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des textures, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param textures les textures
 * \param wordl le monde
 */

void init(SDL_Window **window, SDL_Renderer ** renderer, textures_t *textures, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(world);
    init_textures(*renderer,textures);

}


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    textures_t textures;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&textures,&world);
    
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&textures);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);
    }
    
    //nettoyage final
    clean(window,renderer,&textures,&world);
    
    
    return 0;
}
