#include <stdlib.h>

#include "GUI.h"

/*
 * Deze renderer wordt gebruikt om figuren in het venster te tekenen. De renderer
 * wordt geïnitialiseerd in de initialize_window-functie.
 */
static SDL_Renderer *renderer;

/* De afbeelding die een vakje met een "1" in voorstelt. */
static SDL_Texture *digit_1_texture = NULL;


/*
 * Onderstaande twee lijnen maken deel uit van de minimalistische voorbeeldapplicatie:
 * ze houden de laatste positie bij waar de gebruiker geklikt heeft.
 */
int mouse_x = 0;
int mouse_y = 0;

/*
 * Geeft aan of de applicatie moet verdergaan.
 * Dit is waar zolang de gebruiker de applicatie niet wilt afsluiten door op het kruisje te klikken.
 */
int should_continue = 1;

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel ten einde komt.
 */
static SDL_Window *window;

/*
 * Controleert of het gegeven event "relevant" is voor dit spel.
 * We gebruiken in deze GUI enkel muiskliks, toetsdrukken, en de "Quit"
 * van het venster, dus enkel deze soorten events zijn "relevant".
 */
static int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) ||
           (event->type == SDL_KEYDOWN) ||
           (event->type == SDL_QUIT);
}

/*
 * Vangt de input uit de GUI op. Deze functie is al deels geïmplementeerd, maar je moet die
 * zelf nog afwerken.
 * Je mag natuurlijk alles aanpassen aan deze functie, inclusies return-type en argumenten.
 */
void read_input() {
    SDL_Event event;

    /*
     * Handelt alle input uit de GUI af.
     * Telkens de speler een input in de GUI geeft (bv. een muisklik, muis bewegen, toetsindrukken
     * enz.) wordt er een 'event' (van het type SDL_Event) gegenereerd dat hier wordt afgehandeld.
     *
     * Niet al deze events zijn relevant voor jou: als de muis bv. gewoon wordt bewogen, hoef
     * je niet te reageren op dit event.
     * We gebruiken daarom de is_relevant_event-functie om niet-gebruikte events weg te
     * filteren, zonder dat ze de applicatie vertragen of de GUI minder responsief maken.
     *
     * Zie ook https://wiki.libsdl.org/SDL_PollEvent
     */
    while (1) {
        int event_polled = SDL_PollEvent(&event);
        if (event_polled == 0) {
            return;
        } else if (is_relevant_event(&event)) {
            break;
        }
    }

    switch (event.type) {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_p) {
            printf("P pressed\n");
        }
        break;
    case SDL_QUIT:
        // De gebruiker heeft op het kruisje van het venster geklikt om de applicatie te stoppen.
        should_continue = 0;
        break;
    case SDL_MOUSEBUTTONDOWN:
        /*
         * De speler heeft met de muis geklikt: met de onderstaande lijn worden de coördinaten in het
         * het speelveld waar de speler geklikt heeft bewaard in de variabelen mouse_x en mouse_y.
         */
        mouse_x = event.button.x;
        mouse_y = event.button.y;
        printf("Clicked at (%i,%i)\n", mouse_x, mouse_y);
        break;
    }
}

void draw_window() {
	/*
	 * Maakt het venster blanco.
	 */
	SDL_RenderClear(renderer);


	/*
	 * Bereken de plaats (t.t.z., de rechthoek) waar een afbeelding moet getekend worden.
	 * Dit is op de plaats waar de gebruiker het laatst geklikt heeft.
	 */
	SDL_Rect rectangle = { mouse_x, mouse_y, IMAGE_WIDTH, IMAGE_HEIGHT };
	/* Tekent de afbeelding op die plaats. */
	SDL_RenderCopy(renderer, digit_1_texture, NULL, &rectangle);

    /*
     * De volgende lijn moet zeker uitgevoerd worden op het einde van de functie.
     * Wanneer aan de renderer gevraagd wordt om iets te tekenen, wordt het venster pas aangepast
     * wanneer de SDL_RenderPresent-functie wordt aangeroepen.
     */
	SDL_RenderPresent(renderer);
}

/*
 * Initialiseert het venster en alle extra structuren die nodig zijn om het venster te manipuleren.
 */
void initialize_window(const char *title, int window_width, int window_height) {
	/*
	 * Code o.a. gebaseerd op:
	 * http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
	 */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	/* Maak het venster aan met de gegeven dimensies en de gegeven titel. */
	window = SDL_CreateWindow(title, 0, 0, window_width, window_height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		/* Er ging iets verkeerd bij het initialiseren. */
		printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
		exit(1);
	}

	/* Initialiseert de renderer. */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	/* Laat de default-kleur die de renderer in het venster tekent wit zijn. */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

/*
 * Laadt alle afbeeldingen die getoond moeten worden in.
 */
void initialize_textures() {
	/*
	 * Laadt de afbeeldingen in. In deze minimalistische applicatie laden we slechts 1 afbeelding in.
	 * Indien de afbeelding niet kon geladen worden (bv. omdat het pad naar de afbeelding verkeerd is),
	 * geeft SDL_LoadBMP een NULL-pointer terug.
	 */
	SDL_Surface *digit_1_surface = SDL_LoadBMP("Images/mine.bmp");
	/*
	 * Zet deze afbeelding om naar een texture die getoond kan worden in het venster.
	 * Indien de texture niet kon omgezet worden, geeft de functie een NULL-pointer terug.
	 */
	digit_1_texture = SDL_CreateTextureFromSurface(renderer, digit_1_surface);
	/* Dealloceer de tijdelijke SDL_Surface dat werd aangemaakt. */
	SDL_FreeSurface(digit_1_surface);
}

/*
 * Initialiseert onder het venster waarin het speelveld getoond zal worden, en de texture van de afbeelding die getoond zal worden.
 * Deze functie moet aangeroepen worden aan het begin van het spel, vooraleer je de spelwereld begint te tekenen.
 */
void initialize_gui(int window_width, int window_height) {
	initialize_window("Minesweeper", window_width, window_height);
	initialize_textures();
    // Maakt van wit de standaard, blanco achtergrondkleur.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

/*
 * Dealloceert alle SDL structuren die geïnitialiseerd werden.
 */
void free_gui() {
    // Dealloceert de afbeelding
    SDL_DestroyTexture(digit_1_texture);
    // Dealloceert de renderer.
    SDL_DestroyRenderer(renderer);
    // Dealloceert het venster.
    SDL_DestroyWindow(window);

    // Sluit SDL af.
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    initialize_gui(WINDOW_WIDTH,WINDOW_HEIGHT);
    while (should_continue) {
        draw_window();
        read_input();
    }
    // Dealloceer al het geheugen dat werd aangemaakt door SDL zelf.
    free_gui();
    return 0;
}
