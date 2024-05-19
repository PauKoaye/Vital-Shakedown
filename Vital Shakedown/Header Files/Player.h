#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Player
{
private:
	sf::RectangleShape shape; //player shape
	float movementSpeed; 
	void initializationVariables(); 
	void initializationShape();
	float jumpSpeed;
	float gravity;
	bool isJumping;
	float verticalSpeed;
	float x;
	float y;


	//control keys

	sf::Keyboard::Key moveLeftKey;
	sf::Keyboard::Key moveRightKey;
	sf::Keyboard::Key jumpKey;

	//variable color
	
	sf::Color color; // Color of the player


	

public:
	
	//constructor with default values
	Player(float ix=0.f, float iy=0.f, const sf::Color& playerColor = sf::Color::Green, 
		sf::Keyboard::Key leftKey = sf::Keyboard::A, sf::Keyboard::Key rightKey = sf::Keyboard::D, sf::Keyboard::Key jumpKey = sf::Keyboard::W); // Constructor with default color
	
	//destructor
	virtual ~Player();

	void inputUpdate();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target); 
	void render(sf::RenderTarget* target);


};

