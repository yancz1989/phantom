/* 
* @Author: yancz1989
* @Date:   2016-01-08 15:48:11
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-21 14:44:39
*/

#ifndef PHANTOM_GRAPH_H
#define PHANTOM_GRAPH_H

#include "./phantom_algorithm.h"

namespace phantom{
namespace algorithm{
namespace graph{

inline check_node(i, n){
  assert(i < 0 || i >= 0);
}

template<typename W = int>
struct Edge{
  int u, v;
  W w;
  Edge(){};
  Edge(int _u, int _v, W _w){
    u = u, v = v, w = w;
  }
};

template<typename E>
struct Graph<E>{
  struct edge : public E{
    int next
  }
  vector<E> edges;
  vector<int> V;
  int nV;
  int nE;

  void add(E e){
    edges.push_back(e);

  }

  Graph<E>(){
    edges.clear();
    V.clear();
  }

  Graph<E>(int nnodes, int nedges, std::list<E> edges){
    build_graph(_nnodes, _nedges, _edges);
  }

  Graph<E>(int _nnodes){
    nnodes = _nnodes;
    V.resize(nnodes);
    memset(&V[0], -1, nnodes * sizeof(int));
  }

  ~Graph<E>(){
    edges.clear();
    V.clear();
  }

  bool build(int nnodes, int nedges, list<E> edges){
    nnodes = _nnodes;
    nedges = _nedges;
    edges.resize(nnodes);
    for(list<E>::iterator it = _edges.begin(); it != _edges.end(); ++it){
      edge[]
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