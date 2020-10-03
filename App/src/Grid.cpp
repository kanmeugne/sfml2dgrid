#include "Grid.h"

void Grid::iApplyOnCells(ICellFunctor& cf) const
{
	for (unsigned int i = 0; i<_cells.size(); i++)
		cf(i);
}

unsigned int Grid::iGetSizeX() const
{
	return _sizex;
}

unsigned int Grid::iGetSizeY() const
{
	return _sizey;
}

unsigned int Grid::iGetNumberOfCells() const
{
	return _sizex * _sizey;
}

unsigned int Grid::iGetResolutionX() const
{
	return _resolutionx;
}

unsigned int Grid::iGetResolutionY() const
{
	return _resolutiony;
}

bool Grid::iGetCellPosition(CELL cell, unsigned int &x, unsigned int &y) const
{
	y = (0.5 + (cell / _sizex))*_resolutiony;
	x = (0.5 + (cell % _sizex))*_resolutionx;
	return (cell < iGetNumberOfCells());
}

bool Grid::iGetCellNumber(unsigned int i, unsigned int j, CELL& cell) const
{
	cell = j + _sizex * i;
	return (cell < iGetNumberOfCells()) && (i < iGetSizeY()) && (j < iGetSizeX());
}

bool Grid::iIsObstacle(const CELL cell) const
{
	bool result = false;
	if ((cell < iGetNumberOfCells()) && (_cells[cell]==1))
		result = true;
	return result;
}

bool Grid::iGetCellCoordinates(CELL cell, unsigned int &i, unsigned int &j) const
{
	i = cell / _sizex;
	j = cell % _sizex;
	return (i < iGetSizeX()) && (j < iGetSizeY());
}

bool Grid::iIsWithinCell(const unsigned int posx, const unsigned int posy, CELL cell) const
{
	CELL c;
	return (iGetContainingCell(posx, posy, c) && (cell==c));
}

void Grid::iInitialize()
{
	_cells.reserve(iGetNumberOfCells());
	for (CELL i = 0; i < iGetNumberOfCells(); i++)
		_cells.push_back(0);
}

bool Grid::iAddObstacle(const CELL cell)
{
	bool result = false;
	if (cell < iGetNumberOfCells() && _cells[cell] == 0)
	{
		_cells[cell] = 1;
		result = true;
	}
	return result;
}

bool Grid::iRemoveObstacle(const CELL cell)
{
	bool result = false;
	if (cell < iGetNumberOfCells() && _cells[cell] == 0)
	{
		_cells[cell] = 0;
		result = true;
	}
	return result;
}

bool Grid::iGetContainingCell(const unsigned int x, const unsigned int y, CELL& cell) const
{
	unsigned int cellx (x / _resolutionx);
	unsigned int celly (y / _resolutiony);
	cell = (cellx + celly * _sizex);
	return (x >= 0) && (y >= 0) && (cellx < _sizex) && (celly < _sizey);
}

void Grid::setSizeX(unsigned int sizex)
{
	_sizex = sizex;
}

void Grid::setSizeY(unsigned int sizey)
{
	_sizey = sizey;
}

void Grid::setResolutionX(unsigned int resx)
{
	_resolutionx = resx;
}

void Grid::setResolutionY(unsigned int resy)
{
	_resolutiony = resy;
}
