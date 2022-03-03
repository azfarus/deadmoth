#include <SFML/Graphics.hpp>
#include<Windows.h>

using namespace std;
int main()
{
    sf:: RenderWindow amarwindow;
    sf::RectangleShape amarline(sf::Vector2f(5.f, 5.f));
    float del=0;
    //amarline.setPosition(400, 300);
    //amarline.setOrigin(150.0, 2.5);

    
    amarwindow.create(sf::VideoMode(800, 600), "jingalala");
    

    while (amarwindow.isOpen())
    {
        sf::Event ghotonas;
        while (amarwindow.pollEvent(ghotonas))
        {
            if (ghotonas.type == sf::Event::Closed)
            {
                amarwindow.close();

            }
        }
        
        amarwindow.clear(sf::Color::Black);
        //amarline.rotate(1);

        for (float i = 0; i < 40; i+=.01)
        {
            amarline.setPosition(20*i, 300.0-150*cosf(i+ del));
            amarwindow.draw(amarline);
        }
        del += 0.5;
       // Sleep(1);
        if (del == 360) del == 0;
        amarwindow.draw(amarline);
        
        amarwindow.display();
        Sleep(3);


    }
    

    return 0;
}