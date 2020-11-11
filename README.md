I started studying simulation of moving agents ten years ago and I have come to realize that regular 2D Grids are extraordinary abstractions for the navigable space. In fact, regular 2D grids are very easy to encode and they offer an elegant framework for path planning and collision avoidance algorithms deployment.

In this post, I am sharing an *object oriented architecture* --- with its C++ implementation ---  that I am actually using in my personal projects when I need a 2D Grid. I hope that it could be an affordable starting point for anyone who is interested in the subject.

## Architecture

To be very concrete, I am going to assume that I am building a simulation app --- of moving agents --- that uses a 2D grid as the navigable space model. The root *object oriented architecture* that I am using to tackle the implementation is outlined in **Fig. 1.** Basically, there is an application object called *App* and three other packages: 
- *env* : for the navigable space representation and manipulation objects
- *viewers* : for visualisation purposes
- *geometry* : for geometrical abstraction

I am giving more details about *App*, *env*, *viewers* and *geometry* below.

![Fig. 1.](http://www.plantuml.com/plantuml/svg/JOzHJe0m38RVUugUO8YFP2wG63t7s0eiRenq6qQ9TvSfKVhsV_tx9UrJrfnByB2GjiGTokG-gMiV5CefhXbDz96VHbz8lRXPO2jaKnSA1pQBosHoOS8uOIoCZy_uoixYi6qecwfI0CRhb7xGyGMmQVEcPq9QTuG3y1ouuTtHEt62umvdYe4oV_pIQX92_LMlN8rmiPh_hs1nbZ1G66kzfzMU7ty3)

```terminal
sfml2dgrid
.
├── CMakeLists.txt
├── deps
│   └── sfml
│       └── CMakeLists.txt.in
└── sfml2dgrid
    ├── CMakeLists.txt
    ├── main.cpp
    ├── app
    │   ├── include
    │   │   └── App.h
    │   └── src
    │       └── App.cpp
    ├── env
    │   ├── include
    │   │   ├── Grid.h
    │   │   └── IGrid.h
    │   └── src
    │       └── Grid.cpp
    ├── geometry
    │   └── include
    │       └── geometry.h
    └── viewers
        ├── include
        │   ├── AbstractViewer.h
        │   └── GridViewer.h
        └── src
            ├── AbstractViewer.cpp
            └── GridViewer.cpp
```
> **Note**: the file tree of the project with the source (.cpp) and header (.h) files that I am going to discuss about in the rest of the post.

### App : the Application Object

The *App* object is the definition of our application --- see **Fig.2.** It holds a viewer (*viewers::AbstractViewer*) --- that contains display instructions --- and a reference to a 2D Grid (*env::IGrid*) --- that will be used to manipulate the 2D grid. Note that the *App* object has an *SFML window* as a private attribute --- this is where the rendering will occurs.

![Fig. 2.](http://www.plantuml.com/plantuml/svg/NL5DIyGm4BtdLxpZBhAxkiSImow8ujM37YLDfZQI9YL9MrJyxwQf1TtJCE_nFeOvnIH36ZhBMfAQGWKUpITLDzU2DzubA6zzkAtjGEBUlErntFF3J0YS-nw-VYULO29aIbArf94y94P34mLipdLCGQhqNFOjfDDGMHsypH8Sx_0GZCRcSHvRVfYp1MFAoXXBm1S3W1rYKrLFv7B35-Eqd_0wbLdeAum-kuJ1RRP_0MrYR-L71hyPaxzLi9Z_RmREbyfHv7ZZ4eL6AaBfbKbouqoKatSxiU3hUk75M6lqAksegxDhWIupLuwTyc7v1Jy0)

*App* also defines two important methods :
- *App::run* : responsible of the simulation logic
- *App::display* : responsible of the display (what we see on the screen).

**App.h**

```c++

#ifndef APP_H
#define APP_H

namespace sf
{
	class RenderWindow;
};

namespace env
{
	class IGrid;
};

namespace viewers
{
	class AbstractViewer;
};

class App
{
private:
	// sfml render window
	sf::RenderWindow *_window = nullptr;
	// the 2D grid pointer
	env::IGrid *_grid = nullptr;
	// a pointer to the viewer
	// this could be a set of viewer actually
	// if we consider component behavior
	viewers::AbstractViewer *_viewer = nullptr;

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
	// attach window to the app
	void setWindow(sf::RenderWindow *);
	// attach a specific viewer
	void setViewer(viewers::AbstractViewer *);
	// attach a grid (should have been initialized)
	void setGrid(env::IGrid *);
	// return the attached grid
	env::IGrid *getGrid();
	// return the attached window
	sf::RenderWindow *getWindow();
	// run the application (the logic)
	void run();
	// show content (display routines)
	void display();

	App() = default;
	virtual ~App();
};
#endif // !APP_H
```
> **Note**: In the *App.h* file, I have defined static attributes --- *DEFAULT_WIDTH*, *DEFAULT_HEIGHT*, *DEFAULT_RESX*, *DEFAULT_RESY* --- to set the default dimensions of a grid in the application.

### *AbstractViewer*, GridViewer and the *geometry* Package

*AbstractViewer* is meant to be derivated according to what we want to show on the application window --- for instance, *GridViewer* is a specific implementation of *AbstractViewer* that uses the *geometry* package to draw the grid lines.


#### AbstractViewer : The Generic Definition of a Viewer

*AbstractViewer* is always attached to an *App* object --- see **Fig.3** --- and defines a protected abstract method called *AbstractViewer::iDraw* --- implemented in its inherited classes. *AbstractViewer::iDraw* is called by the public method *AbstractViewer::iDisplay* when necessary --- that will be in the *App::display* function.

![Fig.3.](http://www.plantuml.com/plantuml/svg/RL5DYzim4BthLpnOACcMU5jwIxrc0sLBeBU5NeiYZUEXicGaETlDalzUEPPfR7hGvRsPzw5v2b7wsBT6D2GrUL46FjFsywSAPUriX7B6-SU3wQbwvcE1BqNvC10LldlMFvbUoOC39497YcjME8tWYWigmBOXpp6Wzgx5xX2YbogEU-l4GZNI7mckXlRobUqHiI4OjXImQfpdStAJ1j9gdCX7LjAiq_Xrx9Wo5DX7z872Y91hAVetT5BzbacuV1WQLOBIVkweZ0m1kwx3km20ZpWvrl2zNQrl0SsXC_8jWHSXStBavLaHbELOEbJLN9DtAl99HfehypUI_oVsuRgnX5yefhohzEuNGbF6hrVu3kzJqiiqaRurgztXu9p1hwituH6rD85Ikx5KlkYo4Fs9PFMoS-wvoL-LJ7uCDrjD1zXkzozqRCd6vzwgwFo7UN3BaQNXCqtPvd4lWcqaNqj5M0YbS9D9LUNeUM9EYULYKLJJf1ZExpQRHIjnymTfUc4ze-ytctzgec5D63HRQW_ammWirkTavkRWZK7DP7GGuecixblp5m00)

**AbstractViewer.h**
```c++
#ifndef ABSTRACTVIEWER_H
#define ABSTRACTVIEWER_H

class App;

namespace viewers
{
	// AbstractViewer
	class AbstractViewer
	{
	public:
		// activate the viewer. If activated, it provides the desired view
		virtual void iActivate();
		// deactivate the viewer. Do not display anaything if deactivated
		virtual void iDeactivate();
		// return True if the viewer is active
		virtual bool iIsActive() const;
		// display function
		virtual void iDisplay();
		// attach the application object
		virtual void iSetApp(App *);

		virtual ~AbstractViewer() = default;
		AbstractViewer() = default;

	protected:
		// specific draw method (to be concretized in child classes)
		virtual void iDraw() = 0;
		// if active the viewer is automatically activated
		bool _active = false;
		// reference to the attached app
		App *_app;
	};
} // namespace viewers

#endif // !ABSTRACTVIEWER_H
```
> **Note**: *AbstractViewer* is always attached to an *App* object and defines a protected abstract method called *AbstractViewer::iDraw*.

#### GridViewer : the Grid Lines Viewer

For the exercice, we will define *GridViewer* as our only viewer, reponsible of displaying the lines of the 2D Grid. The private methods defined in *GridViewer* are : 
- *initialize* : to build the set of segments to be displayed
- *drawLine* : to call the graphic engine and draw every segment built during the initialization step *initialize*
- *iDraw* : to call the above methods in the right order.

**GridViewer.h**

```c++
#ifndef GRIDVIEWER_H
#define GRIDVIEWER_H

#include "AbstractViewer.h"
#include "geometry.h"
#include <vector>

namespace viewers
{
	class GridViewer : public AbstractViewer
	{
	public:
		GridViewer() = default;
		virtual void initialize();
		virtual ~GridViewer() = default;

	protected:
		virtual void iDraw();

	private:
		void drawLines(geometry::ISegmentFunctor &) const;
		std::vector<geometry::Segment> _lines;
	};
} // namespace viewers
#endif // !GRIDVIEWER_H
```
> **Note**: We define *GridViewer* as our only viewer, reponsible of displaying the lines of the 2D Grid

#### The *geometry* Package

Here is the full description of our modest *geometry* package.

It contains the following objects :
- *Point* : a 2D point definition, actually a pair of integers
- *Segment* : the definition of a segment --- a pair of *Point*
- *ISegmentFunctor* : an interface, meant to be realised by functors that applies on *Segment*

**geometry.h**

```c++
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>

namespace geometry
{
	// definition of a point (typedef is sufficient)
	typedef std::pair<int, int> Point;
	// definition of a segment (typedef is sufficient)
	typedef std::pair<Point, Point> Segment;

	// Functor definition to apply on segment
	// We can inherit from this to function
	// to apply display instruction on segments
	class ISegmentFunctor {
	public:
		// operator function to apply on each segment 
		// (should concretized according to the need)
		virtual void operator()(
			const Segment& // cell_id
		) = 0;
	};
}
#endif // !GEOMETRY_H
```
> **Note**: Our very modest geometry package contains *geometry::Point*, *geometry::Segment* and *geometry::ISegmentFunctor*.

### The 2D Grid

The most important features of our 2D grid are defined in the *IGrid* interface  --- see **Fig.4**.  *IGrid* is realized by the *Grid* object which is composed of grid cells --- note that the *CELL* object is defined in *IGrid.h*.

![Fig. 4.](http://www.plantuml.com/plantuml/svg/ZPBHIyCm4CRV-rVSarJTEXMVHYsJgMCmLFH1VSoQwtgG9gL91phytyqjwt2ie7qeoVTzlzo5oyGwqRYsKb69Gc8pXjJI5uulBp982wCTv4QPvcQfMimUQ9N0TPAEsCXWrf241eNoW0LN8f1ss1GYHp052BYwWvNF341YGHgbzs7EL0BfYCjaKQw4jN1Rrx29m7_di3PyQglZqz-295ihyUd5xnqplLyi84rHhxEiWxa18Eap-qv2mQFWqXW5DDVaYFl7hbeuOORkrOlllUh7aVg2rgZMaT61wFUEkSUsMcBpL4nHAHlShZMsMNusbXYE-Re39a_2lpUzCBduVpgKZxtF8VzZgYTgj1EaIQyOYdEZhGlv_JAWX-JSlf4hIVy9TGCzc1DLjS8AjREx0MvyBgoI9DkIqNPtDXpkjlo8ZDy582f98h1M8L_J1Y4SKH0g6PJmZYfqfUaKZkof2MhPLke7)

**IGrid.h**

```c++
#ifndef IGRID_H
#define IGRID_H

namespace env
{
	struct CELL
	{
		int _id; // id of the cell
		CELL() = default;
		CELL(const CELL &) = default;
	};

	class IGrid
	{
	public:
		virtual ~IGrid() = default;
		// returns the width
		virtual int iGetSizeX() const = 0;
		// return the height
		virtual int iGetSizeY() const = 0;
		// return the number of cells in the grid
		virtual int iGetNumberOfCells() const = 0;
		// get the width of a cell (in terms of pixels)
		virtual int iGetResolutionX() const = 0;
		// get the height of a cell (in terms of pixels)
		virtual int iGetResolutionY() const = 0;
		//-- Test
		// relative position of a cell according to its id
		virtual bool iGetCellPosition(
			const CELL &, // cell
			int &,        // posx
			int &,        // posy
		) const = 0;
		// coordinates of a cell accoring to its id
		virtual bool iGetCellCoordinates(
			const CELL &, // cell
			int &,        // row_number
			int &         // column_number
		) const = 0;
		// cell rank of the the cell according
		// to its relative position in the grid
		virtual bool iGetCellNumber(
			int, // row_number
			int, // column_number
			CELL &) const = 0;
		// the containing cell given the coordinates in the 2D space
		virtual bool iGetContainingCell(
			int,   // posx
			int,   // posy
			CELL & // cell
		) const = 0;
		// check if a given point is within a given cell
		virtual bool iIsWithinCell(
			int,         // posx
			int,         // posy
			const CELL & // cell
		) const = 0;
		// initialize the vector of cells, obstacle mask, etc.
		virtual void iInitialize() = 0;
	};
} // namespace env
#endif // !IGRID_H
```
> **Note**: The features of the 2D grid are defined in *IGrid.h*. *IGrid.h* also contains the definition of the *CELL* object.

**Grid.h**

```c++
#ifndef GRID_H
#define GRID_H

#include "IGrid.h"
#include <vector>

namespace env
{
	const int DEFAULT_GRID_SIZEX = 10;
	const int DEFAULT_GRID_SIZEY = 10;
	const int DEFAULT_RESOLUTIONX = 1;
	const int DEFAULT_RESOLUTIONY = 1;

	class Grid : public IGrid
	{
	public:
		virtual ~Grid() = default;
		Grid() = default;
		//-- Getters
		virtual int iGetSizeX() const;
		virtual int iGetSizeY() const;
		virtual int iGetNumberOfCells() const;
		virtual int iGetResolutionX() const;
		virtual int iGetResolutionY() const;
		// Test
		virtual bool iGetCellPosition(const CELL &, int &, int &) const;
		virtual bool iGetCellCoordinates(const CELL &, int &, int &) const;
		virtual bool iGetCellNumber(int, int, CELL &) const;
		virtual bool iGetContainingCell(int, int, CELL &) const;
		virtual bool iIsWithinCell(int, int, const CELL &) const;
		virtual void iInitialize();
		//-- Setters
		void setSizeX(int);
		void setSizeY(int);
		void setResolutionX(int);
		void setResolutionY(int);

	private:
		int _sizex = DEFAULT_GRID_SIZEX;
		int _sizey = DEFAULT_GRID_SIZEY;
		int _resolutionx = DEFAULT_RESOLUTIONX;
		int _resolutiony = DEFAULT_RESOLUTIONY;
		std::vector<CELL> _cells;
	};
} // namespace env
#endif // !GRID_H
```
> **Note**: The *Grid* object realizes the *IGrid* interface.


## Demo

Our 2D Grid app architecture is now complete! The build strategy is exactly the same as what we have presented in a [previous post][3] --- we refer the reader to that post for more details. The main file for the demo contains the following :

**main.cpp**

```c++
#include "App.h"
#include "GridViewer.h"
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
            (App::DEFAULT_WIDTH*App::DEFAULT_RESX),
            (App::DEFAULT_HEIGHT*App::DEFAULT_RESY)
        ),
        "SFML 2D Grid",
        sf::Style::Titlebar | sf::Style::Close,
        settings
    );
    window.clear(sf::Color::White);
    window.setFramerateLimit(120);
    window.setActive(false);
    
    // -- application
    App app;
    app.setWindow(&window);
    
    //-- grid 2D
    Grid g;
    g.setSizeX(App::DEFAULT_WIDTH);
    g.setSizeY(App::DEFAULT_HEIGHT);
    g.setResolutionX(App::DEFAULT_RESX);
    g.setResolutionY(App::DEFAULT_RESY);
    g.iInitialize();
    app.setGrid(&g);
    
    //-- viewer
    GridViewer gviewer;
    app.setViewer(&gviewer);
    gviewer.initialize();
    gviewer.iActivate();
    
    //-- launch application
    std::thread rendering_thread(&App::display, &app);
    app.run();
    rendering_thread.join();
    
    return 0;
}
```

## Configure and Build

The interested reader can fork the complete source code from [here][2] and run the following in a terminal at the root of the project folder :

### on windows

```shell
  $ cmake  -G "Visual Studio $(Version)" -S . -B ./build 
  $ cmake  --build ./build --config Debug --target app
  $ ./bin/Debug/app
```

### on linux

```shell
  $ mkdir build  
  $ cd build
  $ cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE=Debug
  $ cmake --build ./ --target app --config Debug
  $ ../bin/Debug/app
```

![screenshot](/images/sfml-2d-grid.gif)

You should see a clickable window with a 2D-Grid displayed on it! Enjoy and feel free to send me your feedbacks!


[1]: https://www.sfml-dev.org/
[2]: https://github.com/kanmeugne/sfml2dgrid/releases/tag/sfml-2d-grid
[3]: /posts/sfml-cmake-windows
