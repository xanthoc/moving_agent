#pragma once
#include <iostream>

template <typename T, typename ConT>
bool is_overlapped(const T *ob, const ConT &con_ob, double min_dist) {
	bool overlapped = false;
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
		//if (ob == *iter) continue;
		double dist_sq = (ob->pos().m_x - (*iter)->pos().m_x)*(ob->pos().m_x - (*iter)->pos().m_x) 
			+ (ob->pos().m_y - (*iter)->pos().m_y)*(ob->pos().m_y - (*iter)->pos().m_y);
		double dist_comp_sq = ob->bounding_radius() + (*iter)->bounding_radius() + min_dist;
		dist_comp_sq *= dist_comp_sq;
		if (dist_sq < dist_comp_sq) {
			overlapped = true;
			break;
		}
	}
	return overlapped;
}

template <typename T, typename ConT>
void tag_neighbor(const T *ob, const ConT &con_ob, double range) {
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
		(*iter)->untag();
		//if (ob == *iter) continue;
		//(*iter)->set_scale(Vector2D(1.0, 1.0));
		Vector2D to = (*iter)->pos() - ob->pos();
		double dist = to.length() - (*iter)->bounding_radius();
		if (dist < range) (*iter)->tag();
	}
}

// tag_neighbor_same shall be called when ob is in the container of con_ob
template <typename T, typename ConT>
void tag_neighbor_same(const T *ob, const ConT &con_ob, double range) {
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
		(*iter)->untag();
		if (ob == *iter) continue;
		//(*iter)->set_scale(Vector2D(1.0, 1.0));
		Vector2D to = (*iter)->pos() - ob->pos();
		double dist = to.length() - (*iter)->bounding_radius();
		if (dist < range) (*iter)->tag();
	}
}

// tag_neighbor_same_cell shall be called when ob is in the container of con_ob
template <typename T, typename ConT, typename ConU>
void tag_neighbor_same_cell(const T *ob, const ConT &con_ob, const ConU &con_cell, double range) {
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
		(*iter)->untag();
	}
	Vector2D tl = Vector2D(ob->pos().m_x - range, ob->pos().m_y - range);
	Vector2D br = Vector2D(ob->pos().m_x + range, ob->pos().m_y + range);
	int overlapped_cell_cnt = 0;
	for (typename ConU::const_iterator iter = con_cell.begin(); iter != con_cell.end(); ++iter) {
		if (!(*iter).is_empty() && (*iter).is_overlapped(tl, br)) {
		//if ((*iter).is_overlapped(tl, br)) {
			(*iter).tag_neighbor(ob, range);
			overlapped_cell_cnt++;
		}
	}
	if (overlapped_cell_cnt > 12) {
		overlapped_cell_cnt = 0;
	}
	std::cout << overlapped_cell_cnt << std::endl;
}



