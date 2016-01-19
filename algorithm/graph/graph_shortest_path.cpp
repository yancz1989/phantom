/* 
* @Author: yancz1989
* @Date:   2016-01-18 15:54:59
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-19 11:40:14
*/

#include "graph.h"

vector<int> pair_shortest_path_solver::path(int start, int end){
	vector<int> p;
	int k = end;
	while(k != start){
		p.push_back(k);
		k = predecessor[start][k];
	}
	return p;
}

vector<int> single_source_shortest_path_solver::path(int start, int end){
	vector<int> p;
	int k = end;
	while(k != start){
		p.push_back(k);
		k = predecessor[k];
	}
	return p;
}

double pair_shortest_path_solver::query(int start, int end){
	CHECK_NODE(start, dist.size());
	CHECK_NODE(end, dist.size());
	return dist[start][end];
};

double single_source_shortest_path_solver::query(int dest){
	return dist[dest];
}

void dijkstra_solver::solve(graph* pg, int start){
	CHECK_NODE(start, pg->nnodes);
	dist.resize(pg->nnodes, DOUBLE_INF);
	dist[start] = 0;
	predecessor.resize(pg->nnodes, -1);
	priority_queue<meta> q;
	q.push(meta(start, 0));
	meta tmp;
		
	if(pg->type == matrices){
		while(!q.empty()){
			tmp = q.top();
			q.pop();
			for(int i = 0; i < pg->nnodes; ++i){
				if(dist[i] > dist[tmp.end] + pg->mat[tmp.end][i]){
					dist[i] = dist[tmp.end] + pg->mat[tmp.end][i];
					predecessor[i] = tmp.end;
					q.push(meta(i, dist[i]));
				}
			}
		}
	} else if (pg->type == linkedlists){
		vector<list<edge> >& edges = pg->edges;
		while(!q.empty()){
			tmp = q.top();
			q.pop();
			for(list<edge>::iterator it=edges[tmp.end].begin(); it!=edges[tmp.end].end(); ++it){
				if(dist[it->end] > dist[tmp.end] + it->weight){
					dist[it->end] = dist[tmp.end] + it->weight;
					predecessor[it->end] = tmp.end;
					q.push(meta(it->end, dist[it->end]));
				}
			}
		}
	}
}

void SPFA_solver::solve(graph* pg, int start){
	CHECK_NODE(start, pg->nnodes);
	queue<int> q;
	dist.resize(pg->nnodes, DOUBLE_INF);
	dist[start] = 0;
	predecessor.resize(pg->nnodes, -1);

	q.push(start);
	if(pg->type == matrices){
		vector<vector<double> >& mat = pg->mat;
		while(!q.empty()){
			int k = q.front();
			q.pop();
			for(int i = 0; i < pg->nnodes; ++i){
				if(dist[i] > dist[k] + mat[k][i]){
					dist[i] = dist[k] + mat[k][i];
					predecessor[i] = k;
					q.push(i);
				}
			}
		}
	} else if(pg->type == linkedlists){
		vector<list<edge> >& edges = pg->edges;
		while(!q.empty()){
			int k = q.front();
			q.pop();
			for(list<edge>::iterator it = edges[k].begin(); it != edges[k].end(); ++it){
				if(dist[it->end] > dist[k] + it->weight){
					dist[it->end] = dist[k] + it->weight;
					predecessor[it->end] = k;
					q.push(it->end);
				}
			}
		}
	}
}


void bellman_ford_solver::solve(graph* pg){
	edge e;
	dist.clear();
	dist.resize(pg->nnodes, vector<double>(pg->nnodes, DOUBLE_INF));
	predecessor.resize(pg->nnodes, vector<int>(pg->nnodes, -1));
	if(pg->type == matrices){
		for(int i = 0; i < pg->nnodes; ++i)
			for(int j = 0; j < pg->nnodes; ++j)
				dist[i][j] = pg->mat[i][j];
	} else if(pg->type == linkedlists){
		for(int i = 0; i < pg->nnodes; ++i)
			for(list<edge>::iterator it=pg->edges[i].begin(); it!=pg->edges[i].end(); ++it)
				dist[it->start][it->end] = it->weight;
	}

	for(int k = 0; k < pg->nnodes; ++k)
		for(int i = 0; i < pg->nnodes; ++i)
			for(int j = 0; j < pg->nnodes; ++j){
				if(dist[i][j] > dist[i][k] + dist[k][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
					predecessor[i][j] = k;
				}
			}
}
