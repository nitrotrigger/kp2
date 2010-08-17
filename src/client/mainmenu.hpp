#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "gui/container.hpp"
#include "gui/button.hpp"
#include "gui/image.hpp"

#include "graphics/texturecollection.hpp"

class MainMenu : public Container
{
	public:
		MainMenu(TextureCollection& textureCollection);
		
		virtual void onResize(Window& window);

	private:
		Image background;
		Image title;
	
		Button netgameButton;	
		Button localgameButton;		
		Button aboutButton;
		Button settingsButton;		
		Button quitBbutton;		
	
		void netgameClickHandler();
		void localgameClickHandler();
		void aboutClickHandler();		
		void settingsClickHandler();
		void quitClickHandler();
};

#endif // MAINMENU_HPP
