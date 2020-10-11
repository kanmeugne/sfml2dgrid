#ifndef PHEROMONVIEWER_H
#define PHEROMONVIEWER_H

#include "AbstractViewer.h"
#include "IGrid.h"
#include <vector>

class PheromonViewer : public AbstractViewer
{
public:
    PheromonViewer() = default;
    virtual ~PheromonViewer() = default;

protected:
    virtual void iDraw();

private:
    void drawPheromon(IGrid::ICellFunctor &);
};
#endif // !PHEROMONVIEWER_H