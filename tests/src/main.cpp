#include <gmock/gmock.h>
#include "Grid.h"

using namespace testing;

class GridManipulation : public Test{
    public:
        env::Grid _grid;
        GridManipulation():_grid(){}
};

TEST_F(GridManipulation, Grid_CheckSizeInitialisation)
{
    ASSERT_EQ(_grid.iGetSizeY(), env::DEFAULT_GRID_SIZEY);
    ASSERT_EQ(_grid.iGetSizeX(), env::DEFAULT_GRID_SIZEX);
}

TEST_F(GridManipulation, Grid_CheckResolutionInitialisation)
{
    ASSERT_EQ(_grid.iGetResolutionY(), env::DEFAULT_RESOLUTIONY);
    ASSERT_EQ(_grid.iGetResolutionX(), env::DEFAULT_RESOLUTIONX);
}

TEST_F(GridManipulation, Grid_CheckSizeModification)
{
    const int height = 5;
    const int width = 4;
    _grid.setSizeX(width);
    _grid.setSizeY(height);
    ASSERT_EQ(_grid.iGetSizeY(), height);
    ASSERT_EQ(_grid.iGetSizeX(), width);
}

TEST_F(GridManipulation, Grid_CheckResolutionModification)
{
    const int resx = 5;
    const int resy = 4;
    _grid.setResolutionX(resx);
    _grid.setResolutionY(resy);
    ASSERT_EQ(_grid.iGetResolutionY(), resy);
    ASSERT_EQ(_grid.iGetResolutionX(), resx);
}

TEST_F(GridManipulation, Grid_CheckNumberOfCells)
{
    const int height = 5;
    const int width = 4;
    _grid.setSizeX(width);
    _grid.setSizeY(height);
    ASSERT_EQ(_grid.iGetNumberOfCells(), 5*4);
}

TEST_F(GridManipulation, Grid_CheckFirstCellPosition)
{
    int x=0, y=0;
    env::CELL c;
    _grid.iGetContainingCell(x, y, c);
    ASSERT_EQ(c._id, 0);
}

TEST_F(GridManipulation, Grid_LastCellPosition)
{
    int x = _grid.iGetSizeX()*_grid.iGetResolutionX()-1;
    int y = _grid.iGetSizeY()*_grid.iGetResolutionY()-1;
    env::CELL c;
    _grid.iGetContainingCell(x, y, c);
    ASSERT_EQ(c._id, _grid.iGetNumberOfCells()-1);
}

TEST_F(GridManipulation, Grid_OutOfBoundCell)
{
    int x = 20;
    int y = 1;
    env::CELL c;
    ASSERT_FALSE(_grid.iGetContainingCell(x, y, c));
}

TEST_F(GridManipulation, Grid_RandomInBoundCellFirstLine)
{
    int x = 5;
    int y = 0;
    env::CELL c;
    ASSERT_TRUE(_grid.iGetContainingCell(x, y, c));
    ASSERT_EQ(c._id, 5);
}

TEST_F(GridManipulation, Grid_RandomInBoundCellFirstColumn)
{
    int y = 5;
    int x = 0;
    env::CELL c;
    ASSERT_TRUE(_grid.iGetContainingCell(x, y, c));
    ASSERT_EQ(c._id, 50);
}

int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
