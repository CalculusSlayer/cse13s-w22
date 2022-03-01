#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphsearch.h"

// dealing with sets of integers. We wrote these in class.
LLint *add_to_set(LLint *set, int val) {
  LLint *newfront = calloc(1, sizeof(LLint));
  newfront->val = val;
  newfront->next = set;

  return newfront;
}

void delete_set(LLint **set) {
	if (*set == NULL) {
		return;
	}

	if ((*set)->next == NULL) {
		free(*set);
		*set = NULL;
	}

	else {
		delete_set(&((*set)->next));
		free(*set);
		*set = NULL;
	}
}

void delete_LLPath(LLPath **q) {
	if (*q == NULL) {
		return;
	}

	if ((*q)->next == NULL) {
		free(*q);
		*q = NULL;
	}

	else {
		delete_LLPath(&((*q)->next));
		free(*q);
		*q = NULL;
	}
}
		
bool set_contains(LLint *set, int val) {
  if (set == NULL) {
    return false;
  } else if (set->val == val) {
    return true;
  } else {
    return set_contains(set->next, val);
  }
}



// Linked lists of paths. You'll need to implement these.

// Returns the new front of the queue, for a queue of Path structs.
// Usually this will be the old front of the queue, but if q is NULL, then it
// will allocate a new linked list node and return that.
LLPath *enqueue_path(LLPath *q, Path path) {
  // YOUR CODE HERE
	LLPath *new_path = (LLPath *) malloc(sizeof(LLPath));
	new_path->val = path;
	new_path->next = NULL;
	if (!q) {
		return new_path;
	}

	LLPath *current_path = q;
	while (current_path->next) {
		current_path = current_path->next;
	}

	current_path->next = new_path;

	return q;
}

LLPath *push_path(LLPath *q, Path path) {
	LLPath *new_path = (LLPath *) malloc(sizeof(LLPath));
	new_path->val = path;
	new_path->next = NULL;

	if (q) {
		LLPath *temp = q;
		new_path->next = temp;
	}

	return new_path;
}

bool dequeue_path(LLPath **q, Path *ret) {
  // YOUR CODE HERE
	if (!(*q)) {
		return false;
	}
	
	LLPath *temp = *q;
	*q = (*q)->next;
	
	*ret = temp->val;
	free(temp);
	temp = NULL;

  return true;
}

// We wrote these in class.
Graph *graph_create(int vertices) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  g->matrix = (int **)calloc(vertices, sizeof(int*));
  for (int i=0; i < vertices; i++) {
    g->matrix[i] = (int *)calloc(vertices, sizeof(int));
  }
  return g;
}

void graph_add_edge(Graph *g, int i, int j) {
  g->matrix[i][j] = 1;
}

bool graph_has_edge(Graph *g, int i, int j) {
  return g->matrix[i][j];
}

void graph_delete(Graph **g) {
	for (int i = 0; i < (*g)->vertices; ++i) {
		free((*g)->matrix[i]);
		(*g)->matrix[i] = NULL;
	}
	free((*g)->matrix);
	(*g)->matrix = NULL;
	free(*g);
	*g = NULL;
}

// Convenience method for you -- returns a new Path where you have added another
// vertex along the path.
Path path_extend(Path path, int new_vertex) {
  Path out;
  out.steps = path.steps;

  for (int i=0; i < path.steps; i++) {
    out.vertices_visited[i] = path.vertices_visited[i];
  }
  out.vertices_visited[path.steps] = new_vertex;
  out.steps += 1;
  return out;
}

// Print out a path nicely for the user.
void print_path(Path path) {
  if (path.steps == 0) {
    puts("(empty path)");
  }
  for (int i=0; i < path.steps; i++) {
    printf("%s%d",
        (i == 0) ? "" : " -> ",
        path.vertices_visited[i]);
  }
  puts("");
}

// Breadth-first search!
Path graph_find_path_bfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
	LLint *visited = NULL;
	LLPath *paths = NULL;
	
	Path initial_path = {1, {i}};
	//initial_path.steps = 1;
	//initial_path.vertices_visited[0] = i;

	paths = enqueue_path(paths, initial_path);

	while (paths) {
		Path current_path;
		dequeue_path(&paths, &current_path);

	int current_int = current_path.vertices_visited[current_path.steps - 1];
		if (current_int == j) {
			delete_set(&visited);
			delete_LLPath(&paths);
			return current_path;
		}
	
	visited = add_to_set(visited, current_int);
		
		for (int neighbor = 0; neighbor < g->vertices; neighbor++) {
			if (graph_has_edge(g, current_int, neighbor) && !set_contains(visited, neighbor)) {
				paths = enqueue_path(paths, path_extend(current_path, neighbor));
			}
		}
	}

	delete_set(&visited);
	delete_LLPath(&paths);
  Path empty = {0, {0}};
  return empty;

}


// Depth-first search!
Path graph_find_path_dfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
	LLint *visited = NULL;
	LLPath *paths = NULL;
	
	Path initial_path = {1, {i}};
	//initial_path.steps = 1;
	//initial_path.vertices_visited[0] = i;

	paths = push_path(paths, initial_path);

	while (paths) {
		Path current_path;
		dequeue_path(&paths, &current_path);

	int current_int = current_path.vertices_visited[current_path.steps - 1];
		if (current_int == j) {
			delete_set(&visited);
			delete_LLPath(&paths);
			return current_path;
		}
	
	visited = add_to_set(visited, current_int);
		
		for (int neighbor = 0; neighbor < g->vertices; neighbor++) {
		//for (int neighbor = g->vertices-1; neighbor >= 0; neighbor--) {
			if (graph_has_edge(g, current_int, neighbor) && !set_contains(visited, neighbor)) {
				paths = push_path(paths, path_extend(current_path, neighbor));
			}
		}
	}

	delete_set(&visited);
	delete_LLPath(&paths);
  Path empty = {0, {0}};
  return empty;
}

