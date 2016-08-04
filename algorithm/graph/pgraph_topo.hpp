/* 
* @Author: yancz1989
* @Date:   2016-01-19 09:02:53
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-21 08:00:28
*/

#ifndef PHANTOM_GRAPH_TOPO_H
#define PHANTOM_GRAPH_TOPO_H

#include "pgraph.hpp"

namespace phantom{
namespace algorithm{
namespace graph{

template<typename E>
class TopologySort{
public:
  bool solve(Graph<E>* pg, vector<int>& sorted){
    vector<list<edge> >& edges = pg->edges;
    queue<int> q;
    vector<int> degree(pg->nnodes, 0);
    int cnt = 0, cur;

    sorted.resize(pg->nnodes, -1);
    for(int i = 0; i < pg->nnodes; ++i)
      for(list<edge>::iterator it = edges[i].begin(); it != edges[i].end(); ++it)
        ++degree[it->end];
    for(int i = 0; i < pg->nnodes; ++i){
      if(degree[i] == 0)
        q.push(i);
    }
    while(!q.empty()){
      cur = q.front();
      sorted[cnt++] = cur;
      q.pop();
      for(list<edge>::iterator it = edges[cur].begin(); it != edges[cur].end(); ++it){
        --degree[it->end];
        if(degree[it->end] == 0){
          q.push(it->end);
        }
      }
    }
    if(cnt < pg->nnodes)
      return false;
    else
      return true;
  }
};
}
}
}
#endif