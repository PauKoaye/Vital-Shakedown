#include <iostream>
#include "../Header Files/Game.h"


int main()
{
   
    //init game object

    Game game;  //game object
    
    

    //game loop

    while (game.running())  //keep the window open until the user closes it
    {
		
         //update
       
        game.update();  //update the game object
		
	    //rendering

        game.render();  //render the game object

	}
       //end of game loop
    
    return 0;
}
 
