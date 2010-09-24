#ifndef WIDGET_HPP
#define WIDGET_HPP

#include "graphics/vector2d.hpp"
#include "graphics/window.hpp"

#include "events/eventlistener.hpp"
#include "events/keyevent.hpp"
#include "events/mouseevent.hpp"
#include "events/drawevent.hpp"

#include "utils/noncopyable.hpp"

class Container;

class Widget: public EventListener, public NonCopyable
{
	public:
		void setPosition(Vector2D position);	
		void setPixelPosition(Vector2D position);	
		Vector2D getPosition();	

		void setSize(Vector2D size);	
		void setPixelSize(Vector2D size);	
		Vector2D getSize();
		
		void setVisible(bool visible);
		bool getVisible();
		
		/*
		These are the functions for signaling that an event has
		happened.		
		*/		
		virtual void keyDown(KeyEvent event);
		virtual void keyUp(KeyEvent event);				
		
		virtual void mouseDown(MouseEvent event);
		virtual void mouseUp(MouseEvent event);
		virtual void mouseMove(MouseEvent event);	
		
		virtual void resize(Window& window);		
		
		virtual void mouseOn();
		virtual void mouseOut();		
		
		virtual void blur();
		virtual void focus();	
		
		virtual void draw(DrawEvent event);		
		
		Container* getParent();
		
		Widget();
		virtual ~Widget();
	
	protected:	
		bool hasPixelPosition();
		bool hasPixelSize();
	
		/*
		These are the functions that implement object specific handler
		for an event.
		*/		
		virtual void onKeyDown(KeyEvent event);
		virtual void onKeyUp(KeyEvent event);
		
		virtual void onMouseDown(MouseEvent event);
		virtual void onMouseUp(MouseEvent event);
		virtual void onMouseMove(MouseEvent event);
	
		virtual void onResize(Window& window);
		
		virtual void onMouseOn();
		virtual void onMouseOut();	
		
		virtual void onBlur();
		virtual void onFocus();	
		
		virtual void onShow();	
		virtual void onHide();	
		
		virtual void onDraw(DrawEvent event);
	
	private:
		void setParent(Container* container);
			
		bool visible;
			
		Container* parent;
	
		Vector2D position;
		bool pixelPosition;
		
		Vector2D size;
		bool pixelSize;		
		
		friend class Container;
};

#include "container.hpp"

#endif // WIDGET_HPP
