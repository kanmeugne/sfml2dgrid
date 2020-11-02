
#ifndef APP_H
#define APP_H
namespace sf
{
	class RenderWindow;
};
class IGrid;
class AbstractViewer;
class App
{
private:
	// sfml render window
	sf::RenderWindow* _window = nullptr;
	// the 2D grid pointer
	IGrid* _grid = nullptr;
	// a pointer to the viewer
	// this could be a set of viewer actually
	// if we consider component behavior
	AbstractViewer* _viewer = nullptr;

public:
	// theorical width of the environment
	// will match the grid width in terms of number of cells. 
	static const int DEFAULT_WIDTH;
	// theorical height of the environment. 
	static const int DEFAULT_HEIGHT;
	// x-resolution of the grid i.e. the x-size of a cell
	static const int DEFAULT_RESX;
	// y-resolution of the grid i.e. the y-size of a cell
	static const int DEFAULT_RESY;
	// default constructor
	App() = default;
	virtual ~App();
	// attach window to the app
	void setWindow(sf::RenderWindow*);
	// attach a specific viewer
	void setViewer(AbstractViewer*);
	// attach a grid (should have been initialized)
	void setGrid(IGrid*);
	// return the attached grid
	IGrid* getGrid();
	// return the attached window
	sf::RenderWindow* getWindow();
	// run the application (the logic)
	void run();
	// show content (display routines)
	void display();
};
#endif // !APP_H