
struct Node;
enum Directions{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//Should only be created as a pointer
struct Node{
	Node* next;
	int x;
	int y;
	Directions dir;
	Node(int,int,Directions);
	~Node();
	Node( const Node&);
};

