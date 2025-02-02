#ifndef OBSTACLEVIEWER_H
#define OBSTACLEVIEWER_H

#include "AbstractViewer.h"

namespace env
{
    class ICellFunctor;
};

namespace viewers
{
    class ObstacleViewer : public AbstractViewer
    {
    public:
        ObstacleViewer() = default;
        virtual ~ObstacleViewer() = default;

    protected:
        virtual void iDraw();

    private:
        void drawObstacles(env::ICellFunctor &);
    };
} // namespace viewers
#endif // !OBSTACLEVIEWER_H