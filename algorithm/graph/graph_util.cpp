/* 
* @Author: yancz1989
* @Date:   2016-01-08 15:51:19
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-18 15:54:45
*/
graph::graph(){
	mat.clear();
	edges.clear();
}

graph::~graph(){
	mat.clear();
	edges.clear();
}

void graph::print_graph(){
	if(type == linkedlists){
		for(int i = 0; i < nnodes; ++i){
			printf("%d ", i);
			for(list<edge>::iterator it = edges[i].begin(); it != edges[i].end(); ++it)
				printf("%d %f ", it->end, it->weight);
			END_LINE;
		}
	} else if (type == matrices){
		for(int i = 0; i < nnodes; ++i){
			for(int j = 0; j < nnodes; ++j)
				printf("%f ", mat[i][j]);
			END_LINE;
		}
	}
}

bool graph::build_graph(int _nnodes, int _nedges, std::list<edge> _edges, graph_type _type){
	type = _type;
	nnodes = _nnodes;
	nedges = _nedges;
	if(type == matrices){
		list<edge>::iterator it;
		mat.resize(nnodes);
		for(int i = 0; i < nnodes; ++i)
			mat[i].resize(nnodes, DOUBLE_INF);
		for(it = _edges.begin(); it != _edges.end(); ++it){
			CHECK_NODE(it->start, nnodes);
			CHECK_NODE(it->end, nnodes);
			mat[it->start][it->end] = it->weight;
		}
	} else if(type == linkedlists){
		list<edge>::iterator it;
		edges.resize(nnodes);
		for(it = _edges.begin(); it != _edges.end(); ++it){
			CHECK_NODE(it->start, nnodes);
			CHECK_NODE(it->end, nnodes);
			edges[it->start].push_back((*it));
		}
	}
	return true;
}

graph::graph(int _nnodes, int _nedges, list<edge> _edges, graph_type _type){
	build_graph(_nnodes, _nedges, _edges, _type);
}

void graph::switch_type(){
	if(type == matrices){
		type = linkedlists;
		for(int i = 0; i < nnodes; ++i)
			for(int j = 0; j < nnodes; ++j)
				if(mat[i][j] != 0){
					edge e(i, j, mat[i][j]);
					edges[i].push_back(e);
					++nedges;
				}
		mat.clear();
	} else if (type == linkedlists){
		type = matrices;
		mat.resize(nnodes);
		for(int i = 0; i < nnodes; ++i)
			mat[i].resize(nnodes, DOUBLE_INF);
		for(int i = 0; i < nedges; ++i){
			for(list<edge>::iterator it = edges[i].begin(); it != edges[i].end(); ++it)
				mat[it->start][it->end] = it->weight;
		}
		edges.clear();
	}
}

