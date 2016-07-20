/* 
* @Author: yancz1989
* @Date:   2016-01-08 15:48:11
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-24 21:59:03
*/

#ifndef PHANTOM_GRAPH_H
#define PHANTOM_GRAPH_H

#include "./phantom_algorithm.h"

#ifdef DEBUG
#define CHECK_NODE(i, n) assert(i < 0 || i >= n)
#else
#define CHECK_NODE(i, n)
#endif

namespace phantom{
namespace algorithm{
namespace graph{

template<typename W = int>
struct Edge{
	int u, v;
	W w;
	Edge(){};
	Edge(int _u, int _v, W _w){
		u = u, v = v, w = w;
	}
};

template<typename W = int, typename C = int>
struct CostEdge{
	int u, v;
	W w;
	C c;
	CostEdge(){}
	CostEdge(int _u, int _v, W _w, C _c){
		u = _u, v = _u, w = _w, c = _c;
	}
};

template<typename E>
struct Graph<E>{
	vector<list<E> > edges;
	int nnodes;
	int nedges;

	void build(int nnodes, int nedges, list<E> edges);
	Graph<E>(){
		edges.clear();
	}

	Graph<E>(int nnodes, int nedges, std::list<E> edges){
		build_graph(_nnodes, _nedges, _edges, _type);
	}

	~Graph<E>(){
		edges.clear();
	}

	bool build(int nnodes, int nedges, list<E> edges){
		type = _type;
		nnodes = _nnodes;
		nedges = _nedges;
		list<E>::iterator it;
		edges.resize(nnodes);
		for(it = _edges.begin(); it != _edges.end(); ++it){
			CHECK_NODE(it->start, nnodes);
			CHECK_NODE(it->end, nnodes);
			edges[it->start].push_back((*it));
		}
		return true;
	}

	void print_graph(){
		for(int i = 0; i < nnodes; ++i){
			printf("%d ", i);
			for(list<E>::iterator it = edges[i].begin(); it != edges[i].end(); ++it)
				printf("%d %f ", it->end, it->weight);
			END_LINE;
		}
	}

	void clear(){
		nnodes = 0;
		nedges = 0;
		mat.clear();
		edges.clear();
	}
};

}
}
};
#endif