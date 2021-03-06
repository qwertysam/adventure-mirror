#ifndef FLOOR_H
#define FLOOR_H

#include "../Entity.h"
#include <vector>
#include <iostream>
#include <memory>

using namespace std;

class Floor {
	size_t i, w, h, sX, sY;
	vector<vector<vector<shared_ptr<Entity>>>> grid;
public:
	Floor(size_t i, size_t w, size_t h);
	void add(shared_ptr<Entity> e);
	vector<shared_ptr<Entity>> &get(size_t x, size_t y);
	shared_ptr<Entity> getTop(size_t x, size_t y);
	void setSpawn(size_t x, size_t y);
	size_t spawnX();
	size_t spawnY();
	size_t index();
	size_t width();
	size_t height();

	friend ostream &operator<<(ostream &out, Floor &f);
};

#endif
