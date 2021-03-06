/* 
* @Author: yancz1989
* @Date:   2016-01-19 17:37:39
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-01-20 09:32:47
*/

#include "../observer.h"

using namespace std;
using namespace phantom::design_pattern::observer;

struct news{
	char title[256];
	char content[1024];
};

class large_agency : public publisher<news>{
public:
	void notify(long long id, const news& data){
		subs.find(id)->second->update(data);
		printf("message sent to %lld\n", id);
	}
	void new_gen_distribute(){
		news nnews;
		strcpy(nnews.title, "Breaking News, War Start!\n");
		strcpy(nnews.content, "It's a joke, peace will stay the same.\n");
		notify_all(nnews);
	}
};


class small_agency : public subscriber<news> {
public:
	small_agency(const char* _name){ strcpy(name, _name); }
	void update(const news& data) {
		printf("%s recieved news %s, content : %s\n", name, data.title, data.content);
	}
private:
	char name[128];
};

int demo_observer(){
	large_agency xinhua_agency;
	small_agency A("Reuters"), B("United"), C("Globles");
	xinhua_agency.subscribe(&A);
	xinhua_agency.subscribe(&B);
	xinhua_agency.subscribe(&C);
	xinhua_agency.new_gen_distribute();
    return 0;
}