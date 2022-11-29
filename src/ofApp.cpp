#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Create the game board
	initializeRandom();
	// Make the game 60fps
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Update twice every second
	if (ofGetFrameNum() % 30 == 0 && !isPaused)
	{
		// Start the new generation
		cells = CellsManager::updateCells(cells);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Erase the last generation
	ofBackground(255);

	// Draw the new generation
	CellsManager::drawCells(cells);
}

void ofApp::initialize()
{
	// Remove the last game board
	cells.clear();

	// Go through every cell
	for (auto row{ 0 }; row < boardSize; ++row)
	{
		// Create a new Cell vector
		std::vector<Cell> tempVect;
		for (auto col{ 0 }; col < boardSize; ++col)
		{
			// Assign the cells to the temp vectordd
			const Point temp{ row * size, col * size, size };
			
			tempVect.emplace_back(Cell::state::dead, temp);
		}
		// Add the temp vector to cells
		cells.emplace_back(tempVect);
	}
}


void ofApp::initializeRandom()
{
	cells.clear();
	
	for (auto row{ 0 }; row < boardSize; ++row)
	{
		std::vector<Cell> tempVect;
		for (auto col{ 0 }; col < boardSize; ++col)
		{
			const Point temp{ row * size, col * size, size };

			// Check if the cell is alive or dead, 10% chance to be alive
			if(ofRandom(10) < 1) 	
			{	 tempVect.emplace_back(Cell::state::alive, temp);		}
			else tempVect.emplace_back(Cell::state::dead, temp);
		}
		cells.emplace_back(tempVect);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// Check for space bar
	if(key == ' ')
	{
		// Invert isPaused
		isPaused = !isPaused;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

void ofApp::mousePressed(int x, int y, int button)
{
	

	// Check if the game is paused
	// if so then check where the mouse was pressed
	for (auto row{ 0 }; isPaused && row < boardSize; ++row)
	{
		// Bool to break out of the loop
		bool breaker{ false };

		for (auto col{ 0 }; col < boardSize; ++col)
		{
			// Get the size and position of current cell
			const Point temp{ row * size, col * size, size };

			// Check if mouse is at current cell
			if (x < (row * size) + size && y < (col * size) + size)
			{
				// toggle cell state
				if ( cells[row][col].isAlive())
				{	 cells[row][col] = Cell{ Cell::state::dead, temp };	}
				else cells[row][col] = Cell{ Cell::state::alive, temp };

				// Stop the loop
				breaker = true;
				break;
			}
		}
		// Break out of outer loop
		if (breaker) break;
	}
}
