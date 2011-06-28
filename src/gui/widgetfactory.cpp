#include "widgetfactory.hpp"

#include "button.hpp"
#include "label.hpp"
#include "field.hpp"
#include "graph.hpp"
#include "listbox.hpp"
#include "select.hpp"
#include "scrollbox.hpp"
#include "verticalscrollbar.hpp"
#include "horizontalscrollbar.hpp"
#include "graphics/texture.hpp"
#include "columnlayoutcontainer.hpp"
#include "rowlayoutcontainer.hpp"
#include "freecontainer.hpp"
#include "client/playervehiclewidget.hpp"
#include "client/gauge.hpp"

#include "utils/string.hpp"

Widget* WidgetFactory::build(WidgetNode& node)
{
	Widget* widget = NULL;
	
	if(node.type == "RowLayout")
		widget = new RowLayoutContainer();
	else if(node.type == "ColumnLayout")
		widget = new ColumnLayoutContainer();
	else if(node.type == "FreeLayout")
		widget = new FreeContainer();
	else if(node.type == "Button")
		widget = new Button();
	else if(node.type == "Label")
		widget = new Label();
	else if(node.type == "Field")
		widget = new Field();
	else if(node.type == "Graph")
		widget = new Graph();
	else if(node.type == "Image")
		widget = new Image();
	else if(node.type == "ListBox")
		widget = new Listbox();
	else if(node.type == "PlayerVehicleWidget")
		widget = new PlayerVehicleWidget();
	else if(node.type == "Select")
		widget = new Select();
	else if(node.type == "Gauge")
		widget = new Gauge();
	else if(node.type == "Spacer")
		widget = new Widget();
	else if(node.type == "ScrollBox")
		widget = new ScrollBox();
	else if(node.type == "VerticalScrollBar")
		widget = new VerticalScrollBar();
	else if(node.type == "HorizontalScrollBar")
		widget = new HorizontalScrollBar();
	
	if(dynamic_cast<LayoutContainer*>(widget))
		applyAttributes(dynamic_cast<LayoutContainer*>(widget), node.attributes);
	if(dynamic_cast<TextWidget*>(widget))
		applyAttributes(dynamic_cast<TextWidget*>(widget), node.attributes);
	if(dynamic_cast<Image*>(widget))
		applyAttributes(dynamic_cast<Image*>(widget), node.attributes);
	if(dynamic_cast<Gauge*>(widget))
		applyAttributes(dynamic_cast<Gauge*>(widget), node.attributes);
	if(dynamic_cast<Widget*>(widget))
		applyAttributes(widget, node.attributes);
	
	
	return widget;
}

void WidgetFactory::applyAttributes(LayoutContainer* layoutContainer, const IniFile& attributes)
{
	layoutContainer->showOuterPadding(attributes.getValueWithDefault("showOuterPadding", 0));
	layoutContainer->showInnerPadding(attributes.getValueWithDefault("showInnerPadding", 1));
}

void WidgetFactory::applyAttributes(TextWidget* textWidget, const IniFile& attributes)
{
	textWidget->setText(attributes.getValueWithDefault("text", ""));
	
	std::string font = attributes.getValueWithDefault("font", "");
	
	if(font != "")
		textWidget->setFont(Font(font));
}

void WidgetFactory::applyAttributes(Image* image, const IniFile& attributes)
{
	std::string filename = attributes.getValueWithDefault("file", "");
	
	if(filename != "")
		image->setTexture(Texture(filename));
	
	std::string scalingMode = attributes.getValueWithDefault("scaling", "");
	
	if(scalingMode == "none")
		image->setScalingMode(Image::NONE);
	else if(scalingMode == "proportional")
		image->setScalingMode(Image::PROPORTIONAL);
	else if(scalingMode == "proportionalfill")
		image->setScalingMode(Image::PROPORTIONAL_FILL);
	else if(scalingMode == "stretchfill")
		image->setScalingMode(Image::STRETCH_FILL);
	else if(scalingMode == "nineslice")
		image->setScalingMode(Image::NINE_SLICE);
	
	int border = attributes.getValueWithDefault("nineSliceBorder", 0);
	
	int left = border;
	int top = border;
	int right = border;
	int bottom = border;
	
	try
	{
		attributes.getValue("nineSliceLeft", left);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineSliceTop", top);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineSliceRight", right);
	}
	catch(...){}
	
	try
	{
		attributes.getValue("nineSliceBottom", bottom);
	}
	catch(...){}
	
	image->setNineSliceCorners(Vector2D(left, top), Vector2D(right, bottom));
}

void WidgetFactory::applyAttributes(Widget* widget, const IniFile& attributes)
{
	widget->setName(attributes.getValueWithDefault("name", ""));
	widget->setVisible(attributes.getValueWithDefault("visible", 1));
	widget->setToolTip(attributes.getValueWithDefault("tooltip", ""));
	
	std::string color = attributes.getValueWithDefault("background", "");
	
	if(color != "")
	{
		std::vector<std::string> tokens = tokenize(color, ",");
		
		float r = 0.0;
		float g = 0.0;
		float b = 0.0;
		float a = 1.0;
		
		if(tokens.size() >= 3)
		{
			r = convertTo<float>(tokens[0]);
			g = convertTo<float>(tokens[1]);
			b = convertTo<float>(tokens[2]);
		}
		
		if(tokens.size() == 4)
			a = convertTo<float>(tokens[3]);
			
		widget->setBackgroundColor(Color(r, g, b, a));
	}
}

void WidgetFactory::applyAttributes(Gauge* gauge, const IniFile& attributes)
{
	float minValue = attributes.getValueWithDefault("minValue", 0.0);
	float maxValue = attributes.getValueWithDefault("maxValue", 100.0);
	float minAngle = attributes.getValueWithDefault("minAngle", 0.0);
	float maxAngle = attributes.getValueWithDefault("maxAngle", 0.0);

	gauge->setValueRange(minValue, maxValue);
	gauge->setAngleRange(minAngle, maxAngle);

	std::string gaugeFileName = attributes.getValueWithDefault("gauge", "");

	if(gaugeFileName != "")
		gauge->setGaugeTexture(Texture(gaugeFileName));

	std::string needleFileName = attributes.getValueWithDefault("needle", "");

	if(needleFileName != "")
		gauge->setNeedleTexture(Texture(needleFileName));
}

