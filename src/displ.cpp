#include "displ.hpp"
void displ::createWindow(std::string str, unsigned x, unsigned y, unsigned antialiasing)
{
	sf::ContextSettings settings;
	//Z antyaliasingiem 0 działa bardzo szybko ale brzydko
	settings.antialiasingLevel = antialiasing;
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

	float doubledZoom = view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y;

	if (radius/doubledZoom*1.5f > 1.f)
	{
		//Kółka są widoczne

		sf::CircleShape circle(radius);

		//Dokładność kształtów rośnie z powiększaniem
		float vertices = 0.4f/doubledZoom + 3.f;
		vertices = vertices < 20.f ? vertices : 20.f;
		circle.setPointCount((int)vertices);

		circle.setRadius(radius);
		int temperature;
		sf::FloatRect viewBoundingBox(view.getCenter() - view.getSize()/2.f, view.getSize());
		for(const auto& i : p)
		{
			circle.setPosition(i.getPosition().getX() - radius, i.getPosition().getY() - radius);

			//Poza ekranem nie rysujemy
			if (!viewBoundingBox.intersects(circle.getGlobalBounds()))
				continue;

			// Uwaga! 0.25 było wyznaczone eksperymentalnie!
			temperature = i.getVelocity().getSquaredLength() * 1020; // * 255.f / 0.25f;
			temperature = temperature < 255 ? temperature : 255;
			circle.setFillColor(sf::Color(temperature, 0, 255 - temperature));
			window.draw(circle);
		}
	}
	else
	{
		//Kółka sprowadzają się do punktów
		sf::Vertex point;
		int temperature;
		for(const auto& i : p)
		{
			// Uwaga! 0.25 było wyznaczone eksperymentalnie!
			temperature = i.getVelocity().getSquaredLength() * 255.f / 0.25f;
			temperature = temperature < 255 ? temperature : 255;
			point.position = {i.getPosition().getX() - radius, i.getPosition().getY() - radius};
			point.color = sf::Color(temperature, 0, 255 - temperature);
			window.draw(&point, 1, sf::Points);
		}
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
            if (event.mouseWheelScroll.delta < 0.f && view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y < 0.01f)
                break;
            if (event.mouseWheelScroll.delta > 0.f && view.getSize().x/(float)window.getSize().x + view.getSize().y/(float)window.getSize().y > 2.f)
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
