#include "../Header Files\Player.h"
#include <iostream>

const float GroundPosition = 420.f; //sets the ground position to 720.f


void Player::initializationVariables()
{
	this->movementSpeed = 5.f;
	this->jumpSpeed = 350.f;
	this->gravity = 0.3f;
	this->isJumping = false;
	this->verticalSpeed = 0.f;

	
	
}

void Player::initializationShape()
{
	this->shape.setSize(sf::Vector2f(100.f, 200.f));
	this->shape.setFillColor(this->color);
	
}
// constructor 

Player::Player(float ix, float iy, const sf::Color& playerColor, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey)
{
	//x=100.f;	
	//y=GroundPosition;
	x=ix;
	y=iy;

	color = playerColor;
	moveLeftKey = leftKey;
	moveRightKey = rightKey;
	this->jumpKey = jumpKey;
	this->shape.setPosition(x, y);
	this->initializationVariables();
	this->initializationShape();
} 

// default destructor
Player::~Player()
{
}


// functions

//keyboard input handling
void Player::inputUpdate()
{
	//left movement
	if (sf::Keyboard::isKeyPressed(this->moveLeftKey)) {

		this->shape.move(-this->movementSpeed, 0.f);

	}
	//right movement
	else if (sf::Keyboard::isKeyPressed(this->moveRightKey)) {

		this->shape.move(this->movementSpeed, 0.f);

	}

	//jumping

	if (sf::Keyboard::isKeyPressed(this->jumpKey) && !this->isJumping)
	{
		
			this->isJumping = true;
			this->shape.move(0.f, -this->jumpSpeed);
		
	}
	

}

//window bounds collision
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	sf::Vector2f playerPosition = this->shape.getPosition(); //gets the position of the player


	//bottom collision

	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y) //checks if the player has reached the bottom of the window
	{
		this->shape.setPosition(playerPosition.x, target->getSize().y - this->shape.getGlobalBounds().height); //sets the position of the player to the bottom of the window
		this->isJumping = false; //sets the isJumping variable to false
		this->verticalSpeed = 0.f; //sets the vertical speed to 0
	}


	//left collision
	
	if (this->shape.getGlobalBounds().left <= 0.f) {
		
		this->shape.setPosition(0.f, playerPosition.y); //sets the position of the player to the left side of the window, at the y position of the player before collision
	}
	//right collision
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x) {
		
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, playerPosition.y); //sets the position of the player to the right side of the window, at the y position of the player before collision
	}


}
//update function for player
void Player::update(const sf::RenderTarget* target)
{
	if (this->isJumping) {
	this->verticalSpeed += this->gravity;

	this->shape.move(0.f, this->verticalSpeed);
	
	} 
	this ->updateWindowBoundsCollision(target); // calls the window bounds collision function
	this->inputUpdate(); // calls the input update function



}



void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);

}


