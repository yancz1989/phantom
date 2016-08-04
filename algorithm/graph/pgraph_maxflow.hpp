/* 
* @Author: yancz1989
* @Date:   2016-01-19 09:03:35
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-23 10:12:38
*/

#include "pgraph.hpp"

namespace phantom{
namespace algorithm{
namespace graph{

template<typename W = int>
struct Edge{
  int u, v, next;
  W w;
  Edge(){};
  Edge(const Edge& e) : u(e.u), v(e.v), w(e.w), next(e.next) { }
  Edge(int _u, int _v, W _w, int _next) : u(_u), v(_v), w(_w), next(_next) { }
};


template<typename W>
class Dinic{
public:
  void add(int u, int v, W w){
    edges.push_back(Edge<W>(u, v, w, V[u])); V[u] = nE++;
    edges.push_back(Edge<W>(v, u, 0, V[v])); V[v] = nE++;
  }

  void reset(int _nnodes){
    nV = _nnodes;
    nE = 0;
    edges.clear();
    V.resize(nV);
    memset(&V[0], -1, nV * sizeof(int));
  }

  W maxflow(int s, int t){
    const W inf = 0x3fffffff;
    W mf = 0; cur.resize(nV); dist.resize(nV);
    if(s == t) return inf;
    while(label(t, s)){
      memcpy(&cur[0], &V[0], nV * sizeof(int));
      mf += augment(s, t, inf);
    }
    return mf;
  }
private:
  bool label(int s, int t){
    int x, y;
    memset(&dist[0], 0x3f, nV * sizeof(int));
    for(; !q.empty(); q.pop());
    dist[s] = 0; q.push(s);
    while(!q.empty()){
      x = q.front(); q.pop();
      for(int i = V[x]; ~i; i = edges[i].next){
        if(edges[i ^ 1].w && dist[y = edges[i].v] > dist[x] + 1){
          dist[y] = dist[x] + 1; q.push(y);
          if(edges[i].v == t) return true;
        }
      }
    }
    return false;
  }

  W augment(int x, int t, const W last){
    W flow = last, d;
    int y;
    if(x == t) return last;
    for(int i = cur[x]; ~i; i = edges[i].next){
      if(edges[i].w && dist[y = edges[i].v] == dist[x] - 1) {
        cur[x] = i;
        d = augment(y, t, min(flow, edges[i].w));
        edges[i].w -= d; edges[i ^ 1].w += d; flow -= d;
        if(flow == 0) break;
      }
    }
    if(flow != 0) dist[x] = nV;
    return last - flow;
  }
  vector<Edge<W> > edges;
  vector<int> V;
  int nV;
  int nE;
  queue<int> q;
  vector<int> dist, cur;
};

template<typename W>
class SAPMaxFlow{
public:
  void add(int u, int v, W w){
    edges.push_back(Edge<W>(u, v, w, V[u])); V[u] = nE++;
    edges.push_back(Edge<W>(v, u, 0, V[v])); V[v] = nE++;
  }

  void reset(int _nnodes){
    nV = _nnodes;
    nE = 0;
    edges.clear();
    V.resize(nV); cur.resize(nV); pre.resize(nV);
    cnt.resize(nV); dist.resize(nV); his.resize(nV);
    memset(&V[0], -1, nV << 2);
  }

  W maxflow(int s, int t){
    const W inf = 0x3fffffff;
    W flow = inf, mf = 0;
    int x, y, i, m;
    bool tag;
    if (!label(t, s)) return 0;
    memcpy(&cur[0], &V[0], nV << 2);
    for(x = s; dist[s] < nV;){
      his[x] = flow; tag = false;
      for(i = cur[x]; ~i; i = edges[i].next){
        y = edges[i].v;
        if (edges[i].w && dist[y] == dist[x] - 1) {
          tag = true; pre[y] = cur[x] = i;
          flow = min(flow, edges[i].w); x = y;
          if (x == t) {
            for(mf += flow; x != s; x = edges[pre[x]].u)
              edges[pre[x]].w -= flow, edges[pre[x] ^ 1].w += flow;
            flow = inf;
          }
          break;
        }
      }
      if (!tag) {
        m = nV;
        for(i = V[x]; ~i; i = edges[i].next){
          y = edges[i].v;
          if (edges[i].w && dist[y] < m)
            m = dist[y], cur[x] = i;
        }
        if (!(--cnt[dist[x]])) break;
        ++cnt[dist[x] = m + 1];
        if (x != s)
          x = edges[pre[x]].u, flow = his[x];
      }
    }
    return mf;
  }
private:
  bool label(int s, int t){
    int x, y;
    memset(&dist[0], 0x3f, nV << 2);
    memset(&cnt[0], 0, nV << 2);
    for(; !q.empty(); q.pop());
    dist[s] = 0; ++cnt[0];
    for(q.push(s); !q.empty(); q.pop()){
      x = q.front();
      for(int i = V[x]; ~i; i = edges[i].next)
        if(edges[i ^ 1].w && dist[y = edges[i].v] > dist[x] + 1){
          dist[y] = dist[x] + 1; q.push(y); ++cnt[dist[y]];
        }
    }
    return dist[t] < nV;
  }

  vector<Edge<W> > edges;
  vector<int> V, dist, cur, pre, cnt;
  vector<W> his;
  int nV;
  int nE;
  queue<int> q;
};

template<typename W = int, typename C = int>
struct Edge{
  int u, v, next;
  W w;
  C c;
  Edge(){};
  Edge(const Edge& e) : u(e.u), v(e.v), w(e.w), c(e.c), next(e.next) { }
  Edge(int _u, int _v, W _w, C _c, int _next) : u(_u), v(_v), c(_c), w(_w), next(_next) { }
};

template<typename E = Edge<int, int>, typename W = int, typename C = int>
class MinCostMaxFlow{
public:
  void reset(int _nV){
    nV = _nV; clearQ();
    V.resize(nV); memset(&V[0], -1, sizeof(int) * nV);
    his.resize(nV); pre.resize(nV); dist.resize(nV); visit.resize(nV);
  }

  void add(int u, int v, W w, C c){
    edges.push_back(Edge<W>(u, v, w, c, V[u])); V[u] = nE++;
    edges.push_back(Edge<W>(v, u, 0, -c, V[v])); V[v] = nE++;
  }

  MinCostMaxFlow(int _nV = 0) { reset(_nV); }

  void solve(int src, int dst, C& cost, W& mf){
    const W inf = 0x7f7f7f7f;
    int i, x, y;
    mf = 0; cost = 0;
    while(true){
      memset(&dist[0], 0x7f, sizeof(int) * nV);
      memset(&visit[0], 0, sizeof(bool) * nV);
      dist[src] = 0; his[src] = inf; visit[src] = 1;
      for(q.push_back(src); !q.empty();){
        x = q.front(); q.pop_front(); visit[x] = 0;
        for(i = V[x]; ~i; i = edges[i].next){
          y = edges[i].v;
          if(edges[i].w && dist[y] > dist[x] + edges[i].c){
            dist[y] = dist[x] + edges[i].c;
            pre[y] = i; his[y] = min(his[x], edges[i].w);
            if (!visit[y]) {
              if(!q.empty() && dist[y] < dist[q.front()])
                q.push_front(y);
              else
                q.push_back(y);
              visit[y] = 1;
            }
          }
        }
      }
      if(dist[dst] >= inf) break;
      mf += his[dst]; cost += dist[dst] * his[dst];
      for(i = dst; i != src; i = edges[pre[i]].u)
        edges[pre[i]].w -= his[dst], edges[pre[i] ^ 1].w += his[dst];
    }
  }
// private:
  int nV, nE;
  void clearQ(){ for(; !q.empty(); q.pop_front()); }
  vector<E> edges;
  vector<int> V, pre, visit;
  vector<C> dist;
  vector<W> his;
  deque<int> q;
};

}
}
}