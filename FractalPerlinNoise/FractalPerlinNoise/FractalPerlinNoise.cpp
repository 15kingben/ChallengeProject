// PerlinNoise.cpp : Defines the entry point for the console application.
//

#include <extlibs/headers/GL/glew.h>
#include <GL/GLU.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h> 
//#include <SOIL.h>
#include <iostream>
float lerp(float, float, float);
float ease(float, float, float);
void display(sf::RenderWindow&);
//template <size_t> void drawNoise(sf::RenderWindow&, sf::Vector2f[][]);
//template <size_t> void genRandom(sf::Ve`ctor2f[][]);
//template <size_t> void genNoise(sf::Vector2f, sf::Vector2f[][]);
const int SIZE = 8;
float pixels[640][640];
//float genNoise(sf::Vector2f);
sf::Texture texture;



float genNoise(sf::Vector2f loc, sf::Vector2f** gradients, size_t size){
	sf::Vector2f a,b,c,d;
	a = gradients[(int)(loc.x/640*size)][(int)(loc.y/640*size)];        //x0y0
	b = gradients[(int)(loc.x/640*size) + 1][(int)(loc.y/640*size)];    //x1y0
	c = gradients[(int)(loc.x/640*size)][(int)(loc.y/640*size) + 1];            //x0y1
	d = gradients[(int)(loc.x/640*size) + 1][(int)(loc.y/640*size) + 1];        //x1y1
	//std::cout << (int)loc.x/10 << std::endl;
	
	//std::cin.get();
	//float alen,blen,clen,dlen;

	float ax, ay, bx, by, cx, cy, dx, dy;
	ax = (int)(loc.x/640*size);
	ay = (int)(loc.y/640*size);
	bx = (int)(loc.x/640*size) + 1;
	by = (int)(loc.y/640*size);
	cx = (int)(loc.x/640*size);
	cy = (int)(loc.y/640*size) + 1;
	dx = (int)(loc.x/640*size) + 1;
	dy = (int)(loc.y/640*size) + 1;
	//std::cout << "a " << ax << " " << ay << " " << "b " << bx << " " << by << " " << "c " << cx << " " << cy << " " << "d " << dx << " " << dy << std::endl; 
	//std::cout << ay << "\n";
	//std::cout << "loc " << loc.x<< " " << loc.y << std::endl;
	//std::cout << "loc " << loc.x/640*SIZE<< " " << loc.y/640*SIZE << std::endl;
	//std::cout << loc.x/640*SIZE - dx;
	//std::cout << loc.y/640*SIZE - dy;
	//std::cin.get();
	float s,t,u,v;

	/*s = a.x * ((ax - loc.x/10.0)) + a.y * ((ay - loc.y/10.0)); 
	t = b.x * ((bx - loc.x/10.0)) + b.y * ((by - loc.y/10.0));
	u = c.x * ((cx - loc.x/10.0)) + c.y * ((cy - loc.y/10.0));
	v = d.x * ((dx - loc.x/10.0)) + d.y * ((dy - loc.y/10.0));*/
	s = a.x * ((loc.x/640.0*size - ax)) + a.y * ((loc.y/640.0*size - ay)); 
	t = b.x * ((loc.x/640.0*size - bx)) + b.y * ((loc.y/640.0*size - by));
	u = c.x * ((loc.x/640.0*size - cx)) + c.y * ((loc.y/640.0*size - cy));
	v = d.x * ((loc.x/640.0*size - dx)) + d.y * ((loc.y/640.0*size - dy));
//	float Sx =  6*pow(s,5) - 15 * pow(s,4) + 10 * pow(s,3);//(s5 - 15x4 + 10x3 
//	float Sx =  6*pow(s,5) - 15 * pow(s,4) + 10 * pow(s,3);
	float lerpX = loc.x/640*size - ax;
	float lerpY = loc.y/640*size - ay;
	float st = ease(s , t , lerpX);
	float uv = ease(u , v , lerpX);
	return ease(st, uv, lerpY);
}


void genRandom(sf::Vector2f** gradients, size_t size, float amplitude){
	for(int i = 0; i < size + 1; ++i){
		for(int j = 0; j < size + 1; ++j){
			gradients[i][j].x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 * amplitude - amplitude;//-1 to 1
			gradients[i][j].y = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 * amplitude - amplitude;
			
			float x = gradients[i][j].x;
			float y = gradients[i][j].y;
			float length = sqrt(x*x + y*y);
			//gradients[i][j].x /= length;
			//gradients[i][j].y /= length;
			//std::cout << x  << " " << y << std::endl;
		}
	}
}


void drawNoise(sf::RenderWindow &window, sf::Vector2f** gradients, size_t size, float per){
	
	for(int i = 0; i < 640; ++i){
		for(int j = 0; j < 640; ++j){
			float k = genNoise(sf::Vector2f(i,j), gradients, size);
			//k *= per;
			//if(k > 2.01 || k < 0.01) std::cout << k;
			//std::cout << k << "\n";
			//float k = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//std::cout << k << std::endl;
			pixels[i][j] += k;
		}
	}
}


int main()
{
	//check if top and bottom flipped
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(640, 640, 32), "Perlin Noise", sf::Style::Titlebar | sf::Style::Close);
	sf::RenderTexture renderTexture;
	glewExperimental = GL_TRUE;
	glewInit();
	srand(time(NULL));
	texture.create(640,640);
	const float PERSISTENCE = .5;
	float i = 0;
	int count = 0;
	for( i = 2; i < 129; i /= PERSISTENCE){
		std::cout << i;
		sf::Vector2f** gradients;
		gradients = new sf::Vector2f* [1 + (int)i];
		for(int j = 0; j < (int)i + 1; j++){
			gradients[j] = new sf::Vector2f[(int)i + 1];
		}
		genRandom(gradients, i, 1 / i);
		drawNoise(window, gradients, i, 1 / i);
		for(int j = 0; j < (int)i + 1; j++){
			delete[] gradients[j];
		}
		delete[] gradients;
		
		//std::cin.get();
	}

	display(window);
	
	std::cout << "draw";
	window.display();
	
	std::cin.get();
	return 0;
}




float lerp(float a, float b, float x){
	return (a * (1 - x) + b * x);
}

float ease(float a, float b, float x){
	float Sx = 3 * pow(x , 2) - 2 * pow(x , 3);
	return a + Sx*(b-a);
}
void display(sf::RenderWindow &window){
	sf::RectangleShape draw = sf::RectangleShape(sf::Vector2f(1,1));
for(int i = 0; i < 640; i++){
		for(int j = 0; j < 640; j++){
			
			draw.setFillColor(sf::Color::White);
			float k = pixels[i][j] + 1;
			//std::cout << k << std::endl;
			draw.setPosition(i,j);
			draw.setFillColor(sf::Color(k*127.0,k*127.0,k*127.0,255));
			window.draw(draw);
		}
	}
}