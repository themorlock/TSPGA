#include "../include/tsp.h"

int main(int argc, char *argv[]) {
    SDL_Window *window = SDL_CreateWindow("Traveling-Salesman Genetic Algorithm", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 512, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int board_width = 512;
    int board_height = 256;
    int num_cities = 64;
    int k = 64;
    float graph_screen_proportion = 0.125;
    switch(argc)
    {
        case 6:
            graph_screen_proportion = strtof(argv[5], NULL);
        case 5:
            k = atoi(argv[4]);
        case 4:
            num_cities = atoi(argv[3]);
        case 3:
            board_height = atoi(argv[2]);
        case 2:
            board_width = atoi(argv[1]);

    }
    tsp the_tsp;
    initialize_tsp(&the_tsp, board_width, board_height, num_cities, k, graph_screen_proportion);

    int running = 1;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        update_tsp(&the_tsp);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);
        draw_tsp(&the_tsp, window);
        SDL_RenderPresent(renderer);
        //SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    free_tsp(&the_tsp);

    return 0;
}
