#include "stdafx.h"
#include "GameWorld.h"


GameWorld::GameWorld() {
	m_sheep = new Vehicle(this);
	//m_sheep->set_seek(true);
	//m_sheep->set_flee(true);
	m_sheep->set_wander(true);
	m_wolf = new Vehicle(this);
	//m_wolf->set_pursuit(true);
	m_wolf->set_wander(true);
	m_wolf->pos() = Vector2D(100, 100);
	m_crosshair = (HBITMAP)LoadImage(nullptr, TEXT("..\\crosshair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hdcmem = CreateCompatibleDC(nullptr);
	m_old_crosshair = (HBITMAP)SelectObject(m_hdcmem, m_crosshair);
	m_target = Vector2D(100, 200);
	m_panic_dist = 100.0;
}


GameWorld::~GameWorld()
{
	SelectObject(m_hdcmem, m_old_crosshair);
	DeleteObject(m_crosshair);
	DeleteDC(m_hdcmem);
	delete m_wolf;
	delete m_sheep;
}


void GameWorld::update(double time_elapsed) {
	m_sheep->update(time_elapsed);
	m_wolf->update(time_elapsed);
}

void GameWorld::render(HDC hdc) {
	//SetMapMode(hdc, MM_ANISOTROPIC);
	//SetWindowExtEx(hdc, m_width / 2, m_height / 2, nullptr);
	//SetViewportExtEx(hdc, m_width / 2, -m_height / 2, nullptr);
	//SetViewportOrgEx(hdc, m_width / 2, m_height / 2, nullptr);

	MoveToEx(hdc, m_width / 2, 0, nullptr);
	LineTo(hdc, m_width / 2, m_height);
	MoveToEx(hdc, 0, m_height / 2, nullptr);
	LineTo(hdc, m_width, m_height / 2);

	COLORREF ori_color = SetTextColor(hdc, RGB(128, 128, 128));
	TCHAR buf[512];
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	long cx = tm.tmAveCharWidth;
	long cy = tm.tmExternalLeading + tm.tmHeight;
	TextOut(hdc, cx, cy, buf, wsprintf(buf, TEXT("Time Quantum = %d ms"), my_config.time_quantum()));
	TextOut(hdc, cx, 2 * cy, buf, wsprintf(buf, TEXT("Time Delta = %d ms  Left(-) / Right(+)"), my_config.time_delta()));
	TextOut(hdc, cx, 3 * cy, buf, wsprintf(buf, TEXT("Panic dist = %d pts  Down(-) / Up(+)"), (int)panic_dist()));
	long tmp = my_clock.total_msec();
	TextOut(hdc, cx, 4 * cy, buf, wsprintf(buf, TEXT("Time elapsed = %d.%d s"), tmp / 1000, tmp % 1000));
	SetTextColor(hdc, ori_color);

	TextOut(hdc, cx, height() - cy, buf, wsprintf(buf, TEXT("Position of the wolf is (%d, %d)"), (int)(m_wolf->pos().x()), (int)(m_wolf->pos().y())));
	TextOut(hdc, cx, height() - 2* cy, buf, wsprintf(buf, TEXT("Position of the sheep is (%d, %d)"), (int)(m_sheep->pos().x()), (int)(m_sheep->pos().y())));


	BitBlt(hdc, (int)(m_target.x()-57/2), (int)(m_target.y()-57/2), 57, 57, m_hdcmem, 0, 0, SRCCOPY);

	m_sheep->render(hdc);
	HPEN red_pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN old_pen = (HPEN)SelectObject(hdc, red_pen);
	m_wolf->render(hdc);
	SelectObject(hdc, old_pen);
	DeleteObject(red_pen);
}
