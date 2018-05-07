#include "stdafx.h"
#include "GameWorld.h"
#include "AppParam.h"
#include "MyGDI.h"

GameWorld::GameWorld() {
	m_sheep = new Vehicle(this);
	//m_sheep->set_seek(true);
	//m_sheep->set_flee(true);
	m_sheep->set_wander(true);
	m_sheep->set_pos(Vector2D(100.0, 100.0));
	m_wolf = new Vehicle(this);
	//m_wolf->set_pursuit(true);
	m_wolf->set_wander(true);
	m_wolf->set_pos(Vector2D(500.0, 500.0));
	m_crosshair = (HBITMAP)LoadImage(nullptr, TEXT("..\\crosshair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hdcmem = CreateCompatibleDC(nullptr);
	m_old_crosshair = (HBITMAP)SelectObject(m_hdcmem, m_crosshair);
	m_target = Vector2D(800, 200);
	m_panic_dist = 100.0;

	double x_of_ob = 50.0;
	double r_of_ob = 20;
	for (int i = 0; i < app_param.num_obstacles(); ++i) {
		m_Obstacles.push_back(new Obstacle(Vector2D(x_of_ob, 1.01*x_of_ob), r_of_ob));
		x_of_ob += 2.0 * r_of_ob;
		r_of_ob += 10.0;
	}
}


GameWorld::~GameWorld()
{
	SelectObject(m_hdcmem, m_old_crosshair);
	DeleteObject(m_crosshair);
	DeleteDC(m_hdcmem);
	delete m_wolf;
	delete m_sheep;
	for (auto iter = m_Obstacles.begin(); iter != m_Obstacles.end(); ++iter) {
		delete *iter;
	}
}


void GameWorld::update(double time_elapsed) {
	m_sheep->update(time_elapsed);
	m_wolf->update(time_elapsed);
}

void GameWorld::render() {
	//SetMapMode(hdc, MM_ANISOTROPIC);
	//SetWindowExtEx(hdc, m_width / 2, m_height / 2, nullptr);
	//SetViewportExtEx(hdc, m_width / 2, -m_height / 2, nullptr);
	//SetViewportOrgEx(hdc, m_width / 2, m_height / 2, nullptr);

	/*
	m_sheep->render(hdc);
	HPEN red_pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN old_pen = (HPEN)SelectObject(hdc, red_pen);
	m_wolf->render(hdc);
	SelectObject(hdc, old_pen);
	DeleteObject(red_pen);
	*/
	my_gdi.draw_axes(m_width, m_height);

	for (auto iter = m_Obstacles.begin(); iter != m_Obstacles.end(); ++iter) (*iter)->render();

	my_gdi.reset_text_auto_pos();
	TCHAR buf[512];
	int text_len;
	text_len = wsprintf(buf, TEXT("Time Quantum = %d ms"), my_config.time_quantum());
	my_gdi.draw_text_auto_pos(buf, text_len);
	text_len = wsprintf(buf, TEXT("Time Delta = %d ms  Left(-) / Right(+)"), my_config.time_delta());
	my_gdi.draw_text_auto_pos(buf, text_len);
	text_len = wsprintf(buf, TEXT("Panic dist = %d pts  Down(-) / Up(+)"), (int)panic_dist());
	my_gdi.draw_text_auto_pos(buf, text_len);
	long tmp = my_clock.total_msec();
	text_len = wsprintf(buf, TEXT("Time elapsed = %d.%d s"), tmp / 1000, tmp % 1000);
	my_gdi.draw_text_auto_pos(buf, text_len);
	text_len = wsprintf(buf, TEXT("Position of the wolf is (%d, %d)"), (int)(m_wolf->pos().x()), (int)(m_wolf->pos().y()));
	my_gdi.draw_text_auto_pos(buf, text_len);
	text_len = wsprintf(buf, TEXT("Position of the sheep is (%d, %d)"), (int)(m_sheep->pos().x()), (int)(m_sheep->pos().y()));
	my_gdi.draw_text_auto_pos(buf, text_len);

	my_gdi.draw_image(m_target, 57.0, 57.0, m_hdcmem);
	m_sheep->render();
	m_wolf->render();
}
