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
		sf::Font font;
		mutable sf::Text text;
        mutable double scal=1;
        mutable double scalY = 1;
        mutable double minEntropy=-1;
        mutable double maxEntropy=0;
        mutable bool change = 1;

    public:
		void createWindow(unsigned x, unsigned y,std::string des);
		void chartUpdate(double,double);
		void zoom(double);
		void setCenter(float, float);
		void pollEvents() const;
		void chartReDraw() const;

};


#endif
