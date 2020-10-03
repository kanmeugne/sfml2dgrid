#include "GridViewer.h"
#include "App.h"
#include "IGrid.h"
#include <SFML/Graphics.hpp>

class LineDrawer : public geometry::ISegmentFunctor
{
private:
	App* _app;
	sf::Color _color;
public :
	LineDrawer() : _color(sf::Color(212, 212, 212)){};
	virtual ~LineDrawer() {};
	void setApp(App* app)
	{
		_app = app;
	}
	virtual void operator()(const geometry::Segment& segment)
	{
		const geometry::Point& init = segment.first;
		const geometry::Point& end = segment.second;
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(init.first, init.second), _color),
			sf::Vertex(sf::Vector2f(end.first, end.second), _color)
		};
		_app->getWindow()->draw(line, 2, sf::Lines);
	}
};

// segment functor for grid line drawing
LineDrawer ld;

void GridViewer::initialize()
{
	int sizex = _app->getGrid()->iGetSizeX();
	int sizey = _app->getGrid()->iGetSizeY();
	int resx = _app->getGrid()->iGetResolutionX();
	int resy = _app->getGrid()->iGetResolutionY();

	// build vertical lines
	for (int i = 0; i <= sizex; i++)
	{
		geometry::Point init (std::make_pair(resx*i, 0));
		geometry::Point end  (std::make_pair(resx*i, resy*sizey));
		_lines.push_back(std::make_pair(init, end));
	}

	// build horizontal lines
	for (int j = 0; j <= sizey; j++)
	{
		geometry::Point init (std::make_pair(0, resy*j));
		geometry::Point end  (std::make_pair(resx*sizex, resy*j));
		_lines.push_back(std::make_pair(init, end));
	}
}
void GridViewer::drawLines(geometry::ISegmentFunctor& lf) const
{
	for (auto it = _lines.begin(); it != _lines.end(); it++)
		lf(*it);
}

void GridViewer::iDraw()
{
	ld.setApp(_app);
	drawLines(ld);
}
