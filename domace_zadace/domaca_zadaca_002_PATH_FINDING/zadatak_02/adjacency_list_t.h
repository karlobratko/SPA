#pragma once

#include <vector>
#include <algorithm>

#include "node_t.h"

const weight_t max_weight = std::numeric_limits<weight_t>::infinity();

class adjacency_list_t {
public:
	typedef std::vector<node_t> relations_t;

	adjacency_list_t(const std::int32_t& col, const std::int32_t& row) :
		col_{ col },
		row_{ row },
		list_{ col * row } {
	}

	std::int32_t size() const {
		return list_.size();
	}

	relations_t& at(vertex_t target) {
		return list_.at(target);
	}

	const relations_t& at(vertex_t target) const {
		return list_.at(target);
	}

	void init_relations(weight_t init_weight = default_init_weight) {
		for (std::size_t target{ 0 }; target < list_.size(); ++target) {
			for (vertex_t offset : { -1, 1 }) {
				if (target % col_ == 0) {
					if (offset == 1)
						push_back(target, target + offset, init_weight);
				}
				else if (target % col_ == col_ - 1) {
					if (offset == -1)
						push_back(target, target + offset, init_weight);
				}
				else {
					if ((target + offset) >= 0 && (target + offset) < list_.size())
						push_back(target, target + offset, init_weight);
				}

				if ((offset * col_) + target >= 0 && (offset * col_) + target < list_.size())
					push_back(target, offset * col_ + target, init_weight);
			}
		}
	}

	void dislocate_node(const std::int32_t& x, const std::int32_t& y) {
		dislocate_node(((y - 1) * col_) + (x - 1));
	}

	void dislocate_node(vertex_t target) {
		std::for_each(std::begin(list_), std::end(list_),
			[&](relations_t& nodes) {
				std::for_each(std::begin(nodes), std::end(nodes),
					[&](node_t& node) {
						if (node.target == target)
							node.weight = max_weight;
					}
				);
			}
		);
	}

private:

	void push_back(std::int32_t i, vertex_t target, weight_t weight) {
		list_.at(i).push_back(node_t{ target, weight });
	};

	static constexpr weight_t default_init_weight = 1;

	std::vector<relations_t> list_;
	std::int32_t col_;
	std::int32_t row_;

};