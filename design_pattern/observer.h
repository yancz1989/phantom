/* 
* @Author: yancz1989
* @Date:   2016-01-19 16:50:19
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-19 19:53:25
*/

#ifndef DESIGN_PATTERN_OBSERVER_H
#define DESIGN_PATTERN_OBSERVER_H

#include "../phantom.h"

namespace phantom{
namespace design_pattern{
namespace observer{

class subscriber{
public:
	virtual void update(void* data) = 0;
	long long get_id() { return id; };
private:
	long long id;
};

class publisher{
public:
	publisher(){ count = 0;	}

	virtual void subscribe(subscriber* sub){
		subs.insert(pair<long long, subscriber*>(count++, sub));
	}

	virtual void notify_all(void* ndata) {
		for(map<long long, subscriber*>::iterator it = subs.begin(); it != subs.end(); ++it)
			it->second->update(ndata);
	}
	virtual void notify(long long id, void* ndata){
		subs.find(id)->second->update(ndata);
	}

	virtual void remove(subscriber* sub){
		map<long long, subscriber*>::iterator it = subs.find(sub->get_id());
		subs.erase(it);
	};
protected:
	map<long long, subscriber*> subs;
	atomic<long long> count;
};

}
}
};

#endif