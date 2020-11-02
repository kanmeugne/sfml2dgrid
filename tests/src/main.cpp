#include <gmock/gmock.h>
#include "grid.h"

using namespace testing;

class GridObjects : public Test{};

TEST(GridObjects, Parser_LowerSingleLetter)
{
    const int height = 10;
    const int width = 10;
    env::Grid g;
    g.setSizeX(height);
    g.setSizeY(width);
    ASSERT_EQ(g.iGetSizeY(), height);
    ASSERT_EQ(g.iGetSizeX(), width);

}

int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
