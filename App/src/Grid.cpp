#include "Grid.h"

void Grid::iApplyOnCells(ICellFunctor& cf) const
{
	for (size_t i = 0; i<_cells.size(); i++)
		cf(i);
}

void Grid::iApplyOnSegments(ISegmentFunctor& lf) const
{
	for (auto it = _lines.begin(); it != _lines.end(); it++)
		lf(*it);
}

size_t Grid::iGetSizeX() const
{
	return _sizex;
}

size_t Grid::iGetSizeY() const
{
	return _sizey;
}

size_t Grid::iGetNumberOfCells() const
{
	return _sizex * _sizey;
}

double Grid::iGetResolutionX() const
{
	return _resolutionx;
}

double Grid::iGetResolutionY() const
{
	return _resolutiony;
}

bool Grid::iGetCellPosition(CELL cell, double &x, double &y) const
{
	y = (0.5 + (cell / _sizex))*_resolutiony;
	x = (0.5 + (cell % _sizex))*_resolutionx;
	return (cell < iGetNumberOfCells());
}

bool Grid::iGetCellNumber(size_t i, size_t j, CELL& cell) const
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

bool Grid::iGetCellCoordinates(CELL cell, size_t &i, size_t &j) const
{
	i = cell / _sizex;
	j = cell % _sizex;
	return (i < iGetSizeX()) && (j < iGetSizeY());
}

bool Grid::iIsWithinCell(const float posx, const float posy, CELL cell) const
{
	CELL c;
	return (iGetContainingCell(posx, posy, c) && (cell==c));
}

void Grid::iInitialize()
{
	_cells.reserve(iGetNumberOfCells());
	for (CELL i = 0; i < iGetNumberOfCells(); i++)
		_cells.push_back(0);

	// build vertical lines
	for (CELL i = 0; i <= _sizex; i++)
	{
		Point init (std::make_pair(_resolutionx*i, 0.));
		Point end  (std::make_pair(_resolutionx*i, _resolutiony*_sizey));
		_lines.push_back(std::make_pair(init, end));
	}

	// build horizontal lines
	for (CELL i = 0; i <= _sizey; i++)
	{
		Point init (std::make_pair(0., _resolutiony*i));
		Point end  (std::make_pair(_resolutionx*_sizex, _resolutiony*i));
		_lines.push_back(std::make_pair(init, end));
	}
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

bool Grid::iGetContainingCell(const float x, const float y, CELL& cell) const
{
	size_t cellx (x / _resolutionx);
	size_t celly (y / _resolutiony);
	cell = (cellx + celly * _sizex);
	return (x >= 0) && (y >= 0) && (cellx < _sizex) && (celly < _sizey);
}

void Grid::setSizeX(size_t sizex)
{
	_sizex = sizex;
}

void Grid::setSizeY(size_t sizey)
{
	_sizey = sizey;
}

void Grid::setResolutionX(double resx)
{
	_resolutionx = resx;
}

void Grid::setResolutionY(double resy)
{
	_resolutiony = resy;
}
