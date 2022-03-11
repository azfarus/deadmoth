#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>
#include <dos.h>
#define nodes 5
#define edges 3
class node
{
public:
	std::vector<sf::Vector2f> connectedNodes;
	sf::Vector2f myPos;
	sf::CircleShape circle;
	int connections = 0;
	//long double distancem = 1e10;
	//int flag = 0;
	

	void drawNode(sf::RenderWindow& window)
	{
		circle.setOrigin(sf::Vector2f(5, 5));
		circle.setPosition(myPos);
		circle.setRadius(5.0);
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = myPos;
		window.draw(circle);
		for (size_t i = 0; i < connectedNodes.size(); i++)
		{
			line[1].position = connectedNodes[i];
			window.draw(line);
		}

	}
	void nodePush(sf::Vector2f &n)
	{
		connectedNodes.push_back(n);
	}
	
};

void connect(node *a, node  *b )
{
	//if (a->connections < edges && b->connections <= edges)
	{
		a->nodePush(b->myPos);
		b->nodePush(a->myPos);
		a->connections++;
		b->connections++;
		return;
	}
	return;
	
	//a->flag = b->flag = 0;
	

}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "lines",sf::Style::Fullscreen);
	node graph[nodes];
	bool inserted[nodes];
	int x, y;

	
	memset(inserted, 0, sizeof(inserted));
	
	std::vector<sf::Vector2f> pointGula;
	for (int i = 0; i < nodes; )
	{
		x = rand()%1920;
		y = rand()%1080;
		sf::Vector2f point = { (float)x,(float)y };
		auto it = find(pointGula.begin(), pointGula.end(), point);
		if (it == pointGula.end())
		{
			std::cout << "pushed"<<sizeof(graph)<<"\n";
			pointGula.push_back(point);
			graph[i].myPos = point;
			i++;

		}
		
	}

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < edges ; j++)
		{
			std::cout << "connecting" << sizeof(node) << "\n";
			if (j != i) connect(graph + i, graph + j);
			//inserted[j] = true;
		}
	}
	while (window.isOpen())
	{
		sf::Event eve;
		while (window.pollEvent(eve))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		for (int i = 0; i < nodes;i++ )
		{
			graph[i].drawNode(window);

		}
		window.display();
	}

}