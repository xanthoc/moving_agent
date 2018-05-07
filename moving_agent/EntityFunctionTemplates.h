#pragma once

template <typename T, typename ConT>
bool is_overlapped(const T *ob, const ConT &con_ob, double min_dist) {
	bool overlapped = false;
	for (typename ConT::const_iterator iter = con_ob.begin(); iter != con_ob.end(); ++iter) {
		double dist_sq = (ob->pos().x() - (*iter)->pos().x())*(ob->pos().x() - (*iter)->pos().x()) 
			+ (ob->pos().y() - (*iter)->pos().y())*(ob->pos().y() - (*iter)->pos().y());
		double dist_comp_sq = ob->bounding_radius() + (*iter)->bounding_radius() + min_dist;
		dist_comp_sq *= dist_comp_sq;
		if (dist_sq < dist_comp_sq) {
			overlapped = true;
			break;
		}
	}
	return overlapped;
}


