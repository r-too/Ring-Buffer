#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
using namespace std;

#define FORWARD   1
#define  REWIND   0

class Node {
  public:
  int data;
  Node *prev, *next;
};

class RList {
  void rdcopy(const RList& other);
  public:
  string name;
  Node head, tail;
  RList(string argname) {
    head.next = head.prev = &tail;
    tail.next = tail.prev = &head;
    head.data = tail.data = 0;
    name = argname;
  };
  ~RList();
  void radd(int ldata);
  void rpop_h(int ldata, Node *pnode);
  void rpop_t(int ldata, Node *pnode);
  void rpush_h(int ldata, Node *pnode);
  void rpush_t(int ldata, Node *pnode);
  void rinsert_at(int ldata, Node *pnode);
  void rmerge(int ldata, Node *pnode);
  void rsort(Node *pnode);
  void rsplice();
  void rextract(int ldata, Node *pnode);
  void rdel(int ldata);
  void rprint(bool dir);
  void rreverse(Node *pnode);
  void rshift_h(int ldata, Node *pnode);
  void rshift_t(int ldata, Node *head_node);
  void rresize(int num, Node *head_node);
  void runique(Node *head_node);
  RList(const RList& other);
  RList& operator=(const RList& other);
};

void RList::rdcopy(const RList& other) {
  Node *scurr = other.tail.next;
  bool head_copied = false;

  while(scurr) {
    if (scurr == &other.head && head_copied) {
      return;
    } else if (scurr == &other.head && !head_copied) {
      head_copied = true, this->radd(scurr->data), scurr = scurr->next;
    } else {
      this->radd(scurr->data), scurr = scurr->next;
    }
  }
}

RList::RList(const RList& other) {
  rdcopy(other);
}

RList& RList::operator=(const RList& other) {
  if (this == &other) return *this;
  rdcopy(other);
  return *this;
}

RList::~RList() {
  Node *curr = head.next, *tmp;
  while(curr->next && (curr != &tail))
    tmp = curr, curr = curr->next, delete tmp;
  cout << "[FREE] (" << name << ") elements" << endl;
}

void RList::rprint(bool dir) {
  if (dir == FORWARD) {
    Node *tmp = &head;
    cout << "[FORWARD] (" << name << ") ";
    while (tmp) {
      cout << tmp->data << " ";
      if (tmp->data == tail.data) {
        cout << endl;
        return;
      }
      tmp = tmp->next;
    }
  } else if (dir == REWIND) {
    Node *tmp = &tail;
    cout << "[REVERSE] (" << name << ") ";
    while (tmp) {
      cout << tmp->data << " ";
      if (tmp->data == head.data) {
        cout << endl;
        return;
      }
      tmp = tmp->prev;
    }
  }
}

void RList::radd(int ldata) {
  if (head.data == 0) {
    head.data = ldata;
    return;
  }
  if (tail.data == 0) {
    tail.data = ldata;
    return;
  }
  Node *nnode = new Node();
  nnode->data = tail.data;
  tail.data = ldata;
  (tail.prev)->next = nnode;
  nnode->prev = tail.prev;
  nnode->next = &tail;
  tail.prev = nnode;
}

class RStack: public RList {
  ~RStack();
};

class RQueue: public RList {
  ~RQueue();
};

class RBuffer: public RList {
  ~RBuffer();
};

void RList::rdel(int ldata) {
  Node *tmp = &head;

  while(tmp) {
    if(tmp->data == ldata) {
      if(tmp != &head && tmp != &tail) {
      } else if (tmp == &head) {
        Node *link = head.next;
        head.data = head.next->data;
        head.next->prev = &head;
        head.next = head.next->next;
        delete link;
      } else if (tmp == &tail) {

      } else if (tmp == &head) {

      }
    }
    tmp = tmp->next;
  }
}

int main()
{
  RList nlist("nlist"), clist("clist"), plist("plist"), blist("blist");
  nlist.radd(4); // goes into head
  nlist.radd(5); // the rest go in between
  nlist.radd(6);
  nlist.radd(7);
  nlist.radd(8);
  nlist.radd(9); // goes into tail

  nlist.rprint(FORWARD);
  nlist.rprint(REWIND);

  clist = nlist;
  clist.rprint(FORWARD);
  plist = clist;
  plist.rprint(FORWARD);
  blist = plist;
  blist.rprint(FORWARD);

  cout << "[END]" << endl;
  return 0;
}
