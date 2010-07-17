#include "localgamemenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "graphics.hpp"
#include "shared/string.hpp"
#include "connection.hpp"

LocalGameMenu::LocalGameMenu()
{
	m_background_texture.load("data/images/localgamemenu.png");
	m_background.setTexture(&m_background_texture);
	
	m_title.setFont(Font("title"));
	m_title.setText("Yksinpeli");			
	
	m_new_game_button.setText("Uusi tilanne");
	m_new_game_button.setClickHandler(Callback0(this,&LocalGameMenu::newClickHandler));
	m_load_game_button.setText("Lataa tilanne");
	
	//m_save_game_button.setText("Tallenna peli");
	
	m_back_button.setText("Peruuta");
	m_back_button.setClickHandler(Callback0(this,&LocalGameMenu::backClickHandler));
	
	addWidget(&m_background);
	
	addWidget(&m_title);
	
	addWidget(&m_new_game_button);
	addWidget(&m_load_game_button);	
	
	addWidget(&m_back_button);	
}

void LocalGameMenu::onResize(Graphics& graphics)
{
	m_background.setSize(Vector2D(1,1));
		
	m_title.setPosition(TITLE_POSITION);
	m_title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	m_new_game_button.setPosition(buttonpos);
	m_new_game_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_load_game_button.setPosition(buttonpos);
	m_load_game_button.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	m_back_button.setPosition(BACK_BUTTON_POSITION);
	m_back_button.autoSize();
}

void LocalGameMenu::onShow()
{

}

void LocalGameMenu::backClickHandler()
{
	setVisible(false);
	getRootWidget("mainmenu")->setVisible(true);
}

void LocalGameMenu::newClickHandler()
{
	setVisible(false);
	getRootWidget("newlocalgamemenu")->setVisible(true);
}

