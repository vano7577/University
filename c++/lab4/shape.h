#pragma once

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
public:
	//virtual ~Shape();
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC, bool) = 0;
	virtual Shape *Copy() = 0;
};

class PointShape : public virtual Shape
{
public:
	void Show(HDC, bool);
	Shape *Copy();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC, bool);
	virtual Shape *Copy();
};

class RectShape : public virtual Shape
{
public:
	virtual void Show(HDC, bool);
	virtual Shape *Copy();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC, bool);
	virtual Shape *Copy();
};

class LineOOShape : public LineShape, public EllipseShape
{
public:
	virtual void Show(HDC, bool);
	virtual LineOOShape *Copy();
};

class CubeShape : public LineShape, public RectShape
{
public:
	virtual void Show(HDC, bool);
	virtual CubeShape *Copy();
};