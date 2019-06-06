#include "lineChart.hpp"
#include <string>
#include <sstream>
void chart::createWindow(unsigned x, unsigned y, std::string des)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 3;

    window.create(sf::VideoMode(x, y), des, sf::Style::Default || sf::Style::Close, settings);
    view.reset(sf::FloatRect(-20, 0, x, y));
    window.setView(view);

    window.clear(sf::Color::Black);
    window.display();
}

void chart::chartReDraw()const
{
    window.clear(sf::Color::Black);
   
    view.setCenter(view.getCenter().x, -(minEntropy/scalY+(view.getSize().y /2)));
    window.setView(view); 
    sf::RectangleShape axis_OX(sf::Vector2f(100000, 2));
    sf::RectangleShape axis_OY(sf::Vector2f(100000, 2));
    axis_OY.setPosition(-1, 0);
    axis_OX.setPosition(0, 0);

    axis_OX.setFillColor(sf::Color(100, 250, 50));
    axis_OY.setFillColor(sf::Color(100, 250, 50));

    axis_OY.rotate(270);
    window.draw(axis_OX);
    window.draw(axis_OY);


    int x = view.getSize().x / 2 + 1;
    int y = view.getSize().y / 2 + 1;


    double ax  = ((view.getCenter().x - x) /(100*scal));
    double ay = ((-view.getCenter().y - y)/(100*scalY));

    if (ax  < 0)
        ax  = 0;
    if (ay < 0)
        ay = 0;


    if (lastPoint.size() > (view.getCenter().x + x)*scal && change)
        scal += 0.5;
       // scal= lastPoint.size()/ (view.getCenter().x + view.getSize().x / 2);
  
    if (maxEntropy > (-view.getCenter().y + view.getSize().y / 2)*scalY)
        scalY += 0.1;


    for (ax ; ax  < view.getCenter().x + x; ax  += 100/scal)
    {
        sf::RectangleShape line(sf::Vector2f(40, 2));
        line.setFillColor(sf::Color(100, 250, 50));
        line.setPosition(ax  + 1, 0);
        line.rotate(90);
        window.draw(line);
        if (ax  - 500 == 0)
        {
            // tutaj dodac jednostke 
        }

    }

    for (ay; ay < -view.getCenter().y + y; ay += 100/scalY)
    {
        sf::RectangleShape line(sf::Vector2f(40, 2));
        line.setFillColor(sf::Color(100, 250, 50));
        line.setPosition(-40, -ay);
        window.draw(line);
        if (ay - 500 == 0)
        {
            // tutaj dodac jednostke 
        }

    }

    ax = (view.getCenter().x - x) ;
    if (ax < 1)
        ax = 1;


    for (unsigned int i = ax; i < lastPoint.size(); i++) {

        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f((i - 1)/scal, -lastPoint[i - 1]/scalY)),
            sf::Vertex(sf::Vector2f(i/scal, -lastPoint[i]/scalY))
        };

        window.draw(line, 2, sf::Lines);
    }
    window.display();
}

void chart::chartUpdate(double time, double entropy)
{
    if (entropy < minEntropy || minEntropy < 0 )
        minEntropy = entropy;
    if (entropy > maxEntropy)
        maxEntropy = entropy;

    lastPoint.push_back(entropy);
    chartReDraw();
    return;

    /*
    if (lastPoint.size() == 1)
        return;

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(time - 1, -lastPoint[lastPoint.size() - 2])),
        sf::Vertex(sf::Vector2f(time, -entropy))
    };

    window.draw(line, 2, sf::Lines);
    window.display();  */

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
        }
        if (event.type == sf::Event::KeyPressed)
        {
            view = window.getView();
            switch (event.key.code)
            {
            case sf::Keyboard::F:
                view.setCenter(0, -lastPoint[0]);
                break;
            case sf::Keyboard::X:
                change ^=1 ;
                break;
            case sf::Keyboard::C:
                if(lastPoint.size()>0)
                view.setCenter((lastPoint.size()-1)/scal, -lastPoint[lastPoint.size()-1]);
                break;
            case sf::Keyboard::R:
                scalY = 1;
                scal=1;
                break;
            case sf::Keyboard::P:
                paused = !paused;
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
                view.move(view.getSize().x / (float)window.getSize().x * (mouseX - event.mouseMove.x), view.getSize().y / (float)window.getSize().y * (mouseY - event.mouseMove.y));
                window.setView(view);
            }
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
        }
    }
}

void chart::zoom(double f)
{
    initZoom = (f/200 < 8)? f/200:8;
    view.zoom(initZoom);
    view.setCenter(380*initZoom, -f+50);
    window.setView(view);
    
}

void chart::setCenter(float x, float y)
{
    view.setCenter(x*initZoom, y*initZoom);
    window.setView(view);
}
