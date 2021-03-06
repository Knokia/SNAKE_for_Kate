#pragma once


extern const int displayMode;

bool init(SDL_Renderer* &ren, SDL_Window* win, const int displayMode)
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	win = SDL_CreateWindow("SNAKE", 100, 100, displayMode, displayMode, SDL_WINDOW_SHOWN);

	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (!ren)
	{
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "init complete sucsesseful" << std::endl;

	return true;
}

void add_text(SDL_Renderer* ren, std::string msg,int size ,int x, int y, bool isBlack)
{
	TTF_Font* font = TTF_OpenFont("Thintel.ttf", size);
	SDL_Color color;
	if(isBlack == true)
	color = { 255, 000, 140 };
	else color = { 000, 000, 000 };
	SDL_Surface* text = TTF_RenderText_Solid(font, msg.c_str(), color);

	if (!text)
	{
		std::cout << "Failed to render text: " << TTF_GetError();
	}
	else
	{
		SDL_Texture* text_texture = SDL_CreateTextureFromSurface(ren, text);
		SDL_Rect dest = { x, y, text->w, text->h };
		SDL_RenderCopy(ren, text_texture, NULL, &dest);
		SDL_DestroyTexture(text_texture);
	}
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
}

void make_raiting(SDL_Renderer* ren, int* raiting, int score)
{
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
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

	add_text(ren, "Best scores: ", 40, displayMode * 0.35, 110, true);
	for (int i = 1, j = 165; i < size && i <= 10; i++, j += 30)
		add_text(ren, std::to_string(i)+ ". "+std::to_string(raiting[i]), 40, displayMode * 0.45, j, true);

	SDL_RenderPresent(ren);
	std::remove("raiting.bin");

	file.open("raiting.bin", std::ios::out);
	for (int i = 0; i <= size && i < 10; i++)
		file.write((char*)&raiting[i], sizeof(int));
}

void draw_rating(SDL_Renderer* ren, int* raiting, int score, bool scoreIsNew)
{
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
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

	//????????? ?? ???????????
	int buff;
	int j;
	if (scoreIsNew == true)
	{
		for (int i = 1; i <= size; i++)
		{
			buff = raiting[i];
			for (j = i - 1; j >= 0 && raiting[j] < buff; j--)
				raiting[j + 1] = raiting[j];
			raiting[j + 1] = buff;
		}
	}
}

void make_rating_for_lost(SDL_Renderer* ren, int* raiting, int score) 
{
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

	add_text(ren, "Total point: ", 40, displayMode * 0.35, 55, true);
	add_text(ren, std::to_string(score), 40, displayMode * 0.6, 55, true);
	SDL_RenderPresent(ren);
}

