#include "displ.hpp"

void displ::createWindow(std::string str, unsigned x, unsigned y)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	window.create(sf::VideoMode(x,y), str,sf::Style::Default, settings);	
	
	view.reset(sf::FloatRect( 0, 0, x, y));
	window.setView(view);
	
	window.clear(sf::Color::Black);
	window.display();
}

void displ::drawParticles(const std::vector<particle>& p)const
{
	window.clear(sf::Color::Black);

/*	sf::RectangleShape rectangle;
	
	rectangle.setSize(sf::Vector2f(box.getX(), box.getY()));
	rectangle.setOutlineColor(sf::Color(0x808080));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(1);
	
	window.draw(rectangle);*/

	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(0.01);
	circle.setOutlineColor(sf::Color::White);
	
	for(const auto& i : p)
	{
		circle.setPosition(i.getPosition().getX(), i.getPosition().getY());
		window.draw(circle);
	}
	
	window.display();
}

void displ::pollEvents() const
{
	sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void displ::zoom(float f)
{
	view.zoom(f);
	window.setView(view);
}
void displ::setCenter(float x, float y)
{
	view.setCenter(x,y);
	window.setView(view);
}
