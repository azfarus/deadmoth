#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>
#include <dos.h>
#define nodes 50
#define edges 7
#define ends 8
#define rad 10

std::vector<int> path;


class node
{
public:
	std::vector<int> connectedNodes;
	sf::Vector2f myPos;
	sf::CircleShape circle;
	
	float distance = 1e10;
	int find = 0, visited = 0 , shuru = 0 , previous , me ;
	

	void drawNode(sf::RenderWindow& window , node * graph)
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
			line[1].position = graph[connectedNodes[i]].myPos;
			window.draw(line);
		}
		window.draw(circle);

	}
	void nodePush(int n)
	{
		connectedNodes.push_back(n);
	}
	
};

void drawPath(node* graph, sf::RenderWindow &window , int endNode)
{
	sf::VertexArray line(sf::Lines, 2);;
	if (graph[endNode].me == graph[endNode].previous)
	{
		return;
	}
	else {
		line[0].position = graph[endNode].myPos; line[0].color = sf::Color::Green;
		line[1].position = graph[graph[endNode].previous].myPos; line[1].color = sf::Color::Green;
		window.draw(line);
		return drawPath(graph, window, graph[endNode].previous);
	}
}

void connect(int a, int   b , node * graph)
{
	//if (a->connections < edges && b->connections <= edges)
	{
		graph[a].nodePush(b);
		graph[b].nodePush(a);
		
		return;
	}
	return;
	
	//a->flag = b->flag = 0;
	

}

int chooseNode(node* graph, int nodeCount,  std::map<int,float> &nodepairs)
{
	float lowestval = 1e10;
	int position = -1;
	for (int i = 0; i < nodeCount; i++)
	{
		if ( ( nodepairs[i] < lowestval) && (graph[i].visited != 1))
		{
			lowestval = nodepairs[i];
			position = i;
		}
	}
	int c = 0;
	for (auto itr = nodepairs.begin()  ; itr != nodepairs.end(); ++itr , c++) {
		std::cout << '\t' << itr->first << '\t' << itr->second<<'\t' << graph[c].previous << '\t'<< position << '\n';
			
	}
	return position;
}

void djikstra(node* graph, int nodeCount, std::map<int,float> &nodepairs)
{
	while (true)
	{
		int start = chooseNode(graph, nodeCount, nodepairs);
		if (start < 0)
		{
			std::cout << "pouchaite parinai\n";
			return;
		}
		else if (graph[start].find == 1)
		{
			std::cout << "At node >>>> " << start << " prev " << graph[start].previous << "\n";
			std::cout << "pouchaisi\n";
			return;
		}
		else
		{
			graph[start].visited = 1;
			std::cout << "At node >>>> " << start << " prev " << graph[start].previous<< " connections ";
			
			for (unsigned int i = 0; i < graph[start].connectedNodes.size(); i++)
			{
				int connection = graph[start].connectedNodes[i];
				std::cout << connection <<' ';
				sf::Vector2f difference;
				difference.x = graph[start].myPos.x - graph[connection].myPos.x;
				difference.y = graph[start].myPos.y - graph[connection].myPos.y;
				float distance = sqrtf(difference.x * difference.x + difference.y * difference.y) + graph[start].distance;
				if (nodepairs[i] > distance && (graph[connection].visited != 1) )
				{
					nodepairs[connection] = distance;
					graph[connection].previous = start;
					graph[connection].distance = distance;
				}

			}
			std::cout << "\n";
		}
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "lines");
	node graph[nodes];
	int x, y;
	std::vector<sf::Vector2f> pointGula;
	std::map<int, float> nodepairs;


	

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
			graph[i].me = i;
			graph[i].previous = i;
			nodepairs[i] = 1e10;
			i++;

		}
		
	}

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < edges ; j++)
		{
			int conneced_to = rand() % nodes;
			std::cout << "connecting" << sizeof(node) << "\n";
			if (conneced_to != i) connect( i,  conneced_to , graph);
			//inserted[j] = true;
		}
	}

	graph[0].shuru = 1;
	graph[0].distance = 0;
	graph[0].previous = 0;
	nodepairs[0] = 0;
	graph[ends].find = 1;
	path.push_back(0);

	djikstra(graph,nodes,nodepairs);
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
			graph[i].drawNode(window , graph);
			
		}
		drawPath(graph, window, ends);
		window.display();
		//Sleep(5000);
	}

}