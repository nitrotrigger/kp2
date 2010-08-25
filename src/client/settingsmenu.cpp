#include "settingsmenu.hpp"

#include <iostream>

#include "ui.hpp"
#include "utils/string.hpp"

SettingsMenu::SettingsMenu(Window& window,TextureCollection& textures):
	window(window)
{
	setVisible(false);

	title.setFont(Font("title"));
	title.setText("Asetukset");			
	
	sizeLabel.setText("Ikkunan koko");
	fullscreenLabel.setText("Kokoruututila");
	vsyncLabel.setText("Vsync");	
	
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	std::vector<Vector2D>::iterator i;
	
	for(i=possibleSizes.begin();i!=possibleSizes.end();++i)
	{
		std::string str;
		str+=convertToString((*i).getX());
		str+="x";
		str+=convertToString((*i).getY());
		
		sizeSelect.addItem(str);
	}
	
	fullscreenSelect.addItem("ei");
	fullscreenSelect.addItem("kyllä");
	
	vsyncSelect.addItem("ei");
	vsyncSelect.addItem("kyllä");
	
	backButton.setText("Takaisin");
	backButton.setClickHandler(Callback0(this,&SettingsMenu::backClick));
	applyButton.setText("Ota käyttöön");
	applyButton.setClickHandler(Callback0(this,&SettingsMenu::applyClick));

	addChild(background);
	
	addChild(title);
	
	addChild(sizeLabel);
	addChild(fullscreenLabel);
	addChild(vsyncLabel);	
			
	addChild(sizeSelect);
	addChild(fullscreenSelect);	
	addChild(vsyncSelect);
		
	addChild(backButton);	
	addChild(applyButton);
}

void SettingsMenu::onResize(Window& window)
{
	setSize(Vector2D(1,1));
	background.setSize(Vector2D(1,1));
		
	title.setPosition(TITLE_POSITION);
	title.setSize(TITLE_SIZE);
		
	Vector2D buttonpos=CONTENT_POSITION;

	sizeLabel.setPosition(buttonpos);
	sizeLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	fullscreenLabel.setPosition(buttonpos);
	fullscreenLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	vsyncLabel.setPosition(buttonpos);
	vsyncLabel.autoSize();
	buttonpos+=BUTTON_HEIGHT;
	
	buttonpos=CONTENT_POSITION;
	buttonpos.setX(0.5);
	
	sizeSelect.setPosition(buttonpos);
	sizeSelect.autoSize();	
	buttonpos+=BUTTON_HEIGHT;
	
	fullscreenSelect.setPosition(buttonpos);
	fullscreenSelect.autoSize();
	buttonpos+=BUTTON_HEIGHT;	

	vsyncSelect.setPosition(buttonpos);
	vsyncSelect.autoSize();
	buttonpos+=BUTTON_HEIGHT;

	backButton.setPosition(BACK_BUTTON_POSITION);
	backButton.autoSize();

	applyButton.setPosition(NEXT_BUTTON_POSITION);
	applyButton.autoSize();

}

void SettingsMenu::onShow()
{
	updateDisplayOptions();
}

void SettingsMenu::updateDisplayOptions()
{
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	
	for(size_t i=0;i<possibleSizes.size();++i)
	{
		if(window.getSize() == possibleSizes[i])
		{
			sizeSelect.setIndex(i);
			break;
		}			
	}		

	fullscreenSelect.setIndex(window.isFullscreen());
	
	vsyncSelect.setIndex(window.getVsyncPreference());
	
	sizeSelect.autoSize();	
	fullscreenSelect.autoSize();
	vsyncSelect.autoSize();
}

void SettingsMenu::backClick()
{
	setVisible(false);
	getParent()->getChild("mainmenu")->setVisible(true);
}

void SettingsMenu::applyClick()
{
	std::vector<Vector2D> possibleSizes = window.getPossibleSizes();
	Vector2D size=possibleSizes[sizeSelect.getIndex()];

	bool fullscreen=fullscreenSelect.getIndex();
	bool vsync=vsyncSelect.getIndex();
	
	window.setVideoMode(size,32,fullscreen);
	window.setVsyncPreference(vsync);
	
	updateDisplayOptions();
}

