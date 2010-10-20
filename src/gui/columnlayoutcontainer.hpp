#ifndef COLUMNLAYOUTCONTAINER_HPP
#define COLUMNLAYOUTCONTAINER_HPP

#include "layoutcontainer.hpp"

class ColumnLayoutContainer : public LayoutContainer
{
	protected:
		virtual int getDividedSide(Vector2D size);
		virtual int getNonDividedSide(Vector2D size);
		virtual Vector2D convertDimensionsToVector(int dividedSide,int nonDividedSide);

};

#endif // COLUMNLAYOUTCONTAINER_HPP

