/* 
* @Author: yancz1989
* @Date:   2016-01-18 15:54:59
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-21 08:00:18
*/
#ifndef PHANTOM_GRAPH_SPATH_H
#define PHANTOM_GRAPH_SPATH_H

#include "pgraph.hpp"

namespace phantom{
namespace algorithm{
namespace graph{

template<typename E, typename W = int>
class SingleSourceSPSolver{
public:
  SingleSourceSPSolver() { };
  virtual void solve(Graph<E>* pg, int start) = 0;

  double query(int dest){
    return dist[dest];
  }

  vector<int> path(int start, int dest){
    vector<int> p;
    int k = end;
    while(k != start){
      p.push_back(k);
      k = predecessor[k];
    }
    return p;
  }

protected:
  vector<int> predecessor;
  vector<W> dist;
};


template<typename E, typename W = int>
class PairSPSolver{
public:
  PairSPSolver(){ }
  virtual void solve(Graph<E>* pg) = 0;
  vector<int> path(int start, int end){
    vector<int> p;
    int k = end;
    while(k != start){
      p.push_back(k);
      k = predecessor[start][k];
    }
    return p;
  }

  double query(int start, int end){
    check_node(start, dist.size());
    check_node(end, dist.size());
    return dist[start][end];
  };

protected:
  vector<vector<double> > dist;
  vector<vector<int> > predecessor;
};


template<typename E, typename W = int>
class BellmanFord : public PairSPSolver{
public:
  void solve(Graph<E> *gp){
    edge e;
    dist.clear();
    dist.resize(pg->nnodes, vector<double>(pg->nnodes, DOUBLE_INF));
    predecessor.resize(pg->nnodes, vector<int>(pg->nnodes, -1));
    for(int i = 0; i < pg->nnodes; ++i)
      for(list<edge>::iterator it=pg->edges[i].begin(); it!=pg->edges[i].end(); ++it)
        dist[it->start][it->end] = it->weight;

    for(int k = 0; k < pg->nnodes; ++k)
      for(int i = 0; i < pg->nnodes; ++i)
        for(int j = 0; j < pg->nnodes; ++j){
          if(dist[i][j] > dist[i][k] + dist[k][j]){
            dist[i][j] = dist[i][k] + dist[k][j];
            predecessor[i][j] = k;
          }
        }
  }
};

template<typename E, typename W = int>
class Dijkstra : public SingleSourceSPSolver{
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
  void solve(Graph<E>* pg, int start){
    check_node(start, pg->nnodes);
    dist.resize(pg->nnodes, DOUBLE_INF);
    dist[start] = 0;
    predecessor.resize(pg->nnodes, -1);
    priority_queue<meta> q;
    q.push(meta(start, 0));
    meta tmp;

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
};

template<typename E, typename W = int>
class SPFA : public SingleSourceSPSolver{
public:
  void solve(Graph<E>* pg, int start){
    check_node(start, pg->nnodes);
    queue<int> q;
    dist.resize(pg->nnodes, DOUBLE_INF);
    dist[start] = 0;
    predecessor.resize(pg->nnodes, -1);

    q.push(start);
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
};
}
}
}

#endif
