
#include "App.h"
#include "AbstractViewer.h"
#include "IGrid.h"
#include "dynamics.h"
#include <SFML/Graphics.hpp>

const int App::DEFAULT_WIDTH = 20;
const int App::DEFAULT_HEIGHT = 20;
const int App::DEFAULT_RESX = 40;
const int App::DEFAULT_RESY = 40;

void App::setWindow(sf::RenderWindow *w)
{
	_window = w;
}

void App::setGrid(IGrid *g)
{
	_grid = g;
}

IGrid* App::getGrid()
{
	return _grid;
}

sf::RenderWindow* App::getWindow()
{
	return _window;
}

App::~App()
{
	_window = nullptr;
}

void App::setViewer(AbstractViewer *v)
{
	_viewer = v;
	_viewer->iSetApp(this);
}

void App::display()
{
	if (_window != nullptr)
	{
		_window->setActive(true);
		while (_window->isOpen())
		{
    		_window->clear(sf::Color::White);
			_viewer->iDisplay();
			_window->display();
		}
	}
}

void App::run()
{
	_window->setActive(false);
	while (_window->isOpen())
	{
		sf::Event event;
		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window->close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				int posx = event.mouseButton.x;
				int posy = event.mouseButton.y;
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					printf("Adding obstacle at position [x=%d, y=%d] ", posx, posy);
					printf(" ... %s!\n", addObstacle(posx, posy)?"SUCCESSFUL":"FAILED");
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					printf("Removing obstacle at position [x=%d, y=%d] ", posx, posy);
					printf(" ... %s!\n", removeObstacle(posx, posy)?"SUCCESSFUL":"FAILED");
				}
				if (event.mouseButton.button == sf::Mouse::Middle)
				{
					printf("Adding a deposit of pheromon at position [x=%d, y=%d] ", posx, posy);
					printf(" ... %s!\n", addPheromon(posx, posy)?"SUCCESSFUL":"FAILED");
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
			}
		}
	}
}

void App::evaporate()
{
	// clock for pheromon evaporation
    sf::Clock clock;
    sf::Int32 time = 0;

    // deactivate the opengl context
    _window->setActive(false);

	while (_window->isOpen())
    {
		time = clock.getElapsedTime().asMilliseconds();
		if (time >= 100)
        {
            _grid->iUpdatePheromon(time);
            sf::Int32 lag = clock.restart().asMilliseconds();
            if (lag > 0) _grid->iUpdatePheromon(lag);
        }
	}
}

bool App::addObstacle(int posx, int posy)
{
	IGrid::CELL cell;
	int resx = getGrid()->iGetResolutionX();
	int resy = getGrid()->iGetResolutionY();
	bool thereisacell = getGrid()->iGetCellNumberFromPosition(posy/resy, posx/resx, cell);
	if (thereisacell)
		printf("(CellNo: %d)", cell);
	
	return thereisacell && (getGrid()->iAddObstacle(cell));
}

bool App::removeObstacle (int posx, int posy)
{
	IGrid::CELL cell;
	int resx = getGrid()->iGetResolutionX();
	int resy = getGrid()->iGetResolutionY();
	bool thereisacell = getGrid()->iGetCellNumberFromPosition(posy/resy, posx/resx, cell);
	if (thereisacell)
		printf("(CellNo: %d)", cell);
	return thereisacell && (getGrid()->iRemoveObstacle(cell));
}

bool App::addPheromon(int posx, int posy)
{
	IGrid::CELL cell;
	int resx = getGrid()->iGetResolutionX();
	int resy = getGrid()->iGetResolutionY();
	bool thereisacell = getGrid()->iGetCellNumberFromPosition(posy/resy, posx/resx, cell);
	if (thereisacell)
		printf("(CellNo: %d)", cell);
	return thereisacell && (getGrid()->iAddPheromon(cell, dynamics::DELTAMAX));
}