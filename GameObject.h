#pragma once
extern const int displayMode;

enum MoveList
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

class Game_Object
{
protected:
	SDL_Rect* rect;
	SDL_Texture* texture;
	SDL_Renderer* ren;


public:
	Game_Object(SDL_Renderer* ren, SDL_Texture* texture)
	{
		rect = new SDL_Rect;
		this->texture = texture;
		this->ren = ren;
		*rect = { 0, 0, 0, 0 };
	}



	void move(double x, double y)
	{
		rect->x += x;
		rect->y += y;
	}

	void moveTo(int x, int y)
	{
		rect->x = x;
		rect->y = y;
	}

	int get_x()
	{
		return rect->x;
	}

	int get_y()
	{
		return rect->y;
	}

	int get_w()
	{
		return rect->w;
	}

	int get_h()
	{
		return rect->h;
	}


	void resize(int w, int h)
	{
		rect->w += w;
		rect->h += h;
	}

	virtual void render()
	{
		SDL_RenderCopy(ren, texture, NULL, rect);
	}

	virtual void render(int deg)
	{
		SDL_RenderCopyEx(ren, texture, NULL, rect, deg, NULL, SDL_FLIP_NONE);
	}
};