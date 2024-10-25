#include <stdio.h>
#include <stdlib.h>

#define countof(_arr) (sizeof(_arr)/sizeof(*_arr))
#define max(_x, _y) ((_x > _y) ? (_x) : (_y))
#define min(_x, _y) ((_x < _y) ? (_x) : (_y))

typedef struct Range {
	int start;
	int end;
} Range;

typedef struct SegmentNode {
	Range range;
	int max;
} SegmentNode;

int segmentnode_left(int node_index) {
	return node_index * 2 + 1;
}

int segmentnode_right(int node_index) {
	return node_index * 2 + 2;
}

int segmentnode_parent(int node_index) {
	return node_index / 2;
}

void segmenttree_build_helper(
	int array[],
	Range current_range,
	SegmentNode nodes[],
	int nodes_length,
	int current_node
) {
	nodes[current_node].range = current_range;

	if (current_range.start == current_range.end) {
		nodes[current_node].max = array[current_range.start];
		return;
	}

	int left_node = segmentnode_left(current_node);
	int right_node = segmentnode_right(current_node);
	int mid_point = (current_range.start + current_range.end) / 2;

	segmenttree_build_helper(
		array, (Range){ current_range.start, mid_point }, nodes, nodes_length, left_node
	);
	segmenttree_build_helper(
		array, (Range){ mid_point + 1, current_range.end }, nodes, nodes_length, right_node
	);

	nodes[current_node].max = max(nodes[left_node].max, nodes[right_node].max);
}

void segmenttree_build(int array[], int array_length, SegmentNode nodes[], int nodes_length) {
	segmenttree_build_helper(array, (Range){ 0, array_length - 1 }, nodes, nodes_length, 0);
}

int interval_max_helper(SegmentNode segment_tree[], Range range, int current_node) {
	const Range* current_range = &segment_tree[current_node].range;

	if (
		(current_range->start == current_range->end) ||
		((current_range->start == range.start) && (current_range->end == range.end))
	) {
		return segment_tree[current_node].max;
	}

	int left_node = segmentnode_left(current_node);
	int right_node = segmentnode_right(current_node);
	int mid_point = (current_range->start + current_range->end) / 2;

	if (mid_point >= range.end) {
		return interval_max_helper(segment_tree, range, left_node);
	}
	if (mid_point < range.start) {
		return interval_max_helper(segment_tree, range, right_node);
	}

	Range next_left_range = (Range){
		.start = range.start,
		.end = mid_point,
	};
	Range next_right_range = (Range){
		.start = mid_point + 1,
		.end = range.end,
	};

	int left_max = interval_max_helper(segment_tree, next_left_range, left_node);
	int right_max = interval_max_helper(segment_tree, next_right_range, right_node);
	return max(left_max, right_max);
}

void interval_max(SegmentNode segment_tree[], Range ranges[], int ranges_count, int maximums[]) {
	for (int i = 0; i < ranges_count; i++) {
		maximums[i] = interval_max_helper(segment_tree, ranges[i], 0);
	}
}

void parse_inputs(
	int array[],
	int array_capacity,
	int* array_length,
	Range ranges[],
	int ranges_capacity,
	int* ranges_length
) {
	*array_length = 0;
	*ranges_length = 0;

	char* numbers_line = NULL;
	size_t numbers_line_capacity;
	getline(&numbers_line, &numbers_line_capacity, stdin);

	const char* string = numbers_line;
	while (*array_length < array_capacity && string[0] != '\n' && string[0] != '\0') {
		int characters_read;
		sscanf(string, "%d%n", &array[*array_length], &characters_read);

		*array_length += 1;
		string += characters_read + 1;
	}

	char* ranges_line = NULL;
	size_t ranges_line_capacity;
	getline(&ranges_line, &ranges_line_capacity, stdin);

	string = ranges_line;
	while (*ranges_length < ranges_capacity && string[0] != '\n' && string[0] != '\0') {
		int characters_read;
		sscanf(string, "%d%d%n", &ranges[*ranges_length].start, &ranges[*ranges_length].end, &characters_read);

		*ranges_length += 1;
		string += characters_read + 1;
	}

	free(numbers_line);
	free(ranges_line);
}

int main() {
	int array[4096];
	int array_length;

	int maximums[1024];
	Range ranges[1024];
	int ranges_length;

	SegmentNode nodes[1024];

	parse_inputs(
		array,
		countof(array),
		&array_length,
		ranges,
		countof(array),
		&ranges_length
	);

	segmenttree_build(array, array_length, nodes, countof(nodes));
	interval_max(nodes, ranges, ranges_length, maximums);

	for (int i = 0; i < ranges_length; i++) {
		printf("%d ", maximums[i]);
	}
	printf("\n");

	return 0;
}
