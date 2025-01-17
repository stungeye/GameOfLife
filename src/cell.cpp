﻿#include "cell.h"

// Create the Cell Object
Cell::Cell(state s, Point i) : current{ s }, info{i} {}

void Cell::updateState(int neighbors)
{
	// Change state based on neighbors
	switch(neighbors)
	{
		case 2:
		case 3:
			// Check if the Cell is coming alive
			if(neighbors == 3 && current == Cell::state::dead)
			{
				current = Cell::state::alive;
			}
			break;
		default:
			// Make the cell Die
			current = Cell::state::dead;
			break;
	}
}

void Cell::drawCell() const
{
	// Change color based on current state
	if(current == Cell::state::alive) ofSetColor(255);
	else ofSetColor(0);
	ofDrawRectangle(info.x, info.y, info.size, info.size);
}

bool Cell::isAlive() const
{
	// Return whether the cell is alive or not
	return current == state::alive;
}

