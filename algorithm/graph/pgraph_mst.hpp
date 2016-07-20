/* 
* @Author: yancz1989
* @Date:   2016-01-19 09:03:15
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-24 21:43:49
*/

#ifndef PHANTOM_GRAPH_MST_H
#define PHANTOM_GRAPH_MST_H

#include "graph.h"

namespace phantom{
namespace algorithm{
namespace graph{
template<typename E, typename W = int>
class MinimumSpanningTree{
public:
	virtual void solve(Graph<E>* pg) = 0;
	list<edge>& get_MST_edges(){
		return MST_edges;
	}
protected:
	list<edge> MST_edges;
};

template<typename E, typename W = int>
class Kruskal : public MinimumSpanningTree{
public:
	void solve(Graph<E>* pg){
		vector<edge> edges(pg->nedges, edge());
		discrete_sets flags(pg->nnodes);
		int cnt = 0;
		for(int i = 0; i < pg->nnodes; ++i)
			for(list<edge>::iterator it = pg->edges[i].begin(); it != pg->edges[i].end(); ++it)
				edges[cnt ++] = edge(i, it->end, it->weight);
		sort(edges.begin(), edges.end(), edge::compare_by_weight);
		for(int i = 0; i < cnt; ++i)
			if(flags.find(edges[i].start) != flags.find(edges[i].end)){
				flags.union(edges[i].start, edges[i].end);
				MST_edges.push_back(edges[i]);
			}
	}
};

template<typename E, typename W = int>
class Prim : public MinimumSpanningTree{
public:
	struct meta{
		int node;
		double dist;
		int pre;
		bool operator < (const meta& m) const {
			return dist > m.value;
		}
		meta(int _n, double _d, int _p){ node = _n; dist = _d; pre = _p;}
		meta(){}
	}
	void solve(Graph<E>* pg){
		vector<double> dist(pg->nnodes, DOUBLE_INF);
		vector<bool> visit(pg->nnodes, 0);
		meta mt;
		int t;
		visit[0] = true;
		priority_queue<meta> q;
		q.push(meta(0, 0, 0));
		while(!q.empty()){
			mt = q.top(); t = mt.node;
			q.pop();
			MST_edges.push_back(edge(mt.pre, mt.node, mt.dist));
			if(!visit[t]){
				for(list<edge>::iterator it = pg->edges[t].begin(); it != pg->edges[t].end(); ++it)
					if(!visit[it->end] && dist[it->end] < it->weight){
						visit[it->end] = true;
						dist[it->end] = it->weight;
						q.push(meta(it->end, it->weight, t));
					}
			}
		}
	}
};

template<typename E>
class discrete_sets{
public:
	discrete_sets(int n_elements){
		label.resize(n_elements);
		for(int i = 0; i < n_elements; ++i)
			label[i] = i;
	}

	int find(int i){
		int r = i, t, tmp;
		while(label[r] != r)
			r = label[r];
		t = i;
		while(t != r){
			tmp = label[t];
			label[t] = r;
			t = tmp;
		}
		return r;
	}
	void union(int s1, int s2){
		int rs1 = find(s1), rs2 = find(s2);
		if(rs1 != rs2)
			label[s1] = rs2;
	}
private:
	vector<int> label;
}
}
}
}

#endif