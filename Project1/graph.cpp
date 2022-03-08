#include <SFML/Graphics.hpp>
#include<Windows.h>
#include<iostream>
#include <dos.h>

class Button {
public:
	int buttpos_x, buttpos_y;
	int buttwidth, buttheight;
	sf::RectangleShape butt;
	sf::Texture n,f,p,jama;

	void create(int x , int y , int w , int h , std::string Nn , std::string Ff , std::string Pp )
	{
		butt.setSize(sf::Vector2f(w, h));
		
		//butt.setOrigin(sf::Vector2f(w / 2.0, h / 2.0));
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
				
				butt.setTexture(&p);
				return 2;
			}
			return 1;
		}
		else
		{
			butt.setTexture(&n);
			return 0;
		}
		

	}

	void setTexture(std::string filename)
	{
		
		if (!jama.loadFromFile(filename))
		{
			std::cout << "Failed to load texture\n";
		}
		butt.setTexture(&jama);
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
	Button but;
	but.create(400, 300, 100, 50, "normal.png", "focused.png", "pressed.png");
	sf::RenderWindow win(sf::VideoMode(800, 600), "jingalala");
	
	while (win.isOpen())
	{
		win.clear(sf::Color::Black);
		but.onButton(win);
		but.drawButton(win);
		win.display();



	}


	
}