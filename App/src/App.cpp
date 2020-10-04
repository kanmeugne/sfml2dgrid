
#include "App.h"
#include "AbstractViewer.h"
#include "IGrid.h"

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
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					int posx = event.mouseButton.x;
					int posy = event.mouseButton.y;
					printf("Sending request to add obstacle at position x=%d, y=%d ...\n", posx, posy);
					printf("success = %s!\n", addObstacle(posx, posy)?"OK":"NOK");
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int posx = event.mouseButton.x;
					int posy = event.mouseButton.y;
					printf("Sending request to remove obstacle at position x=%d, y=%d...\n", posx, posy);
					printf("sucess = %s!\n", removeObstacle(posx, posy)?"OK":"NOK");
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
			}
		}
	}
}

bool App::addObstacle(int posx, int posy)
{
	IGrid::CELL cell;
	int resx = getGrid()->iGetResolutionX();
	int resy = getGrid()->iGetResolutionY();
	bool thereisacell = getGrid()->iGetCellNumber(posy/resy, posx/resx, cell);
	if (thereisacell)
		printf("cell = %d!\n", cell);
	
	return thereisacell && (getGrid()->iAddObstacle(cell));
}

bool App::removeObstacle (int posx, int posy)
{
	IGrid::CELL cell;
	int resx = getGrid()->iGetResolutionX();
	int resy = getGrid()->iGetResolutionY();
	bool thereisacell = getGrid()->iGetCellNumber(posy/resy, posx/resx, cell);
	if (thereisacell)
		printf("cell = %d!\n", cell);
	return thereisacell && (getGrid()->iRemoveObstacle(cell));
}