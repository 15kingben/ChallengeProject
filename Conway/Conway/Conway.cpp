// Conway.cpp : Defines the entry point for the console application.
//




#include <extlibs/headers/GL/glew.h>
#include <GL/GLU.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>
//#include <SOIL.h>
#include <iostream>
void changeNode(const int&, const int&);
void displayNodes();
void calcLife();

bool nodes[64][64];
bool nodesCopy[64][64];
bool running;
sf::RenderTexture renderTexture;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 640, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close);
	glewExperimental = GL_TRUE;
	glewInit();
	renderTexture.create(640,640);

	// drawing uses the same functions
	
	//renderTexture.draw(sprite); // or any other drawable
	renderTexture.display();
	sf::Clock clock;
	clock.restart();
	// get the target texture (where the stuff has been drawn)
	//sf::Texture& texture = renderTexture.getTexture();
	bool spacePress;
	bool mousePress = false;

	sf::Event windowEvent;
	while(window.isOpen()){
		while (window.pollEvent(windowEvent))
		{//Event Handling
			switch (windowEvent.type)
			{
				//running = false;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					running = true;
				}
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					running = false;
				}
				break;

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				mousePress = false;
				break;
			case sf::Event::MouseButtonPressed:
				if(!mousePress){
					changeNode(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
					
					mousePress = true;
				}
				break;
			}
		}//\EventHandling

		displayNodes();
		sf::Texture texture = renderTexture.getTexture();

		// draw it to the window
		sf::Sprite sprite(texture);
		window.draw(sprite);

		if(running)
		{
			sf::Time t = clock.getElapsedTime();
			if(t.asMilliseconds() > 50){
				calcLife();
				clock.restart();
			}
		}else{
			clock.restart();
		}
		
		window.display();
	}

}

//switch node based on local mouse coords
//only works with 64x64 node array and 640x640 window
void changeNode(const int& x, const int& y){
	if(nodes[(x/10)][y/10])
		nodes[(x/10)][y/10] = false;
	else
		nodes[(x/10)][y/10] = true;
}

void displayNodes()
{
			sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(10,10));
			for(int x = 0; x < 64; ++x){
				for(int y = 0; y < 64; ++y){
					
					node.setPosition(sf::Vector2f(x * 10, y * 10));
					if(nodes[x][y])
						node.setFillColor(sf::Color::White);
					else
						node.setFillColor(sf::Color::Black);
					renderTexture.draw(node);
				}
			}
}

void calcLife(){
	std::cout << "call";
	for(int x = 0; x < 64; ++x){
		for(int y = 0; y < 64; ++y){
			
			int lifeCount = 0;
			if(x - 1 >= 0){
				if(nodes[x-1][y]){
					lifeCount++;
				}
			}
			if(y - 1 >= 0){
				if(nodes[x][y - 1]){
					lifeCount++;
				}
			}
			if(x - 1 >= 0 && y - 1 >= 0 ){
				if(nodes[x - 1][y - 1]){
					lifeCount++;
				}
			}


			if(x - 1 >= 0 && y + 1 < 64){
				if(nodes[x - 1][y + 1]){
					lifeCount++;
				}
			}
			if(y + 1 < 64){
				if(nodes[x][y + 1]){
					lifeCount++;
				}
			}
			if(x + 1 < 64 && y + 1 < 64){
				if(nodes[x + 1][y + 1]){
					lifeCount++;
				}
			}
			if(x + 1 < 64){
				if(nodes[x + 1][y]){
					lifeCount++;
				}
			}
			if(x + 1 < 64 && y - 1 >= 0){
				if(nodes[x + 1][y - 1]){
					lifeCount++;
				}
			}

			if(lifeCount == 2){//broken
				//std::cout << nodes[x][y] << " ";
				//std::cout << x << " " << y << std::endl;
				if(nodes[x][y])
					nodesCopy[x][y] = true;
				else
					nodesCopy[x][y] = false;
				//std::cout << (nodesCopy[x][y]);
				//nodesCopy[x][y] = nodes[x][y];
			}else if(lifeCount == 3){
				//std::cout << nodes[x][y] << " ";
				//std::cout << x << " " << y << std::endl;
				nodesCopy[x][y] = true;
			}else{
				nodesCopy[x][y] = false;
			}

		}
	}

	for(int x = 0; x < 64; ++x){
		for(int y = 0; y < 64; ++y){
			nodes[x][y] = nodesCopy[x][y];
		}
	}
}