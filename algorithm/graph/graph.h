/* 
* @Author: yancz1989
* @Date:   2016-01-08 15:48:11
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-18 15:57:09
*/

#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H

#include "./phantom_algorithm.h"

#ifdef DEBUG
#define CHECK_NODE(i, n) assert(i < 0 || i >= n)
#else
#define CHECK_NODE(i, n)
#endif

namespace phantom{
namespace algorithm{
namespace graph{

struct edge{
	int start, end;
	double weight;
	double cost;
	edge(int _start, int _end, double _weight, double _cost = 0){
		start = _start;
		end = _end;
		weight = _weight;
		cost = _cost;
	}
	edge(){};
};

class graph;

class single_source_shortest_path_solver{
public:
	single_source_shortest_path_solver(){
	};
	virtual void solve(graph* pg, int start) = 0;
	double query(int dest);
	vector<int> path(int start, int dest);
protected:
	vector<int> predecessor;
	vector<double> dist;
};


class pair_shortest_path_solver{
public:
	pair_shortest_path_solver(){
	}
	virtual void solve(graph* pg) = 0;
	vector<int> path(int start, int end);
	double query(int start, int end);
protected:
	vector<vector<double> > dist;
	vector<vector<int> > predecessor;
};

enum graph_type{
	matrices,
	linkedlists
};

class bellman_ford_solver : public pair_shortest_path_solver{
public:
	void solve(graph *gp);
};


class dijkstra_solver : public single_source_shortest_path_solver{
public:
	struct meta{
		int end;
		double value;
		bool operator < (const meta& m) const{
			return value > m.value;
		};
		meta(int _end, int _value){
			end = _end;
			value = _value;
		};
		meta(){};
	};
	void solve(graph* pg, int start);
};

class SPFA_solver : public single_source_shortest_path_solver{
public:
	void solve(graph* pg, int start);
};


class graph{
public:
	graph();
	graph(int nnodes, int nedges, std::list<edge> edges, graph_type type);
	~graph();
	bool build_graph(int nnodes, int nedges, std::list<edge> edges, graph_type type);
	void switch_type();
	friend void bellman_ford_solver::solve(graph *pg);
	friend void dijkstra_solver::solve(graph *pg, int start);
	friend void SPFA_solver::solve(graph *pg, int start);
	void print_graph();
private:
	graph_type type;
	vector<list<edge> > edges;
	vector<vector<double> > mat;
	int nnodes;
	int nedges;
};

}
}
}
#endif