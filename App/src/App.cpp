
#include "App.h"
#include "AbstractViewer.h"
#include "IGrid.h"

#include <SFML/Graphics.hpp>

const unsigned int App::DEFAULT_WIDTH = 20;
const unsigned int App::DEFAULT_HEIGHT = 20;
const unsigned int App::DEFAULT_RESX = 40;
const unsigned int App::DEFAULT_RESY = 40;

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
					printf("right mouse clicked.\nx=%d, y=%d\n", posx, posy);
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int posx = event.mouseButton.x;
					int posy = event.mouseButton.y;
					printf("left mouse clicked.\nx=%d, y=%d\n", posx, posy);
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
			}
		}
	}
}