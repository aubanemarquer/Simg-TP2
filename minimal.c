#include "header.h"

/* PROTOTYPES */

float coorX(float x);

float coorY(float y);

void resizeWindow();

void drawPoint(PointListe* listePoints);

void drawLine(PointListe* listePoints);

void drawTriangle(PointListe* listePoints);

void drawUnQuad(float c1, float c2, float c3, float x1);

void drawQuad();

Point* allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b);

void addPointToList(Point* point, PointListe *list);

void drawClean();

void changerCouleur(float x, char* tabCoul);

void deletePoints(PointListe* list);

void deletePrimitive(PrimitiveListe* list);

Primitive* allocPrimitive(GLenum primitiveType);

void addPrimitive(Primitive* primitive, PrimitiveListe* list);

void drawPrimitives(PrimitiveListe* list);

int main(int argc, char** argv) {


	PointListe listePoints;
	listePoints = (PointListe)malloc(sizeof(PointListe));
	if(listePoints==NULL){
		exit(0);
	}

	PrimitiveListe listePrimitives;
	listePrimitives = (Primitive*)malloc(sizeof(Primitive));
	if(listePrimitives!=NULL){
		listePrimitives=NULL;
	}else{
		exit(0);
	}

	addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);

	char tabCoul[4]={0,0,0,'\0'};

	char touche = 'p';
	
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("TP1 : cmonannif", NULL);
    
    /* Boucle d'affichage */
    glClearColor(0.9,0.9,0.9,1); // definir la couleur de nettoyage (Jaune)
    glClear(GL_COLOR_BUFFER_BIT); // Nettoie la fenetre et appelle la couleur de nettoyage

    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
      
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) { // e.type = type d'evnt recu

                case SDL_VIDEORESIZE:
                	WINDOW_WIDTH = e.resize.w;
                	WINDOW_HEIGHT = e.resize.h;
                    resizeWindow();
                    drawClean();
                    drawPrimitives(&listePrimitives);
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:


                	switch(touche){

                		case 'p':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case 'l':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case 't':
                			addPointToList(allocPoint(e.button.x, e.button.y, tabCoul[0], tabCoul[1], tabCoul[2]), &(listePrimitives->points));
                			drawPrimitives(&listePrimitives);
                			break;

                		case ' ':
                			printf("Recherche de couleurs\n");
                			changerCouleur(e.button.x, tabCoul);
                			break;
	    
                		default:
                			break;
                	}


                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Mouvement souris */
                case SDL_MOUSEMOTION:
                    glClearColor(e.button.x/(float)WINDOW_WIDTH,e.button.y/(float)WINDOW_HEIGHT,0,1);
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:

                	switch(e.key.keysym.sym){

                		case 'q' : 
                			deletePrimitive(&listePrimitives);
                        	loop=0;
                			break;

                		case ' ':
                			printf("Touche espace pressée\n");
	                    	drawQuad();
	                    	break;

	                    case 'd':
	                    	deletePrimitive(&listePrimitives);
	                    	addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);
	                		drawClean();
	                		break;

	                	case 'l':
	                		if(touche != 'l'){
	                			addPrimitive(allocPrimitive(GL_LINES), &listePrimitives);
	                		}
	                		break;

	                	case 'p':
	                		if(touche != 'p'){
	                			addPrimitive(allocPrimitive(GL_POINTS), &listePrimitives);
	                		}
	                		break;

	                	case 't':
	                		if(touche != 't'){
	                			addPrimitive(allocPrimitive(GL_TRIANGLES), &listePrimitives);
	                		}
	                		break;

	                	default:
	                		break;

                	}

                    /* On determine ce que l'utilisateur souhaite dessiner et on l'enregistre dans 'touche' */
                    if(e.key.keysym.sym != 'd'){
                    	touche = e.key.keysym.sym;
                    }

                    
                    printf("valeur de 'touche' (code = %c)\n", touche);
                    /********************************************************************/

                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
                    glClearColor(1,0,1,1);
                    break;

                 case SDL_KEYUP:

                 	if(e.key.keysym.sym == ' '){
                    printf("Touche espace relarchée\n");
                    drawClean();
                    drawPrimitives(&listePrimitives);
                    touche = 'p';
                    }

                 	break;

                default:
                    break;
            }

        }

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
