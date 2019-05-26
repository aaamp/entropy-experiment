#ifndef lineChart_H_
#define lineChart_H_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class chart {
    private:
		mutable sf::RenderWindow window;
		mutable sf::View view;
		std::vector <double> lastPoint;
		float initZoom;

    public:
		void createWindow(unsigned x, unsigned y,std::string des);
		void chartUpdate(double,double);
		void zoom(float);
		void setCenter(float, float);
		void pollEvents() const;
		void chartReDraw(double) const;

};


#endif