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
const int SIZE = 8;
float genNoise(sf::Vector2f);
sf::Vector2f pixels[SIZE + 1][SIZE + 1];
sf::Uint8* texels[640*640*4];
sf::Texture texture;


int main()
{
	//check if top and bottom flipped
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(640, 640, 32), "Perlin Noise", sf::Style::Titlebar | sf::Style::Close);
	sf::RenderTexture renderTexture;
	glewExperimental = GL_TRUE;
	glewInit();
	srand(time(NULL));
	texture.create(640,640);
	std::cout<< "start noise" << std::endl;
	for(int i = 0; i < SIZE + 1; ++i){
		for(int j = 0; j < SIZE + 1; ++j){
			pixels[i][j].x = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;//-1 to 1
			pixels[i][j].y = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
			
			float x = pixels[i][j].x;
			float y = pixels[i][j].y;
			float length = sqrt(x*x + y*y);
			pixels[i][j].x /= length;
			pixels[i][j].y /= length;
			std::cout << x  << " " << y << std::endl;
		}
	}
	std::cout << "end noise" << std::endl;
	sf::RectangleShape draw = sf::RectangleShape(sf::Vector2f(1,1));
	draw.setFillColor(sf::Color::White);
	for(int i = 0; i < 640; ++i){
		for(int j = 0; j < 640; ++j){
			float k = genNoise(sf::Vector2f(i,j)) + 1;
			//if(k > 2.01 || k < 0.01) std::cout << k;
			//std::cout << k << "\n";
			//float k = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//std::cout << k << std::endl;
			draw.setPosition(i,j);
			draw.setFillColor(sf::Color(k*127.0,k*127.0,k*127.0,255));
			window.draw(draw);
		}
	}
	std::cout << "draw";
	window.display();
	
	std::cin.get();
	return 0;
}

float genNoise(sf::Vector2f loc){
	sf::Vector2f a,b,c,d;
	a = pixels[(int)(loc.x/640*SIZE)][(int)(loc.y/640*SIZE)];        //x0y0
	b = pixels[(int)(loc.x/640*SIZE) + 1][(int)(loc.y/640*SIZE)];    //x1y0
	c = pixels[(int)(loc.x/640*SIZE)][(int)(loc.y/640*SIZE) + 1];            //x0y1
	d = pixels[(int)(loc.x/640*SIZE) + 1][(int)(loc.y/640*SIZE) + 1];        //x1y1
	//std::cout << (int)loc.x/10 << std::endl;
	
	//std::cin.get();
	//float alen,blen,clen,dlen;

	float ax, ay, bx, by, cx, cy, dx, dy;
	ax = (int)(loc.x/640*SIZE);
	ay = (int)(loc.y/640*SIZE);
	bx = (int)(loc.x/640*SIZE) + 1;
	by = (int)(loc.y/640*SIZE);
	cx = (int)(loc.x/640*SIZE);
	cy = (int)(loc.y/640*SIZE) + 1;
	dx = (int)(loc.x/640*SIZE) + 1;
	dy = (int)(loc.y/640*SIZE) + 1;
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
	s = a.x * ((loc.x/640.0*SIZE - ax)) + a.y * ((loc.y/640.0*SIZE - ay)); 
	t = b.x * ((loc.x/640.0*SIZE - bx)) + b.y * ((loc.y/640.0*SIZE - by));
	u = c.x * ((loc.x/640.0*SIZE - cx)) + c.y * ((loc.y/640.0*SIZE - cy));
	v = d.x * ((loc.x/640.0*SIZE - dx)) + d.y * ((loc.y/640.0*SIZE - dy));
//	float Sx =  6*pow(s,5) - 15 * pow(s,4) + 10 * pow(s,3);//(s5 - 15x4 + 10x3 
//	float Sx =  6*pow(s,5) - 15 * pow(s,4) + 10 * pow(s,3);
	float lerpX = loc.x/640*SIZE - ax;
	float lerpY = loc.y/640*SIZE - ay;
	float st = ease(s , t , lerpX);
	float uv = ease(u , v , lerpX);
	return ease(st, uv, lerpY);
}


float lerp(float a, float b, float x){
	return (a * (1 - x) + b * x);
}

float ease(float a, float b, float x){
	float Sx = 3 * pow(x , 2) - 2 * pow(x , 3);
	return a + Sx*(b-a);
}