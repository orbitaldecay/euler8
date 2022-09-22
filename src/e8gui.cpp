#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "e8core.hpp"

#define WIDTH 128
#define HEIGHT 128
#define SCALE 4

int main(int argc, char** argv) {
	bool quit = false;
	SDL_Event event;
	program_t p;
	argstack_t a;
	operator_args_t args;
	arg_t rg, ba, s;

	FILE* f;
	if (argc != 2)
	{
		fprintf(stderr, "Usage: e8gui cartfile\n");
		return -1;
	}
	f = fopen(argv[1], "rb");
	if (!f)
	{
		fprintf(stderr, "Unable to open \"%s\"\n", argv[1]);
		return -1;
	}
	prog_load(f, &p);
	fclose(f);
	args.a = &a;
	args.z.real(0);
	args.z.imag(0);
	args.t.real(0);
	args.t.imag(0);
	args.s.real(0);
	args.s.imag(0);
	a.clear();


	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* screen = SDL_CreateWindow("Euler8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * SCALE, HEIGHT * SCALE, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, 0);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH * SCALE, HEIGHT * SCALE);
	Uint32* pixels = new Uint32[WIDTH * SCALE * HEIGHT * SCALE];
	arg_t* state = new arg_t[WIDTH * HEIGHT];
	memset(pixels, 0, WIDTH * SCALE * HEIGHT * SCALE * sizeof(Uint32));
        for (int i = 0; i < WIDTH * HEIGHT; i++)
            state[i] = arg_t(0, 0);
	while (!quit)
	{
	    args.t.real(SDL_GetTicks() / 1000.0);
            args.t.imag(0);
	    for (int y = 0; y < HEIGHT; y++)
	    {
    	        args.z.imag(2 * ((double) y) / HEIGHT - 1);
	        for (int x = 0; x < WIDTH; x++)
                {
		    args.a->clear();
                    args.z.real(2 * ((double) x) / WIDTH - 1);
                    args.s = state[y * WIDTH + x];
		    prog_run(&p, &args);
		    if (a.sp >= 0)
                    {
		        rg = a.back();
		        a.pop_back();
                    }
                    else
                    {
                        rg = arg_t(0, 0);
                    }
		    if (a.sp >= 0)
                    {
		        ba = a.back();
		        a.pop_back();
                    }
                    else
                    {
                        ba = arg_t(0, 0);
                    }
		    if (a.sp >= 0)
                    {
		        s = a.back();
		        a.pop_back();
                    }
                    else
                    {
                        s = arg_t(0, 0);
                    }
                    state[y * WIDTH + x] = s;
                    unsigned char r = ((rg.real() + 1) / 2) * 255;
                    unsigned char g = ((rg.imag() + 1) / 2) * 255;
                    unsigned char b = ((ba.real() + 1) / 2) * 255;
		    r &= (15 << 4);
		    g &= (15 << 4);
		    b &= (15 << 4);
                    int v = b | (g << 8) | (r << 16);
		    for (int i = 0; i < SCALE; i++)
                        for (int j = 0; j < SCALE; j++)
                            pixels[(y * SCALE + i) * WIDTH * SCALE + (x * SCALE + j)] = v;
	        }
            }
	    SDL_UpdateTexture(texture, NULL, pixels, WIDTH * SCALE * sizeof(Uint32));
	    while (SDL_PollEvent(&event) != 0)
	    {
	        switch (event.type)
	        {
	            case SDL_QUIT:
	                quit = true;
	                break;
	        }
	    }
	    SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
	}
	SDL_DestroyWindow(screen);
	SDL_Quit();
	return 0;
}