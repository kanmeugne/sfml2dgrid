#ifndef ABSTRACTVIEWER_H
#define ABSTRACTVIEWER_H

class App;

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
    virtual void iSetApp(App*);

	virtual ~AbstractViewer() = default;
    AbstractViewer() = default;
protected:
	// specific draw method (to be concretized in child classes)
	virtual void iDraw() = 0;
    bool _active = false;
    App* _app;
};

class AbstractViewerMgr : public AbstractViewer
{
public:
	virtual void iAddViewer(AbstractViewer*) = 0;
	virtual ~AbstractViewerMgr();
};

#endif // ABSTRACTVIEWER_H