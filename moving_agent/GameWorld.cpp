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
	for (auto iter = m_walls.begin(); iter != m_walls.end(); ++iter) {
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

	for (auto iter = m_walls.begin(); iter != m_walls.end(); ++iter) (*iter)->render();

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

	for (auto iter = m_agents.begin(); iter != m_agents.end(); ++iter) {
		(*iter)->render();
		text_len = wsprintf(buf, TEXT("Agent pos = (%d, %d)"), static_cast<int>((*iter)->pos().m_x), static_cast<int>((*iter)->pos().m_y));
		my_gdi.draw_text_auto_pos(buf, text_len);
	}

}


void GameWorld::create_wall() {
	double offset = 5.0;
	Vector2D from, to;
	from = Vector2D(offset, offset);
	to = Vector2D(m_width - offset, offset);
	Wall *ob = new Wall(from, to);
	m_walls.push_back(ob);
	from = Vector2D(m_width - offset, offset);
	to = Vector2D(m_width - offset, m_height - offset);
	ob = new Wall(from, to);
	m_walls.push_back(ob);
	from = Vector2D(m_width - offset, m_height - offset);
	to = Vector2D(offset, m_height - offset);
	ob = new Wall(from, to);
	m_walls.push_back(ob);
	from = Vector2D(offset, m_height - offset);
	to = Vector2D(offset, offset);
	ob = new Wall(from, to);
	m_walls.push_back(ob);
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
	/*
	for (int i = 0; i < app_param.num_agents(); ++i) {
		Vehicle *ob = new Vehicle(this);
		//ob->set_wall_avoidance(true);
		//ob->set_obstacle_avoidance(true);
		//ob->set_wander(true);
		//ob->set_arrive(true);
		ob->set_path_following(true);
		ob->set_pos(Vector2D(my_rand.drand(m_width / 4, m_width * 3 / 4), my_rand.drand(m_height/4, m_height*3/4)));
		m_agents.push_back(ob);
	}
	*/
	Vehicle *ob = new Vehicle(this, Vehicle::RED);
	ob->set_seek(true);
	ob->set_max_speed(ob->max_speed()*0.8);
	ob->set_pos(Vector2D(my_rand.drand(m_width / 4, m_width * 3 / 4), my_rand.drand(m_height / 4, m_height * 3 / 4)));
	m_agents.push_back(ob);

	std::vector<Vector2D> offset = {
		Vector2D(-50, 50), Vector2D(-50, -50), Vector2D(-100, 0), Vector2D(-100, 100), Vector2D(-100, -100)
	};
	for (int i = 0; i < 5; ++i) {
		ob = new Vehicle(this);
		ob->set_offset_pursuit(true);
		ob->set_offset(offset[i]);
		ob->set_max_speed(ob->max_speed()*1.2);
		ob->set_pos(Vector2D(my_rand.drand(m_width / 4, m_width * 3 / 4), my_rand.drand(m_height / 4, m_height * 3 / 4)));
		m_agents.push_back(ob);
	}

}