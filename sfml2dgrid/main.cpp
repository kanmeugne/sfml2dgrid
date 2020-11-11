#include "App.h"
#include "GridViewer.h"
#include "ObstacleViewer.h"
#include "PheromonViewer.h"
#include "Grid.h"
#include <thread>
#include <SFML/Graphics.hpp>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main()
{
#ifdef __linux__
	XInitThreads();
#endif

	// -- sfml windows
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;
	sf::RenderWindow window(
		sf::VideoMode(
			(App::DEFAULT_WIDTH * App::DEFAULT_RESX),
			(App::DEFAULT_HEIGHT * App::DEFAULT_RESY)),
		"SFML 2D Grid",
		sf::Style::Titlebar | sf::Style::Close,
		settings);
	window.clear(sf::Color::White);
	window.setFramerateLimit(120);
	window.setActive(false);

	// -- application
	App app;
	app.setWindow(&window);

	//-- grid 2D
	env::Grid g;
	g.setSizeX(App::DEFAULT_WIDTH);
	g.setSizeY(App::DEFAULT_HEIGHT);
	g.setResolutionX(App::DEFAULT_RESX);
	g.setResolutionY(App::DEFAULT_RESY);
	g.iInitialize();
	app.setGrid(&g);

	//-- viewer
	viewers::GridViewer gviewer;
	gviewer.iActivate();

	// grid obstacles
	viewers::ObstacleViewer oviewer;
	oviewer.iActivate();

	// pheromons 
	viewers::PheromonViewer pviewer;
    pviewer.iActivate();

	// aggregator
	viewers::ViewerMgr mgr;
	mgr.iAddViewer(&oviewer);
	mgr.iAddViewer(&pviewer);
	mgr.iAddViewer(&gviewer);
	app.setViewer(&mgr);
	mgr.iActivate();

	// initialize gviewer (only after having attached it to the App object)
	gviewer.initialize();

	//-- launch application
	std::thread rendering_thread(&App::display, &app);
	std::thread evaporation_thread(&App::evaporate, &app);
	app.run();
	rendering_thread.join();
	evaporation_thread.join();

	return 0;
}