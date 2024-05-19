#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
    //creation of the game window
    
    sf::RenderWindow window(sf::VideoMode(640, 480), "Vital Shakedown", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;   //event object to handle events within the window
   
    //game loop

    while (window.isOpen())
    {
		//event handling
        
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
           
              case sf::Event::Closed:  //close the window manually when user clicks on the close button
				window.close();
				break;

                case sf::Event::KeyPressed:  //event handling for key presses

                    if (ev.key.code == sf::Keyboard::Escape)  //close the window when user presses the escape key
                    {
						window.close();
					}

            }
		}
		
		
        //update
		
		//rendering
		window.clear(); //clear old frame
       
        window.display(); //window is drawn to the screen
	}
       //end of game loop
    
    return 0;
}
 
