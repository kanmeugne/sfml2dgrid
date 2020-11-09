#include "Grid.h"

using namespace env;

int Grid::iGetSizeX() const
{
	return _sizex;
}

int Grid::iGetSizeY() const
{
	return _sizey;
}

int Grid::iGetNumberOfCells() const
{
	return _sizex * _sizey;
}

int Grid::iGetResolutionX() const
{
	return _resolutionx;
}

int Grid::iGetResolutionY() const
{
	return _resolutiony;
}

bool Grid::iGetCellPosition(const CELL& cell, int &x, int &y) const
{
	y = (0.5 + (cell._id / _sizex))*_resolutiony;
	x = (0.5 + (cell._id % _sizex))*_resolutionx;
	return (cell._id < iGetNumberOfCells());
}

bool Grid::iGetCellNumber(int i, int j, CELL& cell) const
{
	cell._id = j + _sizex * i;
	return (cell._id < iGetNumberOfCells()) && (i < iGetSizeY()) && (j < iGetSizeX());
}

bool Grid::iGetCellCoordinates(const CELL& cell, int &i, int &j) const
{
	i = cell._id / _sizex;
	j = cell._id % _sizex;
	return (i < iGetSizeX()) && (j < iGetSizeY());
}

bool Grid::iIsWithinCell(int posx, int posy, const CELL& cell) const
{
	CELL c;
	return (iGetContainingCell(posx, posy, c) && (cell._id==c._id));
}

void Grid::iInitialize()
{
	_cells.reserve(iGetNumberOfCells());
	for (int i = 0; i < iGetNumberOfCells(); i++)
	{
		CELL c {i};
		_cells.push_back(c);
	}
}

bool Grid::iGetContainingCell(int x, int y, CELL& cell) const
{
	int cellx (x / _resolutionx);
	int celly (y / _resolutiony);
	cell._id = (cellx + celly * _sizex);
	return (x >= 0) && (y >= 0) && (cellx < _sizex) && (celly < _sizey);
}

void Grid::setSizeX(int sizex)
{
	_sizex = sizex;
}

void Grid::setSizeY(int sizey)
{
	_sizey = sizey;
}

void Grid::setResolutionX(int resx)
{
	_resolutionx = resx;
}

void Grid::setResolutionY(int resy)
{
	_resolutiony = resy;
}
