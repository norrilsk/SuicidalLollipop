#ifndef _DRAWABLEOBJECT
#define _DRAWABLEOBJECT
class DrawableObject
{
public:
	virtual void draw() = 0;

	DrawableObject()
	{
	}

	virtual ~DrawableObject()
	{
	}
};
#endif
