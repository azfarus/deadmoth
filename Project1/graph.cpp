#include <SFML/Graphics.hpp>
#include<Windows.h>

using namespace std;
int main()
{
    sf:: RenderWindow amarwindow;
    sf::RectangleShape amarline(sf::Vector2f(5.f, 5.f));
    float c = 50 ,c_x = 1 ;
    float del=0;
    

    
    amarwindow.create(sf::VideoMode(800, 600), "jingalala");
    amarwindow.setVerticalSyncEnabled(true);
   // amarline.setPosition(400, 300);
    //amarline.setOrigin(400, 300);
    amarline.setPosition(0, 300);
    

    while (amarwindow.isOpen())
    {
        sf::Event ghotonas;
        while (amarwindow.pollEvent(ghotonas))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                c += .1;
                //Sleep(50);
                break;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                c -= .1;
                //Sleep(50);
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                c_x += .1;
                //Sleep(50);
                break;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                c_x -= .1;
                //Sleep(50);
                break;
            }
            if (ghotonas.type == sf::Event::Closed)
            {
                amarwindow.close();

            }
        }
        
        amarwindow.clear(sf::Color::Black);
        //amarline.rotate(1);

        for (float i = 0; i < 40; i+=.003)
        {
            float x = i;
            amarline.setPosition(20*x*c_x,300- c*(x) * sinf(x - del));
            amarwindow.draw(amarline);
        }
        del += 0.2;
       // Sleep(1);
        if (del == 360) del == 0;
        //amarwindow.draw(amarline);
        
        amarwindow.display();
       // Sleep(3);


    }
    

    return 0;
}