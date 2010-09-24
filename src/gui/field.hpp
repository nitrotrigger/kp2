#ifndef FIELD_HPP
#define FIELD_HPP

#include "textwidget.hpp"

#include "utils/timer.hpp"

class Field : public TextWidget
{
	public:
		virtual void onDraw(DrawEvent event);
		virtual void onKeyDown(KeyEvent event);
		
		virtual void onFocus();
		virtual void onBlur();
		
		Field();
	
	protected:
		virtual bool doAutoSizeOnChange();
		
	private:
		size_t m_cursorpos;
		
		Timer m_blink_timer;
		bool m_focused;
};

#endif // FIELD_HPP
