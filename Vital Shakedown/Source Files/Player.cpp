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
void Player::initializationHealthBar(bool isLeftPlayer)
{
	this->healthBar.setSize(sf::Vector2f(300.f, 40.f));
	this->healthBar.setFillColor(this->color); // sets the color of the health bar to the color of the player
	
	if (isLeftPlayer) {
		this->healthBar.setPosition(50.f, 50.f); //sets the position of the health bar to the left side of the window
	}
	else {
		this->healthBar.setPosition(720.f, 50.f); //sets the position of the health bar to the right side of the window
	}
}
void Player::healthDecrease(float damage, bool isLeftPlayer)
{
	if (health>0) { //checks if the health of the player is greater than 0
		
		if (isLeftPlayer) {
			this->healthBar.setSize(sf::Vector2f(this->healthBar.getSize().x - damage, this->healthBar.getSize().y)); //decreases the size of the health bar when the player is hit
			this->health -= damage/3; //decreases the health of the player when the player is hit by the value of the damage parameter divided by 3 as the player has 100hp and the shape is 300 pixels wide
		}
		else {
			this->healthBar.setSize(sf::Vector2f(this->healthBar.getSize().x - damage, this->healthBar.getSize().y)); //decreases the size of the health bar when the player is hit
			this->health -= damage/3;
		}

	}
}


// constructor 

Player::Player(float ix, float iy, const sf::Color& playerColor, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey, bool isLeftPlayer) 
{
	//x=100.f;	
	//y=GroundPosition;
	x=ix;
	y=iy;

	color = playerColor;
	moveLeftKey = leftKey;
	moveRightKey = rightKey;
	this->jumpKey = jumpKey;
	this->isLeftPlayer= isLeftPlayer; //sets the isLeftPlayer variable to the value of the isLeftPlayer parameter when the object is created
	this->shape.setPosition(x, y);
	this->initializationVariables();
	this->initializationShape();
	this->initializationHealthBar(isLeftPlayer);
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

void Player::setisJumping(bool isJumping)
{
	this->isJumping = isJumping;
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
		this->healthDecrease(1.f, isLeftPlayer); //calls the health decrease function

	}
	
	//right collision
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x) {
		
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, playerPosition.y); //sets the position of the player to the right side of the window, at the y position of the player before collision
		this->healthDecrease(1.f, isLeftPlayer); //calls the health decrease function
	}


}

float Player::getHealth()
{
	return health;
}

sf::RectangleShape& Player::getShape()
{
	return shape;
}




void Player::handleCollision(sf::FloatRect intersection)
{
	float overlapX = intersection.width;
	float overlapY = intersection.height;
	
	if (overlapX < overlapY) {
		// Adjust horizontally
		float moveAmount = overlapX / 2.f; // divide by 2 to move the minimum amount to resolve the collision //creates the illusion that the players stand still when both pushing into each other
		if (shape.getPosition().x < intersection.left) {
			shape.move(-moveAmount, 0.f);
		}
		else {
			shape.move(moveAmount, 0.f);
		}
	}
	else {
		// Adjust vertically
		float moveAmount = overlapY;
		if (shape.getPosition().y< intersection.top) {
			shape.move(0.f, -moveAmount);
			this->isJumping = false;
			this->verticalSpeed = 0.f;
		}
		
	}


}



//update function for player

	void Player::update(const sf::RenderTarget * target)
	{
	

		if (this->isJumping) {
			this->verticalSpeed += this->gravity;

			this->shape.move(0.f, this->verticalSpeed);

		}
			this->updateWindowBoundsCollision(target); // calls the window bounds collision function
			this->inputUpdate(); // calls the input update function
			
	
	}

	




void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->healthBar);

}





