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

void Player::initializationTexture()
{
	if (!this->texture.loadFromFile("Textures/anim.png")) { //loads the texture from the file

		std::cout << "ERROR::PLAYER::INITIALIZATIONTEXTURE::Could not load texture file." << "\n";
	}


}


void Player::initializationShape()
{	this->currentFrame = sf::IntRect(0, 0, 17, 33); //sets the current frame of the player texture
	this->shape.setTexture(this->texture); //sets the texture of the shape to the texture of the player
	this->shape.setTextureRect(this->currentFrame); //sets the texture rectangle of the shape of the player texture
	this->shape.setScale(10.f, 10.f); //scales the shape 10 time -> 160x320
	
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


void Player::healthDecrease(float damage, bool isLeftPlayer){
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
	this->initializationTexture();
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
			this->hasJumped = true;
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
    sf::Vector2f playerPosition = this->shape.getPosition(); // gets the position of the player
    sf::FloatRect bounds = this->shape.getGlobalBounds(); // gets the global bounds of the shape

    // bottom collision
    if (bounds.top + bounds.height >= target->getSize().y) // checks if the player has reached the bottom of the window
    {
        this->shape.setPosition(playerPosition.x, target->getSize().y - bounds.height); // sets the position of the player to the bottom of the window
        this->isJumping = false; // sets the isJumping variable to false
        this->verticalSpeed = 0.f; // sets the vertical speed to 0
    }

    // left collision
    if (bounds.left <= 0.f)
    {
        this->shape.setPosition(0.f, playerPosition.y); // sets the position of the player to the left side of the window
        this->healthDecrease(1.f, isLeftPlayer); // calls the health decrease function
    }

    // right collision
    if (bounds.left + bounds.width >= target->getSize().x)
    {
        this->shape.setPosition(target->getSize().x - bounds.width, playerPosition.y); // sets the position of the player to the right side of the window
        this->healthDecrease(1.f, isLeftPlayer); // calls the health decrease function
    }
	
}


float Player::getHealth() const
{
	return health;
}

sf::Sprite& Player::getShape()
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

void Player::setMovementDirection(bool left, bool right)
{
	movingLeft = left;
	movingRight = right;
}


// Update texture orientation based on movement direction
void Player::updateTextureOrientation()
{
		if (movingLeft) {
		shape.setScale(-10.f, 10.f); // Flip horizontally if moving left
	}
	else if (movingRight) {
		shape.setScale(10.f, 10.f); // Set to normal orientation if moving right
	}
}




//update function for player

	void Player::update(const sf::RenderTarget* target)
	{
		
		//apply gravity
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





