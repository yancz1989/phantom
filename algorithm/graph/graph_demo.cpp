/* 
* @Author: yancz1989
* @Date:   2016-01-18 16:00:36
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-18 16:01:08
*/

#include "./phantom"

void demo_shortest_path(){
	int nnodes, nedges;
	list<edge> le;
	int t;
	while(scanf("%d%d", &nnodes, &nedges) && (nnodes != 0)){
		le.clear();
		for(int i = 0; i < nedges; ++i){
			edge e, er;
			scanf("%d %d %d", &e.start, &e.end, &t);
			e.weight = t;
			e.start = e.start - 1; e.end = e.end - 1;
			er.start = e.end; er.end = e.start; er.weight = e.weight;
			le.push_back(e);
			le.push_back(er);
		}
		graph g(nnodes, nedges, le, linkedlists);
		// SPFA_solver solver;
		// dijkstra_solver solver;
		bellman_ford_solver solver;
		// solver.solve(&g, 0);
		solver.solve(&g);
		printf("%d\n", (int)solver.query(0, nnodes - 1));
	}
}