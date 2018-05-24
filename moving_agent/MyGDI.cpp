#include "stdafx.h"
#include "MyGDI.h"


MyGDI::MyGDI() : m_cnt_text(0)
{
}


MyGDI::~MyGDI()
{
}


MyGDI& MyGDI::instance() {
	static MyGDI ins;
	return ins;
}

void MyGDI::draw_axes(int width, int height) {
	MoveToEx(m_hdc, width / 2, 0, nullptr);
	LineTo(m_hdc, width / 2, height);
	MoveToEx(m_hdc, 0, height / 2, nullptr);
	LineTo(m_hdc, width, height / 2);
}

void MyGDI::draw_circle(const Vector2D &c, double r) {
	Ellipse(m_hdc, static_cast<int>(c.m_x - r), static_cast<int>(c.m_y - r), static_cast<int>(c.m_x + r), static_cast<int>(c.m_y + r));
}

void MyGDI::draw_dark_gray_circle(const Vector2D &c, double r) {
	HBRUSH old_brush = (HBRUSH)SelectObject(m_hdc, GetStockObject(DKGRAY_BRUSH));
	Ellipse(m_hdc, static_cast<int>(c.m_x - r), static_cast<int>(c.m_y - r), static_cast<int>(c.m_x + r), static_cast<int>(c.m_y + r));
	SelectObject(m_hdc, old_brush);
}

void MyGDI::draw_gray_circle(const Vector2D &c, double r) {
	HBRUSH old_brush = (HBRUSH)SelectObject(m_hdc, GetStockObject(GRAY_BRUSH));
	Ellipse(m_hdc, static_cast<int>(c.m_x - r), static_cast<int>(c.m_y - r), static_cast<int>(c.m_x + r), static_cast<int>(c.m_y + r));
	SelectObject(m_hdc, old_brush);
}

void MyGDI::draw_light_gray_circle(const Vector2D &c, double r) {
	HBRUSH old_brush = (HBRUSH)SelectObject(m_hdc, GetStockObject(LTGRAY_BRUSH));
	Ellipse(m_hdc, static_cast<int>(c.m_x - r), static_cast<int>(c.m_y - r), static_cast<int>(c.m_x + r), static_cast<int>(c.m_y + r));
	SelectObject(m_hdc, old_brush);
}

void MyGDI::draw_image(const Vector2D &c, double sx, double sy, HDC image) {
	BitBlt(m_hdc, static_cast<int>(c.m_x - sx / 2.0), static_cast<int>(c.m_y - sy / 2.0), static_cast<int>(sx), static_cast<int>(sy), image, 0, 0, SRCCOPY);
}

void MyGDI::draw_closed_shape(const std::vector<Vector2D> &pts) {
	MoveToEx(m_hdc, (int)pts[0].m_x, (int)pts[0].m_y, nullptr);
	for (unsigned int p = 1; p<pts.size(); ++p) {
		LineTo(m_hdc, (int)pts[p].m_x, (int)pts[p].m_y);
	}
	LineTo(m_hdc, (int)pts[0].m_x, (int)pts[0].m_y);
}

void MyGDI::draw_empty_circle(const Vector2D &c, double r) {
	HBRUSH old_brush = (HBRUSH)SelectObject(m_hdc, GetStockObject(NULL_BRUSH));
	Ellipse(m_hdc, static_cast<int>(c.m_x - r), static_cast<int>(c.m_y - r), static_cast<int>(c.m_x + r), static_cast<int>(c.m_y + r));
	SelectObject(m_hdc, old_brush);

}

void MyGDI::draw_text_auto_pos(const TCHAR *buf, int len) {
	COLORREF ori_color = SetTextColor(m_hdc, RGB(100, 200, 200));
	TEXTMETRIC tm;
	GetTextMetrics(m_hdc, &tm);
	long cx = tm.tmAveCharWidth;
	long cy = tm.tmExternalLeading + tm.tmHeight;
	SetBkMode(m_hdc, TRANSPARENT);
	TextOut(m_hdc, cx, cy*m_cnt_text, buf, len);
	SetBkMode(m_hdc, OPAQUE);
	SetTextColor(m_hdc, ori_color);
	m_cnt_text++;

}

void MyGDI::draw_wall(const Vector2D &from, const Vector2D &to, int width) {
	HPEN wall_pen = CreatePen(PS_SOLID, width, RGB(128, 128, 128));
	HPEN old_pen = (HPEN)SelectObject(m_hdc, wall_pen);
	MoveToEx(m_hdc, from.m_x, from.m_y, nullptr);
	LineTo(m_hdc, to.m_x, to.m_y);
	SelectObject(m_hdc, old_pen);
	DeleteObject(wall_pen);
}

void MyGDI::draw_feeler(const Vector2D &from, const Vector2D &to) {
	MoveToEx(m_hdc, from.m_x, from.m_y, nullptr);
	LineTo(m_hdc, to.m_x, to.m_y);
}

void MyGDI::draw_force(const Vector2D &from, const Vector2D &to) {
	HPEN force_pen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
	HPEN old_pen = (HPEN)SelectObject(m_hdc, force_pen);
	MoveToEx(m_hdc, from.m_x, from.m_y, nullptr);
	LineTo(m_hdc, to.m_x, to.m_y);
	SelectObject(m_hdc, old_pen);
	DeleteObject(force_pen);
}


