#ifndef _DISPL_HPP_
#define _DISPL_HPP_

#include "particle.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class displ
{
private:
	mutable sf::RenderWindow window;
	mutable sf::View view;
	 
	float radius;
	 
	vec2f box;
	
public:
	explicit displ(float r, vec2f b) : radius(r), box(b) {}; //particle rad., bounding box
	void createWindow(std::string, unsigned x = 800, unsigned y = 800, unsigned antialiasing = 2);
	
	void zoom(float f);
	void setCenter(float x, float y);
	
	void drawParticles(const std::vector<particle>& p)const;
	void pollEvents() const;
};

#endif