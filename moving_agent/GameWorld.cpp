#include "stdafx.h"
#include "GameWorld.h"


GameWorld::GameWorld() {
	m_vehicle = new Vehicle(this);
	m_crosshair = (HBITMAP)LoadImage(nullptr, TEXT("..\\crosshair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hdcmem = CreateCompatibleDC(nullptr);
	m_old_crosshair = (HBITMAP)SelectObject(m_hdcmem, m_crosshair);
	m_target = Vector2D(100, 200);
}


GameWorld::~GameWorld()
{
	SelectObject(m_hdcmem, m_old_crosshair);
	DeleteObject(m_crosshair);
	DeleteDC(m_hdcmem);
}


void GameWorld::update(double time_elapsed) {
	m_vehicle->update(time_elapsed);
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
	long tmp = my_clock.total_msec();
	TextOut(hdc, cx, 3 * cy, buf, wsprintf(buf, TEXT("Time elapsed = %d.%d s"), tmp / 1000, tmp % 1000));
	SetTextColor(hdc, ori_color);

	BitBlt(hdc, (int)(m_target.x()-57/2), (int)(m_target.y()-57/2), 57, 57, m_hdcmem, 0, 0, SRCCOPY);

	m_vehicle->render(hdc);
}
