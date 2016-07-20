/* 
* @Author: yancz1989
* @Date:   2016-01-19 16:50:19
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-20 09:31:10
*/

#ifndef DESIGN_PATTERN_OBSERVER_H
#define DESIGN_PATTERN_OBSERVER_H

#include "../phantom.h"

namespace phantom{
namespace design_pattern{
namespace observer{

template<class DATA>
class subscriber{
public:
	virtual void update(const DATA& data) = 0;
	long long get_id() { return id; };
private:
	long long id;
	DATA state;
};

template<class DATA>
class publisher{
public:
	publisher(){ count = 0;	}

	virtual void subscribe(subscriber<DATA>* sub){
		subs.insert(pair<long long, subscriber<DATA>*>(count++, sub));
	}

	virtual void notify_all(const DATA& ndata) {
		for(typename map<long long, subscriber<DATA>*>::iterator it = subs.begin();
				it != subs.end(); ++it)
			it->second->update(ndata);
	}
	virtual void notify(long long id, const DATA& ndata){
		subs.find(id)->second->update(ndata);
	}

	virtual void remove(subscriber<DATA>* sub){
		typename map<long long, subscriber<DATA>* >::iterator it = subs.find(sub->get_id());
		subs.erase(it);
	};
protected:
	map<long long, subscriber<DATA>*> subs;
	atomic<long long> count;
};

}
}
};

#endif