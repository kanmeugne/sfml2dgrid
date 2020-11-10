#ifndef ABSTRACTVIEWER_H
#define ABSTRACTVIEWER_H
#include <vector>

class App;

namespace viewers
{
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
		virtual void iSetApp(App *);

		virtual ~AbstractViewer() = default;
		AbstractViewer() = default;

	protected:
		// specific draw method (to be concretized in child classes)
		virtual void iDraw() = 0;
		bool _active = false;
		App *_app;
	};

	// viewer manager, using the composite pattern to
	// aggregate several viewers into one
	class ViewerMgr : public AbstractViewer
	{
	public:
		virtual void iAddViewer(AbstractViewer *);
		virtual ~ViewerMgr() = default;
		ViewerMgr() = default;
		virtual void iSetApp(App *) override;

	protected:
		virtual void iDraw();

	private:
		std::vector<AbstractViewer *> _viewers;
	};
} // namespace viewers

#endif // ABSTRACTVIEWER_H