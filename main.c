#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#include "m_utils.h"
#include "object.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
//SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;

int closegame = 0; //Close game?
uint32_t rnd_val = 0;


void init()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Small Bullets", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);
}

void input()
{
	SDL_Event event;
	
	while(SDL_PollEvent(&event) > 0)
	{
		if (event.type == SDL_QUIT) closegame = 1;
		
		/*if (event.type == SDL_KEYDOWN)
		{
			switch(event.key.keysym.sym)
			{
			}
		}*/
	}
}

void update()
{
	OBJ_Update();
}

void draw()
{
	SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);
	
	//Draw all existing objects
	SDL_Rect rect;
	object_t* obj = OBJ_GetFirstObj();
	while(obj)
	{
		rect.x = (int)obj->x;
		rect.y = (int)obj->y;
		rect.w = obj->w;
		rect.h = obj->h;
		uint8_t r,g,b;
		
		if (obj->type == OBJ_SPAWNER)
		{
			r = rand()&0xFF;
			g = rand()&0xFF;
			b = rand()&0xFF;
			SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
		}
		else
			SDL_SetRenderDrawColor(renderer, obj->r, obj->g, obj->b, 0xFF);
		SDL_RenderFillRect(renderer, &rect);
		
		obj = obj->next;
	}
	
	SDL_RenderPresent(renderer);
}

void close()
{
	OBJ_ClearList();
}

int main(int argc, char** argv)
{
	uint32_t fps = 60;
	uint32_t elapsed;
	uint32_t frameTime;
	
	init();
	
	float px1, py1, px2, py2;
	px1 = 200.0f; py1 = SCREENHEIGHT/2;
	px2 = 600.0f; py2 = SCREENHEIGHT/2;
	object_t* spawn1;
	object_t* spawn2;
	spawn1 = OBJ_Create(OBJ_SPAWNER, px1, py1, 0);
	spawn2 = OBJ_Create(OBJ_SPAWNER, px2, py2, 0);
	//spawn1->speed = 1.0f;
	//spawn2->speed = 1.0f;
	
	uint8_t spcooldown_val = 3;
	uint8_t spawn_cooldown = 0;
	
	while(!closegame)
	{
		elapsed = SDL_GetTicks();
		
		input();
		rnd_val = rand();
		update();
		draw();
		
		spawn1->angle+=2;
		spawn2->angle-=2;
		
		spawn1->x = px1 + COS(spawn1->angle) * 64;
		spawn1->y = py1 + SIN(spawn1->angle) * 64;
		
		spawn2->x = px2 + COS(spawn1->angle) * 64;
		spawn2->y = py2 - SIN(spawn1->angle) * 64;
		
		
		if (spawn_cooldown) spawn_cooldown--;
		else
		{
			object_t* obj;
			obj = OBJ_Create(OBJ_BULLET, spawn1->x, spawn1->y, spawn1->angle);
			obj->speed = 0.5f;
			//obj->r = (rnd_val>>24)&0xFF;
			//obj->g = (rnd_val>>16)&0xFF;
			//obj->b = (rnd_val)&0xFF;
			obj->r = rand()&0xFF;
			obj->g = rand()&0xFF;
			obj->b = rand()&0xFF;
			obj = OBJ_Create(OBJ_BULLET, spawn2->x, spawn2->y, spawn2->angle);
			obj->speed = 0.5f;
			//obj->r = (rnd_val)&0xFF;
			//obj->g = (rnd_val>>16)&0xFF;
			//obj->b = (rnd_val>>24)&0xFF;
			obj->r = (rnd_val)&0xFF;
			obj->g = (rnd_val)&0xFF;
			obj->b = (rnd_val)&0xFF;
			
			spawn_cooldown = spcooldown_val;
		}
		
		frameTime = SDL_GetTicks() - elapsed;
		
		if (1000/fps > frameTime)
		{
			SDL_Delay((1000/fps) - frameTime);
		}
	}
	
	close();
	
	return 0;
}