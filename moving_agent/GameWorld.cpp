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
	COLORREF ori_color = SetTextColor(hdc, RGB(128, 128, 128));
	TCHAR buf[512];
	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	long cx = tm.tmAveCharWidth;
	long cy = tm.tmExternalLeading + tm.tmHeight;
	TextOut(hdc, cx, cy, buf, wsprintf(buf, TEXT("Time Quantum = %d ms"), my_config.time_quantum()));
	TextOut(hdc, cx, 2 * cy, buf, wsprintf(buf, TEXT("Time Delta = %d ms  Left(-) / Right(+)"), my_config.time_delta()));
	long tmp = my_clock.total_msec();
	TextOut(hdc, cx, 3 * cy, buf, wsprintf(buf, TEXT("Time elapsed = %d.%d ms"), tmp / 1000, tmp % 1000));
	SetTextColor(hdc, ori_color);
	m_vehicle->render(hdc);
}
