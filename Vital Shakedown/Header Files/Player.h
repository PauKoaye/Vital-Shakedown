#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>



class Player
{
private:
	sf::RectangleShape shape; //player shape
	sf::RectangleShape healthBar; //health bar of the player
	float movementSpeed;
	void initializationVariables(); 
	void initializationShape();
	void initializationHealthBar(bool isLeftPlayer);
	void healthDecrease(float damage, bool isLeftPlayer); // Decrease the health of the player
	float jumpSpeed;
	float gravity;
	bool isJumping;
	float verticalSpeed;
	float x;
	float y;
	sf::FloatRect intersection;		//intersection of the two players when they collide
	float health = 100.f;		//initial health of the player
	bool isLeftPlayer=true; //if the player is the left player
	
	//control keys
	sf::Keyboard::Key moveLeftKey; // Key to move left
	sf::Keyboard::Key moveRightKey; // Key to move right
	sf::Keyboard::Key jumpKey; // Key to jump

	
	//color variables
	
	sf::Color color; // Color of the player
	sf::Color healthBarColor; // Color of the health bar

	

	

public:
	
	//constructor
	Player(float ix=0.f, float iy=0.f, const sf::Color& playerColor = sf::Color::Green, 
		sf::Keyboard::Key leftKey = sf::Keyboard::A, sf::Keyboard::Key rightKey = sf::Keyboard::D, sf::Keyboard::Key jumpKey = sf::Keyboard::W, bool isLeftPlayer = true); // Constructor of the player
	
	//destructor
	virtual ~Player(); // Destructor of the player

	


	//accessors
	float getHealth(); // Get the health of the player
	void setisJumping(bool isJumping); // Set the jumping state of the player
	
	//functions
	void handleCollision(sf::FloatRect intersection); // Handle the collision with another player
	sf::RectangleShape& getShape(); // Get the shape of the player
	
	
	//update and render functions
	void inputUpdate(); // Update the input of the player
	void updateWindowBoundsCollision(const sf::RenderTarget* target); // Update the collision with the window bounds
	void update(const sf::RenderTarget* target); // Update the player
	void render(sf::RenderTarget* target); // Render the player

};

