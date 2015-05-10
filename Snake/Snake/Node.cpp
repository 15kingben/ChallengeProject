#include "Node.h"
#include <iostream>
Node::Node(int _x,int _y, Directions _dir){
	x = _x;
	y = _y;
	dir = _dir;
}

Node::Node(const Node& N){
	x = N.x;
	y = N.y;
	if(N.next != nullptr){
		next = N.next;
	}
}

Node::~Node(){
	if(next != nullptr){
		delete next;
	}
}