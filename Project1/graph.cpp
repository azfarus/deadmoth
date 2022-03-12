#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>
#include <dos.h>
#define nodes 50
#define edges 7
#define ends 36
#define rad 10

std::vector<int> path;


class node
{
public:
	std::vector<sf::Vector2f> connectedNodes;
	sf::Vector2f myPos;
	sf::CircleShape circle;
	
	float distance = 1e10;
	int find = 0, visited = 0 , shuru = 0 ;
	

	void drawNode(sf::RenderWindow& window)
	{
		sf::VertexArray line(sf::Lines, 2);


		circle.setOrigin(sf::Vector2f(rad, rad));
		circle.setPosition(myPos);
		if (shuru)
		{
			circle.setFillColor(sf::Color::Magenta);
		}
		else if (visited)
		{
			circle.setFillColor(sf::Color::Cyan);
		}
		
		else if (find)
		{
			circle.setFillColor(sf::Color::Yellow);
		}
		else circle.setFillColor(sf::Color::Red);
		circle.setRadius(rad);
		line[0].position = myPos;
		
		for (size_t i = 0; i < connectedNodes.size(); i++)
		{
			line[1].position = connectedNodes[i];
			window.draw(line);
		}
		window.draw(circle);

	}
	void nodePush(sf::Vector2f &n)
	{
		connectedNodes.push_back(n);
	}
	
};

void drawPath(node* graph, sf::RenderWindow &window)
{
	sf::VertexArray line(sf::Lines, 2);;
	for (unsigned int i = 0; i < (path.size()-1); i++)
	{
		line[0].position = graph[path[i]].myPos; line[0].color = sf::Color::Green;
		line[1].position = graph[path[i + 1]].myPos; line[1].color = sf::Color::Green;
		window.draw(line);
	}
}

void connect(node *a, node  *b )
{
	//if (a->connections < edges && b->connections <= edges)
	{
		a->nodePush(b->myPos);
		b->nodePush(a->myPos);
		
		return;
	}
	return;
	
	//a->flag = b->flag = 0;
	

}

int findNode(node* graph, int nodeCount, sf::Vector2f nodepos)
{
	for (int i = 0; i < nodeCount; i++)
	{
		if (graph[i].myPos.x == nodepos.x && graph[i].myPos.y== nodepos.y && (graph[i].visited != 1))
		{
			//std::cout << i;
			return i;
		}
	}
	return -1;
}

void djikstra(int start, node* graph, int nodeCount)
{
	if (graph[start].find == 1)
	{
		graph[start].visited == 1;
		std::cout << "Pouchaisi\n";
		return;
	}
	else
	{
		graph[start].visited = 1;
		int nextnode , dist_assign_node;
		float lowest_dist = 1e10;
		for (int i = 0; i < graph[start].connectedNodes.size(); i++)
		{
			

			double distance_x = (graph[start].connectedNodes[i].x - graph[start].myPos.x) * (graph[start].connectedNodes[i].x - graph[start].myPos.x);
			double distance_y = (graph[start].connectedNodes[i].y - graph[start].myPos.y) * (graph[start].connectedNodes[i].y - graph[start].myPos.y);
			float distance = sqrtf(distance_x + distance_y) + graph[start].distance;
			dist_assign_node = findNode(graph, nodeCount, graph[start].connectedNodes[i]);
			if (dist_assign_node < 0)
			{
				std::cout << "> " << dist_assign_node << " > " << distance << "\n";
				continue;;
			}
			if (graph[dist_assign_node].distance > distance)
			{
				std::cout << ">> " << distance << "\n";
				graph[dist_assign_node].distance = distance;
			}
			if (lowest_dist > graph[dist_assign_node].distance)
			{
				lowest_dist = graph[dist_assign_node].distance;
				nextnode = dist_assign_node;
				
			}
		}
		std::cout << "nextnode " << nextnode << '\n';
		path.push_back(nextnode);
		return djikstra(nextnode, graph, nodeCount);

	}

}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "lines");
	node graph[nodes];
	int x, y;
	std::vector<sf::Vector2f> pointGula;

	graph[0].shuru = 1;
	graph[0].distance = 0;
	graph[ends].find = 1;
	path.push_back(0);

	std::cout << "aage\n";
	//djikstra(0, graph, nodes);
	//findNode(graph, nodes, graph[0].connectedNodes[0]);

	

	
	
	for (int i = 0; i < nodes; )
	{
		x = rand()%1000;
		y = rand()%800;
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
			int conneced_to = rand() % nodes;
			std::cout << "connecting" << sizeof(node) << "\n";
			if (conneced_to != i) connect(graph + i, graph + conneced_to);
			//inserted[j] = true;
		}
	}

	djikstra(0, graph, nodes);
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
		//Sleep(5000);
		for (int i = 0; i < nodes;i++ )
		{
			graph[i].drawNode(window);
			
		}
		drawPath(graph, window);
		window.display();
		//Sleep(5000);
	}

}