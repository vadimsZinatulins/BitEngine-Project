#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

struct GameObject
{
	virtual void update() = 0;
	virtual void render() = 0;

	bool isAlive{ true };
};

#endif // !__GAME_OBJECT_H__
