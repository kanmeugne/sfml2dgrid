#include "GridViewer.h"
#include "App.h"
#include "IGrid.h"
#include <SFML/Graphics.hpp>

class LineDrawer : public IGrid::ISegmentFunctor
{
private:
	App* _app;
	sf::Color _color;
public :
	LineDrawer(App* app) : _app(app), _color(sf::Color(212, 212, 212)){};
	virtual ~LineDrawer() {};
	virtual void operator()(const IGrid::Segment& segment)
	{
		const IGrid::Point& init = segment.first;
		const IGrid::Point& end = segment.second;
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(init.first, init.second), _color),
			sf::Vertex(sf::Vector2f(end.first, end.second), _color)
		};
		_app->getWindow()->draw(line, 2, sf::Lines);
	}
};

void GridViewer::iDraw()
{
	LineDrawer ld (_app);
	_app->getGrid()->iApplyOnSegments(ld);
}
