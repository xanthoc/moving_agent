#pragma once

template <typename T, typename ConT>
bool is_overlapped(const T *ob, const ConT &con_ob, double min_dist) {
	bool overlapped = false;
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
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
		(*iter)->set_scale(Vector2D(1.0, 1.0));
		Vector2D to = (*iter)->pos() - ob->pos();
		double dist = to.length() - (*iter)->bounding_radius();
		if (dist < range) (*iter)->tag();
	}
}


