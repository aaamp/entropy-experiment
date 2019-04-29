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
	static bool mouseButtonDown = false;
	static int mouseX = 0, mouseY = 0;
	static sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        if (event.type == sf::Event::Resized)
		{
			float factor = (view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y)/2.f;
			view = window.getView();
			view.setSize((float)event.size.width, (float)event.size.height);
			view.zoom(factor);
			window.setView(view);
		}
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            view = window.getView();
            if (event.mouseWheelScroll.delta < 0.f && view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y < 0.001f)
                break;
            if (event.mouseWheelScroll.delta > 0.f && view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y > 1.f)
                break;
            view.zoom((event.mouseWheelScroll.delta > 0.f) * 1.2f + (event.mouseWheelScroll.delta < 0) * 0.8f);
            window.setView(view);
        }
        if (event.type == sf::Event::KeyPressed)
        {
            view = window.getView();
			constexpr float step = 20.f;
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                    view.move(0.f, -view.getSize().y/(float)window.getSize().y * step);
                    break;
				case sf::Keyboard::S:
                    view.move(0.f, view.getSize().y/(float)window.getSize().y * step);
                    break;
                case sf::Keyboard::A:
                    view.move(-view.getSize().x/(float)window.getSize().x * step, 0.f);
                    break;
                case sf::Keyboard::D:
                    view.move(view.getSize().x/(float)window.getSize().x * step, 0.f);
                    break;
                default:
                    break;
            }
			window.setView(view);
        }
		if (event.type == sf::Event::MouseButtonPressed)
		{
			mouseButtonDown = true;
			mouseX = 0;
			mouseY = 0;
		}
		if (event.type == sf::Event::MouseButtonReleased)
			mouseButtonDown = false;
		if (event.type == sf::Event::MouseMoved && mouseButtonDown)
		{
			if (mouseX || mouseY)
			{
				view = window.getView();
				view.move(view.getSize().x/(float)window.getSize().x * (mouseX - event.mouseMove.x), view.getSize().y/(float)window.getSize().y * (mouseY - event.mouseMove.y));
				window.setView(view);
			}
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}
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
