/* 
* @Author: yancz1989
* @Date:   2016-01-19 09:02:37
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-24 21:44:59
*/

namespace phantom{
namespace algorithm{
namespace graph{
template<typename E>
class Tarjan{
public:
	void solve(Graph<E>* pg);
private:
	vector<int> label;
}
}
}
}
