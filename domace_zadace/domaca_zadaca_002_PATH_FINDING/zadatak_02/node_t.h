#pragma once

typedef std::int32_t vertex_t;
typedef std::double_t weight_t;

struct node_t {
	node_t(vertex_t _target, weight_t _weight)
		: target{ _target }, weight{ _weight } {}
	vertex_t target;
	weight_t weight;
};