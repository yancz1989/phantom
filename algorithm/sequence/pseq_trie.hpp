/*
* @Author: yancz1989
* @Date:   2016-07-17 09:10:57
* @Last Modified by:   yancz1989
* @Last Modified time: 2016-07-21 08:01:49
*/
#ifndef PHANTOM_SEQUENCE_TRIE_H
#define PHANTOM_SEQUENCE_TRIE_H


namespace phantom{
namespace algorithm
namespace sequence{

template<typename key_type>
class AhoCorasickAutomata{
public:
  const int S = 26;
  typedef struct ACTrieNode{
    ACTrieNode* next[S];
    key_type val;
    uint32 idx;
    int state;
    ACTrieNode* fail;
    ACTrieNode(key_type v){
      memset(next, 0, sizeof(next));
      fail = NULL;
      state = -1;
      idx = total ++;
      val = v;
    }
  } Node;

  AhoCorasickAutomata() : low('a') {
    root = new Node(key_type(-1));
  }

  ~AhoCorasickAutomata(){
    destroy(root);
  }

  void clear(){
    destroy(root);
    root = new Node(key_type(-1));
  }

  void destroy(Node* t){
    if(t != NULL){
      for(int i = 0; i < S; ++i)
        destroy(t->next[i]);
      delete t;
    }
  }

  void more(key_type* _tmpl, int l){
    vector<key_type> tmpl(l);
    memcpy(&tmpl[0], _tmpl, l * sizeof(key_type));
    dict.push_back(tmpl);
    Node* t = root;
    for(int i = 0; i < l; ++i){
      if(t->next[tmpl[i] - low] == NULL)
        t->next[tmpl[i] - low] = new Node(tmpl[i] - low);
      t = t->next[tmpl[i] - low];
    }
    t->state = dict.size() - 1;
  }

  // return whether seq is in the dict, for naive trie usage.
  bool exists(const key_type* seq, int l){
    Node* t = root;
    bool exist = true;
    for(int i = 0; i < l; ++i){
      if(t->next[seq[i] - low] == NULL){
        exist = false;
        break;
      } else{
        t = t->next[seq[i] - low];
      }
    }
    return exist & (t->state != 0);
  }

  void build(){
    Node *x, *y, *v;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
      x = q.front();
      q.pop();
      for(int i = 0; i < S; ++i){
        y = x->next[i];
        if(y){
          if(x == root)
            y->fail = root;
          else{
            v = x->fail;
            while(v){
              if(v->next[i]){
                y->fail = v->next[i];
                break;
              }
              v = v->fail;
            }
            if(!v) y->fail = root;
          }
          q.push(y);
        }
      }
    }
  }

  vector<vector<int> > index(key_type* seq, int l){
    vector<vector<int> > idxs(dict.size());
    Node *v = root, *p;
    for(int i = 0; i < l; ++i){
      key_type val = seq[i] - low;
      while(!v->next[val] && v != root)
        v = v->fail;
      v = v->next[val] ? v->next[val] : root;
      p = v;
      while(p != root && p->state >= 0){
        idxs[p->state].push_back(i);
        p->state = -1;
        p = p->fail;
      }
    }
    return idxs;
  }

  vector<vector<key_type> > dicts(){
    return dict;
  }
protected:
  vector<vector<key_type> > dict;
  Node* root;
  key_type low;
};
}
}
}

#endif