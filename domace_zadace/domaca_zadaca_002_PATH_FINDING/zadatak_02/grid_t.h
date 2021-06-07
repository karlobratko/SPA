#pragma once

#include <set>
#include <utility>
#include "adjacency_list_t.h"
#include "matrix_t.h"
#include "vector2i_t.h"

class grid_t {
public:
	typedef unsigned char uchar_t;
	grid_t(std::int32_t col, std::int32_t row) :
		col_{ col },
		row_{ row },
		list_{ col, row },
		matrix_{ col, row } {
	}

	void init_grid(const uchar_t c = default_grid_char) {
		settings.grid_char = c;
		matrix_.fill(c);
		list_.init_relations();
	}

	void make_obstacle(const vector2i_t& loc, const uchar_t c = default_obstacle_char) {
		list_.dislocate_node(loc.x, loc.y);
		matrix_.at(loc.x, loc.y) = c;
	}

	void set_src(const vector2i_t& loc, const uchar_t c = default_src_char) {
		settings.src_char = c;
		src_ = loc;
		matrix_.at(loc.x, loc.y) = c;
	}

	void set_dst(const vector2i_t& loc, const uchar_t c = default_dst_char) {
		settings.dst_char = c;
		dst_ = loc;
		matrix_.at(loc.x, loc.y) = c;
	}

	std::vector<vector2i_t> calculate_path() {
		std::int32_t src = (src_.y - 1) * col_ + (src_.x - 1);
		std::int32_t dst = (dst_.y - 1) * col_ + (dst_.x - 1);
		int n = list_.size();

		std::vector<weight_t> min_distance(n, max_weight);
		min_distance.at(src) = 0;

		std::vector<vertex_t> previous(n, -1);

		std::set<std::pair<weight_t, vertex_t>> vertex_queue;
		vertex_queue.insert(std::make_pair(min_distance.at(src), src));

		while (!vertex_queue.empty()) {
			weight_t dist = vertex_queue.begin()->first;
			vertex_t cur = vertex_queue.begin()->second;
			vertex_queue.erase(vertex_queue.begin());

			const std::vector<node_t>& nodes = list_.at(cur);

			for (const node_t& node : nodes) {
				vertex_t next = node.target;
				weight_t weight = node.weight;

				weight_t distance_through_cur = dist + weight;
				if (distance_through_cur < min_distance.at(next)) {
					vertex_queue.erase(std::make_pair(min_distance.at(next), next));

					min_distance.at(next) = distance_through_cur;
					previous.at(next) = cur;
					vertex_queue.insert(std::make_pair(min_distance.at(next), next));
				}
			}
		}

		std::vector<vector2i_t> path{};
		for (; dst != -1; dst = previous.at(dst)) {
			path.push_back(vector2i_t{ dst % col_, dst / col_ });
		}
		std::reverse(std::begin(path), std::end(path));
		return path;
	}

	void update(const vector2i_t& loc, uchar_t c) {
		matrix_.at(loc.x + 1, loc.y + 1) = c;
	}

	void draw(std::ostream& os) {
		os << matrix_;
	}

private:
	static constexpr uchar_t default_grid_char = 250;
	static constexpr uchar_t default_obstacle_char = 254;
	static constexpr uchar_t default_src_char = 254;
	static constexpr uchar_t default_dst_char = 32;

	adjacency_list_t list_;
	matrix_t<uchar_t> matrix_;

	std::int32_t col_;
	std::int32_t row_;

	vector2i_t src_{};
	vector2i_t temp_{};
	vector2i_t dst_{};

	struct settings_t {
		uchar_t grid_char;
		uchar_t src_char;
		uchar_t dst_char;
	} settings{};

};