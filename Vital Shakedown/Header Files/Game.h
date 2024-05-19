#pragma once
#include "../Header Files\Player.h"
#include <iostream>
#include <vector>

// Class that acts as the game engine

class Game
{
private:
	 // Variables
	// Window
	sf::RenderWindow* window; // Pointer to the window 
	sf::Event ev;
	sf::VideoMode videoMode; // Video mode object // allows us to set the size of the window
	
	//create player object
	
	Player player1; //player object
	Player player2; //player object



	// Private functions
	void initializeVariables();
	void initializeWindow();


public:
	

	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Accessors
	const bool running() const;


	// Functions
	void pollEvents();
	void update();
	void render();

};
