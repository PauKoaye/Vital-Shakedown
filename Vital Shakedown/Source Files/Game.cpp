#include "../Header Files/Game.h"
#include <iostream>
#include<stdlib.h>


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
	
	player1(500.f, 720.f, sf::Color::Red, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, true),
	player2(900.f, 720.f, sf::Color::Blue, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, false) //constructor
				
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




void Game::checkPlayerCollision(Player& player1, Player& player2)
{
	sf::FloatRect player1Bounds = player1.getShape().getGlobalBounds(); //get the global bounds of the player object
	sf::FloatRect player2Bounds = player2.getShape().getGlobalBounds(); //get the global bounds of the player object
	sf::FloatRect intersection; //variable to store the intersection of the two players
	bool collisionDetected = player1Bounds.intersects(player2Bounds, intersection); // Check if the two players intersect
	
	if(collisionDetected) //if the two players intersect stores the intersection in the intersection variable
	{
		std::cout<<"Collision Detected"<<std::endl;
		player1.handleCollision(intersection);
		player2.handleCollision(intersection);
		
	}
	intersection = sf::FloatRect(0, 0, 0, 0); //reset the intersection variable


	
	if(player1.getShape().getPosition().y<400) //sets the player to jump if the player is on the ground so gravity can be applied 
	{
		player1.setisJumping(true);	

	}
	if (player2.getShape().getGlobalBounds().top<400) //sets the player to jump if the player is on the ground so gravity can be applied
	{
		player2.setisJumping(true);
	
	}

	
}




void Game::updatePlayerOrientation()
{
	player2.setMovementDirection(sf::Keyboard::isKeyPressed(sf::Keyboard::Left), sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
	player1.setMovementDirection(sf::Keyboard::isKeyPressed(sf::Keyboard::A), sf::Keyboard::isKeyPressed(sf::Keyboard::D));

	// Update texture orientation based on movement direction
	player1.updateTextureOrientation();
	player2.updateTextureOrientation();
}

void Game::update() //update function //game logic 

{
	this->pollEvents(); //call poll events
	
	this->checkPlayerCollision(player1, player2);
	this->player1.update(this->window);//update the player object
	this->player2.update(this->window);//update the player object



}
void Game::render() //render function //draws the game to the screen
{
	
		
	this->window->clear(); //clears the window
	this->updatePlayerOrientation(); //updates the player object orientation
	this->player1.render(this->window); //renders the player object
	this->player2.render(this->window); //renders the player object
	this->window->display(); //displays the game objects
	

	
	
}






