#include "../Header Files/Game.h"
#include <iostream>


void Game::initializeVariables()
{
 this->window = nullptr;
}

void Game::initializeWindow()
{
	//video mode object // allows us to set the size of the window outside of the RenderWindow function
	this -> videoMode.height = 720;
	this -> videoMode.width = 1080;
	this -> window = new sf::RenderWindow(this -> videoMode, "Vital Shakedown", sf::Style::Titlebar | sf::Style::Close);
	this -> window -> setFramerateLimit(60); //sets the frame rate to 60 frames per second 
}


// Constructor / Destructor
Game::Game() : 
	
	player1(100.f, 520.f, sf::Color::Red, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
	player2(880.f, 520.f, sf::Color::Blue, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up) //constructor
				
{
	this->initializeVariables();
	this->initializeWindow();

}




Game::~Game()
{
	delete this->window; //deletes the window
}

// Accessors

const bool Game::running() const 
{
	return this-> window->isOpen(); //returns if the window is open
}

// Functions

void Game::pollEvents() //poll events function //event handling
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{

		case sf::Event::Closed:  //close the window manually when user clicks on the close button
			this->window->close();
			break;

		case sf::Event::KeyPressed:  //event handling for key presses

			/*close the window when user presses the escape key
			 precaution if game crashes or freezes, user can close the window manually
			*/

			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
				break;

			}

			
		}
	}
}



void Game::update() //update function //game logic 

{
	this->pollEvents(); //call poll events
	
	this->player1.update(this->window);//update the player object
	this->player2.update(this->window);//update the player object
	
}
void Game::render() //render function //draws the game to the screen
{
	this->window->clear(); //clears the window
	this->player1.render(this->window); //renders the player object
	this->player2.render(this->window); //renders the player object
	this->window->display(); //displays the game objects

	
}





