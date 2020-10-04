#include "Grid.h"

void Grid::iApplyOnCells(ICellFunctor& cf) const
{
	for (int i = 0; i<_cells.size(); i++)
		cf(i);
}

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

bool Grid::iGetCellPosition(CELL cell, int &x, int &y) const
{
	y = (0.5 + (cell / _sizex))*_resolutiony;
	x = (0.5 + (cell % _sizex))*_resolutionx;
	return (cell < iGetNumberOfCells());
}

bool Grid::iGetCellNumber(int i, int j, CELL& cell) const
{
	cell = j + _sizex * i;
	return (cell < iGetNumberOfCells()) && (i < _sizey) && (j < _sizex);
}

bool Grid::iIsObstacle(const CELL cell) const
{
	bool result = false;
	if ((cell < iGetNumberOfCells()) && (_cells[cell]==1))
		result = true;
	return result;
}

bool Grid::iGetCellCoordinates(CELL cell, int &i, int &j) const
{
	i = cell / _sizex;
	j = cell % _sizex;
	return (i < _sizex) && (j < _sizey);
}

bool Grid::iIsWithinCell(int posx, int posy, CELL cell) const
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
	if (cell < iGetNumberOfCells() && _cells[cell] == 1)
	{
		_cells[cell] = 0;
		result = true;
	}
	return result;
}

bool Grid::iGetContainingCell(int x, int y, CELL& cell) const
{
	int cellx (x / _resolutionx);
	int celly (y / _resolutiony);
	cell = (cellx + celly * _sizex);
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
