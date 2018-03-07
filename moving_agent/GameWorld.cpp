#include "stdafx.h"
#include "GameWorld.h"


GameWorld::GameWorld() {
	m_vehicle = new Vehicle(this);
}


GameWorld::~GameWorld()
{
}


void GameWorld::update(double time_elapsed) {
	m_vehicle->update(time_elapsed);
}

void GameWorld::render(HDC hdc) {
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetWindowExtEx(hdc, m_width / 2, m_height / 2, nullptr);
	SetViewportExtEx(hdc, m_width / 2, -m_height / 2, nullptr);
	SetViewportOrgEx(hdc, m_width / 2, m_height / 2, nullptr);

	MoveToEx(hdc, -m_width / 2, 0, nullptr);
	LineTo(hdc, m_width / 2.0, 0);
	MoveToEx(hdc, 0, -m_height / 2, nullptr);
	LineTo(hdc, 0, m_height / 2);

	COLORREF ori_color = SetTextColor(hdc, RGB(128, 128, 128));
	TCHAR buf[512];
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	long cx = tm.tmAveCharWidth;
	long cy = tm.tmExternalLeading + tm.tmHeight;
	TextOut(hdc, -m_width/2+cx, m_height/2-cy, buf, wsprintf(buf, TEXT("Time Quantum = %d ms"), my_config.time_quantum()));
	TextOut(hdc, -m_width / 2 + cx, m_height / 2 - 2 * cy, buf, wsprintf(buf, TEXT("Time Delta = %d ms  Left(-) / Right(+)"), my_config.time_delta()));
	long tmp = my_clock.total_msec();
	TextOut(hdc, -m_width / 2 + cx, m_height / 2 - 3 * cy, buf, wsprintf(buf, TEXT("Time elapsed = %d.%d ms"), tmp / 1000, tmp % 1000));
	SetTextColor(hdc, ori_color);

	m_vehicle->render(hdc);
}
