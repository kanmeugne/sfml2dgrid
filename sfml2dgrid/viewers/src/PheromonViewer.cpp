#include "PheromonViewer.h"
#include "App.h"
#include "IGrid.h"
#include "dynamics.h"
#include <SFML/Graphics.hpp>

using namespace viewers;

class PDrawer : public env::ICellFunctor
{
private:
	App* _app;
public:
	PDrawer() {};
	void setApp(App* app)
	{
		_app = app;
	}
	virtual ~PDrawer() {};
	virtual void operator()(const env::CELL& cell)
	{
        if ((false == cell._mask) && (cell._tau > 0.)) 
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

            // color according to pheromon value
            int level (cell._tau * 255 / dynamics::PMAX);
            square.setFillColor(sf::Color(255, 255-level, 255-level));

            // draw the cell
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