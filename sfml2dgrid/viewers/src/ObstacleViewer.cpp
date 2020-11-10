#include "ObstacleViewer.h"
#include "App.h"
#include <SFML/Graphics.hpp>
using namespace viewers;

class ODrawer : public env::ICellFunctor
{
private:
	const sf::Color& _color;
	App* _app;
public:
	ODrawer() : _color(sf::Color::Blue){};
	void setApp(App* app)
	{
		_app = app;
	}
	virtual ~ODrawer() {};
	virtual void operator()(const env::CELL& cell)
	{
        if (cell._mask == true)

        {
            // get cell position
            int x, y;
            const int resx = _app->getGrid()->iGetResolutionX();
            const int resy = _app->getGrid()->iGetResolutionY();
            _app->getGrid()->iGetCellPosition(cell, x, y);
            // build the cell shape
            sf::ConvexShape square;
            square.setPointCount(4);
            square.setPoint(0, sf::Vector2f(x - resx / 2., y - resy / 2.));
            square.setPoint(1, sf::Vector2f(x + resx / 2., y - resy / 2.));
            square.setPoint(2, sf::Vector2f(x + resx / 2., y + resy / 2.));
            square.setPoint(3, sf::Vector2f(x - resx / 2., y + resy / 2.));
            square.setFillColor(_color);
            _app->getWindow()->draw(square);
        }
	}
};


// cell functor for grid obstacle drawing
ODrawer od;

void ObstacleViewer::drawObstacles(env::ICellFunctor& cf)
{
	_app->getGrid()->iApplyOnCells(cf);
}

void ObstacleViewer::iDraw()
{
	od.setApp(_app);
	drawObstacles(od);
}