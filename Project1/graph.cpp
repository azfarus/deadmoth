#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>
#include <dos.h>

class Button {
public:
	int buttpos_x, buttpos_y;
	int buttwidth, buttheight;
	sf::RectangleShape butt;
	sf::Texture n,f,p;

	Button(int x , int y , int w , int h , std::string &Nn , std::string &Ff , std::string &Pp )
	{
		butt.setSize(sf::Vector2f(w, h));
		
		butt.setOrigin(sf::Vector2f(w / 2.0, h / 2.0));
		butt.setPosition(sf::Vector2f(x, y));
		buttpos_x = x; buttpos_y = y;
		buttwidth = w; buttheight = h;
		n.loadFromFile(Nn);
		f.loadFromFile(Ff);
		p.loadFromFile(Pp);
		butt.setTexture(&n);
		
	}
	int onButton(sf:: RenderWindow &window)
	{
		sf::Vector2i mousepos(sf::Mouse::getPosition(window));
		int mouse_x = mousepos.x;
		int mouse_y = mousepos.y;

		if ((buttpos_x < mouse_x && buttpos_x + buttwidth > mouse_x) && (buttpos_y < mouse_y && buttpos_y + buttwidth > mouse_y))
		{
			butt.setTexture(&f);
			std::cout << "Button hovering\n";
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				return 2;
				butt.setTexture(&p);
			}
			return 1;
		}
		else
		{
			butt.setTexture(&n);
			return 0;
		}
		

	}

	void setTexture(std::string &filename)
	{
		sf::Texture jama;
		if (!jama.loadFromFile(filename))
		{
			std::cout << "Failed to load texture\n";
		}
		return;
		
	}
	void drawButton(sf:: RenderWindow &window)
	{
		window.draw(butt);
	}
};
using namespace std;


int main()
{
	int mouse_x, mouse_y;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "UI");
	sf::RectangleShape button1, button2;
	button1.setPosition(450, 375);
	button1.setSize(sf::Vector2f(100, 50));
	sf::Vector2f button1pos(button1.getPosition());
	button2.setPosition(450, 425+5);
	button2.setSize(sf::Vector2f(100, 50));
	sf::Vector2f button2pos(button2.getPosition());

	sf::Texture n, f, p;

	if (!(n.loadFromFile("normal.png") && f.loadFromFile("focused.png") && p.loadFromFile("pressed.png")))
	{
		cout << "Load hoynai";
		return 0;
	}


	while (window.isOpen())
	{
		sf::Event event;
		

		while (window.pollEvent(event))
		{
			sf::Vector2i mousepos(sf::Mouse::getPosition(window));
			mouse_x = mousepos.x;
			mouse_y = mousepos.y;
		  
			if ((button1pos.x < mouse_x && button1pos.x + 100 > mouse_x) && (button1pos.y < mouse_y && button1pos.y + 50 > mouse_y))
			{
				button1.setTexture(&f);
				std::cout << "Button 1 hovering" << endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					button1.setTexture(&p);
					
				}
			}
			else if ((button2pos.x < mouse_x && button2pos.x + 100 > mouse_x) && (button2pos.y < mouse_y && button2pos.y + 50 > mouse_y))
			{
				button2.setTexture(&f);
				std::cout << "Button 2 hovering" << endl;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					button2.setTexture(&p);
				}
			}
			else if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				button1.setTexture(&n);
				button2.setTexture(&n);
				std::cout << "Not hovering" << endl;

			}
			
		}
		window.clear(sf::Color::Black);
		window.draw(button1);
		window.draw(button2);
		window.display();
	}
}