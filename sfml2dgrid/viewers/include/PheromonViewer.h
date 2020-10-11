#ifndef PHEROMONVIEWER_H
#define PHEROMONVIEWER_H

#include "AbstractViewer.h"

namespace env
{
    class ICellFunctor;
};

namespace viewers
{
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
} // namespace viewers
#endif // !PHEROMONVIEWER_H