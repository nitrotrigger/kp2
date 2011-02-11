#include "careermenu.hpp"

#include <iostream>

#include "ui.hpp"

const float CAREER_SIDEBAR_WIDTH=0.20;

CareerMenu::CareerMenu(TextureCollection& sidebartextures,Container& topLevelGameMenus,Connection& connection):
	topLevelGameMenus(topLevelGameMenus)
{
	connection.addEventHandler(std::tr1::bind(&CareerMenu::onConnectionEvent,this,std::tr1::placeholders::_1));
	
	sidebar.setTexture(sidebartextures.getTexture("background"));
	sidebar.setStretched(true);
	
	garageButton.setText("Autot");
	garageButton.setClickHandler(std::tr1::bind(&CareerMenu::garageButtonClick,this));
	tuningButton.setText("Viritys");
	tuningButton.setClickHandler(std::tr1::bind(&CareerMenu::tuningButtonClick,this));
	financeButton.setText("Raha-asiat");
	financeButton.setClickHandler(std::tr1::bind(&CareerMenu::tuningButtonClick,this));
	raceButton.setText("Kisat");
	raceButton.setClickHandler(std::tr1::bind(&CareerMenu::tuningButtonClick,this));
	
	addWidget(topLevelGameMenus);
	
	addWidget(sidebar);
		
	addWidget(infoLabel);
	
	addWidget(garageButton);
	addWidget(tuningButton);
	addWidget(financeButton);
	addWidget(raceButton);	
}

void CareerMenu::onResize(Window& window)
{
	sidebar.setSize(Vector2D(CAREER_SIDEBAR_WIDTH,1));
	
	infoLabel.setPosition(TITLE_POSITION);
	infoLabel.autoSize();
	
	Vector2D buttonpos=CONTENT_POSITION;

	garageButton.setPosition(buttonpos);
	garageButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	tuningButton.setPosition(buttonpos);
	tuningButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	financeButton.setPosition(buttonpos);
	financeButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	raceButton.setPosition(buttonpos);
	raceButton.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	topLevelGameMenus.setSize(Vector2D(1.0-CAREER_SIDEBAR_WIDTH,1));
	topLevelGameMenus.setPosition(Vector2D(CAREER_SIDEBAR_WIDTH,0));
}

void CareerMenu::onConnectionEvent(Connection& connection)
{
	std::stringstream ss;
	
	const PlayerInfo& playerInfo = connection.getPlayerInfo();
	
	ss<<playerInfo.name<<std::endl;
	ss<<playerInfo.money<<" €";

	infoLabel.setText(ss.str());
	infoLabel.autoSize();
}

void CareerMenu::garageButtonClick()
{
	topLevelGameMenus.showOnlyWidget("garage");
}

void CareerMenu::tuningButtonClick()
{
	topLevelGameMenus.showOnlyWidget("tuning");
}

void CareerMenu::financeButtonClick()
{
	topLevelGameMenus.showOnlyWidget("finance");
}

void CareerMenu::raceButtonClick()
{
	topLevelGameMenus.showOnlyWidget("race");
}

