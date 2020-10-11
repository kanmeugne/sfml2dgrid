#include "PheromonViewer.h"
#include "App.h"
#include "IGrid.h"
#include <SFML/Graphics.hpp>

using namespace viewers;

class PDrawer : public env::ICellFunctor
{
private:
	const sf::Color& _color;
	App* _app;
public:
	PDrawer() : _color(sf::Color::Blue){};
	void setApp(App* app)
	{
		_app = app;
	}
	virtual ~PDrawer() {};
	virtual void operator()(const env::CELL& cell)
	{
        if (true == cell._mask)

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


// cell functor for pheromon drawing
PDrawer phdr;

void PheromonViewer::drawPheromon(env::ICellFunctor& cf)
{
	_app->getGrid()->iApplyOnCells(cf);
}

void PheromonViewer::iDraw()
{
	phdr.setApp(_app);
	drawPheromon(phdr);
}