// Snake.cpp : Defines the entry point for the console application.
//


#define GLEW_STATIC

// Headers
#include <extlibs/headers/GL/glew.h>
#include <GL/GLU.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <assert.h>
#include "Node.h"
//#include <SOIL.h>
#include <iostream>

void updatePos(Node&);
void displaySnake(Node&);
bool checkBounds(const Node&);
void checkIntersect(const Node&);
void updateDir(Node&);
Node* getEnd(Node&);
sf::RenderTexture renderTexture;
const int SIZE = 16;
bool blacklist[SIZE][SIZE];
bool gameOver;
int foodX = SIZE*.75;
int foodY = SIZE*.75;
bool newFood = false;

int main(){
	Node* head = new Node(SIZE / 2,SIZE/2,UP);
	head->next = new Node(SIZE/2,SIZE/2-1,UP);
	head->next->next = new Node(SIZE/2,SIZE/2 - 2,UP);
	head->next->next->next = new Node(SIZE/2,SIZE/2-3,UP);
	head->next->next->next->next = new Node(SIZE/2,SIZE/2-4,UP);
	head->next->next->next->next->next = nullptr;
	float speed = 150;
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile("boop.wav");
	sf::Sound sound;
	sound.setBuffer(soundBuffer);
	gameOver = false;
	  srand (time(NULL));

	//sq[32][32] = UP;
	//sq[32][31] = UP;
	//sq[32][30] = UP;
	//sq[32][29] = UP;
	//sq[32][28] = UP;
	for(int x = 0; x <SIZE; x++){
		for( int y = 0; y < SIZE; y++){
			blacklist[x][y] = false;
		}
	}
	

	sf::RenderWindow window(sf::VideoMode(640, 640, 32), "Snake", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	clock.restart();
	sf::Event windowEvent;
	renderTexture.create(640,640);
	renderTexture.display();
	sf::Texture gameOverScreen;
	gameOverScreen.loadFromFile("gameover.png", sf::IntRect(320,192,640,640));
	sf::Sprite sprite;
	sprite.setTexture(gameOverScreen);
	bool upPress, downPress, leftPress, rightPress = false;
	int addCount = 0;
	int soundCount = 0;

	while(window.isOpen()){
		bool anyEvent = false ;
		while (window.pollEvent(windowEvent))
		{//Event Handling
			anyEvent = true;
			switch (windowEvent.type)
			{
				//running = false;
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
					//std::cout << "left" << leftPress <<"\n";
					if(head->dir != RIGHT && !leftPress){
						head->dir = LEFT;
						leftPress = true;
					}
				}else{
					leftPress = false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
					//std::cout << "right\n";
					if(head->dir != LEFT && !rightPress){
						head->dir = RIGHT;
						rightPress = true;
					}
				}else{
					//std::cout << "rightcall";
					rightPress = false;
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){//inverted
					//std::cout << "down\n";
					if(head->dir != DOWN && !upPress){
						head->dir = UP;
						upPress = true;
					}
				}else{
					upPress = false;
				}


				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){//inverted
					//std::cout << "up\n";
					if(head->dir != UP && !downPress){
						head->dir = DOWN;
						downPress = true;
					}
				}else{
					downPress = false;
				}

				break;

			case sf::Event::Closed:
				//delete head;
				window.close();
				break;

			}
		}//\EventHandling
		if(!anyEvent){
			leftPress = false;
			rightPress = false;
			upPress = false;
			downPress = false;
		}
		anyEvent = false;


		//for(int x = 0; x < 64; ++x){
		//	for(int y = 0; y < 64; ++y){
		sf::Time t = clock.getElapsedTime();
		if(t.asMilliseconds() > speed){
			updatePos(*head);
			updateDir(*head);
			soundCount++;
			if(soundCount > 5){
				sound.play();
				soundCount = 0;
			}
			clock.restart();
			if(!gameOver)
				gameOver = !checkBounds(*head);
			checkIntersect(*head);//gen blacklist
			if(addCount > 0){
				--addCount;
				Node* end = getEnd(*head);
				switch(end->dir){
				case UP:
					end->next = new Node(end->x, end->y - 1, end->dir);//backwards
					break;
				case DOWN:
					end->next = new Node(end->x, end->y + 1, end->dir);//backwards
					break;
				case LEFT:
					end->next = new Node(end->x + 1, end->y, end->dir);//backwards
					break;
				case RIGHT:
					end->next = new Node(end->x - 1, end->y, end->dir);//backwards
					break;}
				end->next->next = nullptr;
			}

			if(newFood){
				addCount = 4;
				if(speed >100){
				speed *= .95;
				//sound.setPitch(sound.getPitch()*1.1);
				}
				foodX = rand() % SIZE;
				foodY = rand() % SIZE;
				while(blacklist[foodX][foodY] == true){
					foodX = rand() % SIZE;
					foodY = rand() % SIZE;
				}

				newFood = false;
			}
		}
		if(gameOver){
			window.draw(sprite);
			window.display();
			gameOver = false;
			sf::Time t = sf::seconds(.5);
			for(int i = 0; i < 6; ++i)
			sf::sleep(t);
			delete head->next;
			head->x = SIZE/2;
			head->y = SIZE/2;
			head->next = new Node(SIZE/2,SIZE/2-1,UP);
			head->next->next = new Node(SIZE/2,SIZE/2 - 2,UP);
			head->next->next->next = new Node(SIZE/2,SIZE/2-3,UP);
			head->next->next->next->next = new Node(SIZE/2,SIZE/2-4,UP);
			head->next->next->next->next->next = nullptr;
			float speed = 150;
			foodX = SIZE*.75;
			foodY = SIZE*.75;
			newFood = false;
		}
		if(!gameOver){
			displaySnake(*head);
			
			sf::RectangleShape draw1 = sf::RectangleShape(sf::Vector2f(640/SIZE,640/SIZE));
			draw1.setPosition(sf::Vector2f(foodX * (640/SIZE), foodY * (640/SIZE)));
			draw1.setFillColor(sf::Color::White);
			renderTexture.draw(draw1);
		}
		sf::Texture texture = renderTexture.getTexture();
		// draw it to the window
		sf::Sprite sprite(texture);
		window.draw(sprite);
		window.display();
		renderTexture.clear();
		for(int x = 0; x < SIZE; x++){
			for( int y = 0; y < SIZE; y++){
				blacklist[x][y] = false;
			}
		}
	}
}

void updatePos(Node &node){
	//std::cout << "call";
	int xRes,yRes;
	Directions dir = node.dir;
	if(node.next != nullptr){
		updatePos(*node.next);
	}else{
		xRes = node.x;
		yRes = node.y;
	}
	switch(dir){
	case UP:
		node.y += 1;
		break;
	case DOWN:
		node.y -= 1;
		break;
	case LEFT:
		node.x -= 1;
		break;
	case RIGHT:
		node.x += 1;
		break;
	}
}

sf::RectangleShape draw = sf::RectangleShape(sf::Vector2f((640/SIZE),(640/SIZE)));

bool checkBounds(const Node &node){
	if(node.x > SIZE - 1 || node.x < 0 || node.y < 0 || node.y > SIZE - 1){
		return false;
	}else if(node.next != nullptr)
			return (true && checkBounds(*node.next));
	else
		return true;
}

void displaySnake(Node &node)
{
	draw.setPosition(sf::Vector2f(node.x * (640/SIZE), node.y * (640/SIZE)));
	draw.setFillColor(sf::Color::White);
	//draw.setFillColor(sf::Color::Black);
	renderTexture.draw(draw);
	if(node.next != nullptr)
		displaySnake(*node.next);	
}

void updateDir(Node &node){
	if(node.next != nullptr){
	updateDir(*node.next);
	node.next->dir = node.dir;
	}
}

void checkIntersect(const Node &node){
	if(node.x == foodX && node.y == foodY){
		newFood = true;
	}
	
	//Gen Blacklist
	if(blacklist[node.x][node.y])
		gameOver = true;
	else{
		blacklist[node.x][node.y] = true;
	}if(node.next != nullptr)
		checkIntersect(*node.next);
}

Node* getEnd(Node &node){
	if(node.next == nullptr){
		return &node;
	}else{
		return getEnd(*node.next);
	}
}