#pragma once
#include <vector>
#include "Vector2D.h"

class MyGDI
{
	HDC m_hdc;
	int m_cnt_text;

	MyGDI();
	~MyGDI();

public:
	static MyGDI& instance();
	void set_dc(HDC hdc) { m_hdc = hdc; }
	void draw_axes(int width, int height);
	void draw_gray_circle(const Vector2D &c, double r);
	void draw_image(const Vector2D &c, double sx, double sy, HDC image);
	void draw_triangle(const std::vector<Vector2D> &pts);
	void draw_empty_circle(const Vector2D &c, double r);
	void draw_text_auto_pos(const TCHAR *buf, int len);
	void reset_text_auto_pos() { m_cnt_text = 0; }
};
#define my_gdi MyGDI::instance()