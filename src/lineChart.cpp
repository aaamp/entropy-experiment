#include "lineChart.hpp"
#include <string>
#include <sstream>
void chart::createWindow( unsigned x, unsigned y,std::string des)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 3;

    window.create(sf::VideoMode(x, y),des, sf::Style::Default ||sf::Style::Close, settings);
    view.reset(sf::FloatRect(0, 0, x, y));
    window.setView(view);

    window.clear(sf::Color::Black);
    window.display();

    zoom(7);
    setCenter(380, -190);
}  

void chart::chartReDraw(double entropy)const
{
    window.clear(sf::Color::Black);


    sf::RectangleShape axis_OX(sf::Vector2f(100000, 2));
    sf::RectangleShape axis_OY(sf::Vector2f(100000, 2));
    axis_OY.setPosition(-1, 0);
    axis_OX.setPosition(0, 0);

    axis_OY.rotate(270);
    window.draw(axis_OX);
    window.draw(axis_OY);
	
   
    int x = view.getSize().x / 2 + 1;
    int ax = (view.getCenter().x - x)/100;
    if (ax < 0)
        ax = 0;
    for (ax; ax < view.getCenter().x + x; ax += 100)
    {
        sf::RectangleShape line(sf::Vector2f(40, 2));
        line.setPosition(ax+1, 0);
        line.rotate(90);
        window.draw(line);
        if (ax % 500 == 0)
        {
            // tutaj dodac jednostke 
        }

    }

    int y = view.getSize().y / 2 + 1;

    ax = (-view.getCenter().y - y) / 100;
    if (ax < 0)
        ax = 0;
    for (ax; ax < -view.getCenter().y + y; ax += 100)
    {
        sf::RectangleShape line(sf::Vector2f(40, 2));
        line.setPosition(-40, -ax);
        window.draw(line);
        if (ax % 500 == 0)
        {
          // tutaj dodac jednostke 
        }

    }


    for (unsigned int i = 1; i < lastPoint.size(); i++) {

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i - 1, -lastPoint[i-1])),
            sf::Vertex(sf::Vector2f(i, -lastPoint[i]))
        };

        window.draw(line, 2, sf::Lines);
    }
    window.display();
}

void chart::chartUpdate(double time, double entropy)
{
    lastPoint.push_back(entropy);

    if (lastPoint.size() == 1)
        return;

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(time - 1, -lastPoint[lastPoint.size() - 2])),
        sf::Vertex(sf::Vector2f(time, -entropy))
    };

    window.draw(line, 2, sf::Lines);
    window.display();

}  

void chart::pollEvents() const
{
    static bool mouseButtonDown = false;
    static bool paused = false;
    static int mouseX = 0, mouseY = 0;
    static sf::Event event;
    while (window.pollEvent(event) || paused)
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            [&, this]() {
                view = window.getView();
                if (event.mouseWheelScroll.delta < 0.f && view.getSize().x / (float)window.getSize().x + view.getSize().y / (float)window.getSize().y < 0.01f)
                    return;
                if (event.mouseWheelScroll.delta > 0.f && view.getSize().x / (float)window.getSize().x + view.getSize().y / (float)window.getSize().y > 14.f)
                    return;
                view.zoom((event.mouseWheelScroll.delta > 0.f) * 1.2f + (event.mouseWheelScroll.delta < 0) * 0.8f);
                window.setView(view);

            }();	

            chartReDraw(view.getCenter().y);
        }
        if (event.type == sf::Event::KeyPressed)
        {
            view = window.getView();
            switch (event.key.code)
            {
            case sf::Keyboard::F:
                view.setCenter(380*initZoom,-lastPoint[0]);
                break;
            case sf::Keyboard::P:
                paused = !paused;
            default:
                break;
        }
            window.setView(view);
            chartReDraw(-view.getCenter().y);
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
                view.move(view.getSize().x / (float)window.getSize().x * (mouseX - event.mouseMove.x), view.getSize().y / (float)window.getSize().y * (mouseY - event.mouseMove.y));
                window.setView(view);
            }
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            chartReDraw(-view.getCenter().y);
        }
    }
}

void chart::zoom(float f)
{
    initZoom = f;
    view.zoom(f);
    window.setView(view);
}

void chart::setCenter(float x, float y)
{
    view.setCenter(x*initZoom, y*initZoom);
    window.setView(view);
}