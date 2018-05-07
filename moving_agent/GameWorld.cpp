#include "stdafx.h"
#include "GameWorld.h"
#include "AppParam.h"
#include "MyGDI.h"
#include "MyRand.h"
#include "EntityFunctionTemplates.h"

GameWorld::GameWorld() {
	m_crosshair = (HBITMAP)LoadImage(nullptr, TEXT("..\\crosshair.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_hdcmem = CreateCompatibleDC(nullptr);
	m_old_crosshair = (HBITMAP)SelectObject(m_hdcmem, m_crosshair);
	m_target = Vector2D(800, 200);
	m_panic_dist = 100.0;

}


GameWorld::~GameWorld()
{
	SelectObject(m_hdcmem, m_old_crosshair);
	DeleteObject(m_crosshair);
	DeleteDC(m_hdcmem);
	for (auto iter = m_agents.begin(); iter != m_agents.end(); ++iter) {
		delete *iter;
	}
	for (auto iter = m_obstacles.begin(); iter != m_obstacles.end(); ++iter) {
		delete *iter;
	}
}


void GameWorld::update(double time_elapsed) {
	for (auto iter = m_agents.begin(); iter != m_agents.end(); ++iter) {
		(*iter)->update(time_elapsed);
	}
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

	for (auto iter = m_obstacles.begin(); iter != m_obstacles.end(); ++iter) (*iter)->render();

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

	my_gdi.draw_image(m_target, 57.0, 57.0, m_hdcmem);

	for (auto iter = m_agents.begin(); iter != m_agents.end(); ++iter) (*iter)->render();

}


void GameWorld::create_obstacle() {
	for (int i = 0; i < app_param.num_obstacles(); ++i) {
		int num_try = 10;
		while (num_try) {
			double radius = my_rand.drand(app_param.min_obstacle_radius(), app_param.max_obstacle_radius());
			double x = my_rand.drand(radius, m_width - radius);
			double y = my_rand.drand(radius, m_height - radius);
			Obstacle *ob = new Obstacle(Vector2D(x, y), radius);
			if (is_overlapped(ob, m_obstacles, app_param.min_dist_btn_obstacle())) {
				delete ob;
				--num_try;
			}
			else {
				m_obstacles.push_back(ob);
				break;
			}
		}
	}
}

void GameWorld::create_agent() {
	for (int i = 0; i < app_param.num_agents(); ++i) {
		Vehicle *ob = new Vehicle(this);
		ob->set_wander(true);
		ob->set_pos(Vector2D(my_rand.drand(0.0, m_width), my_rand.drand(0, m_height)));
		m_agents.push_back(ob);
	}
}