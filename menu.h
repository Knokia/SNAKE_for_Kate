#pragma once
SDL_Renderer* ren = nullptr;

enum game_pos
{
	in_menu = 1,
	play,
	best_scores,
	rules,
	quit,
	lost_game
};

class Menu
{
private:
	game_pos pos;
	SDL_Texture* menu_1;
	SDL_Texture* menu_2;
	SDL_Texture* menu_3;
	SDL_Texture* menu_4;
	SDL_Texture* instruction;
	SDL_Texture* menu_words;
	SDL_Texture* game_over;
public:
	Menu()
	{
		SDL_Surface* surface;
		pos = play;

		surface = IMG_Load("image/menu_1.png");
		menu_1 = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/menu_2.png");
		menu_2 = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/menu_3.png");
		menu_3 = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/menu_4.png");
		menu_4 = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/instruction.png");
		instruction = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/menu_items.png");
		menu_words = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		surface = IMG_Load("image/game_over.png");
		game_over = SDL_CreateTextureFromSurface(ren, surface);
		SDL_FreeSurface(surface);

		drawMainMenu();
	}

	~Menu()
	{
		SDL_DestroyTexture(menu_1);
		SDL_DestroyTexture(menu_2);
		SDL_DestroyTexture(menu_3);
		SDL_DestroyTexture(menu_4);
		SDL_DestroyTexture(instruction);
		SDL_DestroyTexture(menu_words);
		SDL_DestroyTexture(game_over);
	}

	void draw_instruction()
	{
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, instruction, nullptr, nullptr);
		SDL_RenderPresent(ren);
	}

	void drawMainMenu()
	{
		SDL_RenderClear(ren);

		switch (pos)
		{
		case play:
			SDL_RenderCopy(ren, menu_1, nullptr, nullptr);
			break;
		case best_scores:
			SDL_RenderCopy(ren, menu_2, nullptr, nullptr);
			break;
		case rules:
			SDL_RenderCopy(ren, menu_3, nullptr, nullptr);
			break;
		case quit:
			SDL_RenderCopy(ren, menu_4, nullptr, nullptr);
			break;
		}
		SDL_RenderCopy(ren, menu_words, nullptr, nullptr);
		SDL_RenderPresent(ren);
	}

	void down()
	{
		if (pos != quit)
			pos = (game_pos)((int)pos + 1);
		else pos = play;
		drawMainMenu();
	}

	void up()
	{
		if (pos != play)
			pos = (game_pos)((int)pos - 1);
		else pos = quit;
		drawMainMenu();
	}

	void lost()
	{
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, game_over, nullptr, nullptr);
		SDL_RenderPresent(ren);
	}

	game_pos enter()
	{
		return pos;
	}
};