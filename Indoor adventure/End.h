#pragma once
#include "AssertManager.h"

class End : public Drawable, public Transformable
{
private:
	RectangleShape dark;

	Text end_text;
	Text result_text;
	Text continue_text;

public:
	End();

	void result(bool victory, int bonuses);

	virtual void draw(RenderTarget& target, RenderStates states) const;
};