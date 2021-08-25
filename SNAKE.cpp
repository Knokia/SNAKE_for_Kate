#include <iostream>
#include <time.h>
#include <random>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <windows.h>
#include <vector>
#include <list>
#include <fstream>
#include <SDL_ttf.h>

#include "function.h"
#include "timer.h"
#include "GameObject.h"
#include "Background.h"
#include "apple.h"
#include "snake.h"
#include "menu.h"

const int displayMode = 512;

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	SDL_Window* win = nullptr;
	//подключаем sdl и задаем настройки окна
	if (!init(ren, win, displayMode))	return -1;
	system("color F0");
	//подгружаем текстурки
	SDL_Texture* background_texture = IMG_LoadTexture(ren, "image//background.png");
	Background* background;
	SDL_Texture* apple_texture = IMG_LoadTexture(ren, "image//apple.png");
	Apple* apple;
	int score = 0;
	SDL_Texture* head_texture[2];
	head_texture[0] = IMG_LoadTexture(ren, "image//head.png");
	head_texture[1] = IMG_LoadTexture(ren, "image//body.png");
	Snake* snake;

	game_pos player_pos = in_menu;
	bool run = true;
	SDL_Event event;
	int raiting[11];

	bool run_game = true;
	bool in_game = false;

	Menu* game_menu = new Menu();

	while (run_game == true)
	{
		while (in_game == false && run_game == true)
		{
			SDL_WaitEvent(&event);

			switch (player_pos)
			{
			case in_menu:
				switch (event.type)
				{
				case SDL_QUIT:
					run_game = false;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_RETURN:
						player_pos = game_menu->enter();
						if (player_pos == rules)
							game_menu->draw_instruction();
						else if (player_pos == best_scores)
								make_raiting(ren, raiting, score);
						break;

					case SDLK_UP:
						game_menu->up();
						break;

					case SDLK_DOWN:
						game_menu->down();
						break;

					}
				}
				break;
			case play:
				in_game = true;
				break;

			case best_scores:
				switch (event.type)
				{
				case SDL_QUIT:
					run_game = false;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						game_menu->drawMainMenu();
						player_pos = in_menu;
						break;
					}
				}
				break;
				

			case rules:
				switch (event.type)
				{
				case SDL_QUIT:
					run_game = false;
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						game_menu->drawMainMenu();
						player_pos = in_menu;
						break;
					}
				}
				break;

			case quit:
				run_game = false;
				break;

			case lost_game:
				switch (event.type){
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						player_pos = in_menu;
						game_menu->drawMainMenu();
						break;
					case SDLK_RETURN:
						in_game = true;
						break;
					}
				}
				break;
			}
		}

		while (in_game == true)
		{
			
			run = true;
			score = 0;
			background = new Background(ren, background_texture, 16);
			background->resize(displayMode, displayMode);
			apple = new Apple(ren, apple_texture, background);
			snake = new Snake(ren, head_texture, background, apple, &score);

			while (run)
			{
				SDL_Delay(10);
				if (SDL_PollEvent(&event))
				{
					snake->Controll(event);
					if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
						run = false;
				}
				if (!snake->Go())
					run = false;

				background->render();
				add_text(ren, "score: ", 40, 0, 0, true);
				add_text(ren, std::to_string(score), 40, 70, 0, true);
				

				apple->render();
				snake->render();
				SDL_RenderPresent(ren);
			}


			//SDL_Delay(3000);
			delete apple;
			delete background;
			delete snake;

			in_game = false;
			game_menu->lost();
			make_rating_for_lost(ren, raiting, score);
			add_text(ren, "score: ", 40, 0, 0, true);
			add_text(ren, std::to_string(score), 40, 70, 0, true);
			
			
				std::fstream file;
				int size = 0;
				file.open("raiting.bin", std::ios::binary | std::ios::in);
				if (file.is_open())
				{
					file.seekg(0, std::ios::end);
					size = static_cast<int>(file.tellg() / sizeof(int));
					file.seekg(0, std::ios::beg);
					for (int i = 0; i < size; i++)
					{
						file.read((char*)&raiting[i], sizeof(int));
					}
					file.close();
				}
				raiting[size] = score;

				//сортируем по возрастанию
				int buff;
				int j;

				for (int i = 1; i <= size; i++)
				{
					buff = raiting[i];
					for (j = i - 1; j >= 0 && raiting[j] < buff; j--)
						raiting[j + 1] = raiting[j];
					raiting[j + 1] = buff;
				}

				std::remove("raiting.bin");

				file.open("raiting.bin", std::ios::out);
				for (int i = 0; i <= size && i < 10; i++)
					file.write((char*)&raiting[i], sizeof(int));

			player_pos = lost_game;
				
		}
	}

	delete game_menu;
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(apple_texture);
	SDL_DestroyTexture(head_texture[0]);
	SDL_DestroyTexture(head_texture[1]);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
	

}