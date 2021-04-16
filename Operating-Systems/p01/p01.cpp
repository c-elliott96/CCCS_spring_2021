// File: p01.cpp
// Author: Christian Elliott
// #############################################################################
// Instructions
// - To compile, simply execute `g++ p01.cpp`.
// - To run, you must enter individual commands via
//   `get_cmd(<command string>, &m) in main().
//   This is because I've run out of time to implement file I/O or
//   interactive prompt functionality. I apologize for this.
// - The two example inputs are included in main(). You can see how my code
//   needs the commands to be entered there. 
// #############################################################################
// Design
// - I ended up using a linked-list implementation. I'm not sure why, I just
//   know that switching to that allowed me to start moving along.
// - Garbage collection kicks in when there is enough free space available, but
//   only when there's not a contiguous chunck somewhere to fit a new process in
//   to. If there is a chunk available, it will not do garbage collection.

#include <iostream>
#include <string>
#include <regex>

class Process {
public:
  int size;
  int base;
  bool act;
  int pid;
  std::string name;
  Process * p_prev;
  Process * p_next;

  Process(int size = 0, std::string s = "") {
    if (size < 2 || this->get_pid(s) == -1) {
      throw "Error: Process too small or invalid proces name\n";
    }
    this->size = size;
    this->act = true;
    this->pid = this->get_pid(s);
    this->name = s;
    this->p_prev = NULL;
    this->p_next = NULL;
  }

  ~Process() {}

  int get_pid(std::string s) {
    if (s == "P1") return 0;
    if (s == "P2") return 1;
    if (s == "P3") return 2;
    if (s == "P4") return 3;
    if (s == "P5") return 4;
    if (s == "P6") return 5;
    if (s == "P7") return 6;
    if (s == "P8") return 7;
    if (s == "P9") return 8;
    if (s == "P10") return 9;
    else return -1;
  }
};

class Mem {
public:
  Process * p_head;
  Process * p_tail;
  int mem_size;
  
  Mem(int mem_size) {
    this->mem_size = mem_size;
    this->p_head = NULL;
    this->p_tail = NULL;
  }

  friend std::ostream& operator<<(std::ostream &out, const Mem & m);

  int free_space() {
    Process * node = this->p_head;
    if (node == NULL) {
      // no procs, full size available
      return this->mem_size;
    }

    int free = this->mem_size;
    while (node != NULL) {
      free -= node->size;
      node = node->p_next;
    }

    return free;
  }

  void garbage_collector() {
    Process * node = this->p_head;

    // start at tail, work to this->p_head
    Process * tail = node;
    while (tail->p_next != NULL) {
      tail = tail->p_next;
    }

    // tail = last (which was first inserted) node
    while (tail->p_prev != NULL) {
      if (tail->p_prev->base != tail->base + tail->size) {
	(tail->p_prev)->base = tail->base + tail->size;
      }
      tail = tail->p_prev;
    }
  }

  void init_new_proc(int size, std::string name) {
    // if process exists, throw error
    // if not enough size available, check with garbage collector
    // then add process if possible. Else, throw error

    if (this->proc_active(name)) throw "Error: Process already active\n";

    int avail = this->free_space();

    // get total available room
    // get largest contiguous chunk
    // if we have enough room i.e. size < avail
    // we need to make sure we have a place for that chunk
    // i.e. if contig > size then place proc else run GC

    if (avail < size) {
      throw "Error: Not enough space available\n";
    }

    // if we get here, we have the size available.
    // however, we need to see if adding the proc will
    // fit between (this->p_head->base + this->p_head->size) and this->mem_size
    Process * new_proc = new Process(size, name);
    
    if (this->p_head != NULL) {
      
      // check to see if we can put process in without shifting
      if ((this->p_head->base + this->p_head->size + size) > this->mem_size) {
	// first, see if we can find contiguous block to put proc in

	Process * next = this->p_head;
	Process * next_two = next->p_next;
	bool contig = false;
	while (next_two != NULL) {
	  if (next_two->base + next_two->size < next->base) {
	    if (next->base - (next_two->base + next_two->size) >= size) {
	      contig = true;
	      break;
	    }
	  }
	  next = next_two;
	  next_two = next_two->p_next;
	}

	if (contig) {
	  this->p_head->p_prev = new_proc;
	  new_proc->p_next = this->p_head;
	  this->p_head = new_proc;
	  new_proc->base = (new_proc->p_next)->base + (new_proc->p_next)->size;
	  return;
	} else {
	  std::cout << "Memory fragmented ... running garbage collection ...\n";
	  this->garbage_collector();
	  this->p_head->p_prev = new_proc;
	  new_proc->p_next = this->p_head;
	  this->p_head = new_proc;
	  new_proc->base = (new_proc->p_next)->base + (new_proc->p_next)->size;
	  return;
	}
	
      } else {
	// regular head insertion
	this->p_head->p_prev = new_proc;
	new_proc->p_next = this->p_head;
	this->p_head = new_proc;
	new_proc->base = (new_proc->p_next)->base + (new_proc->p_next)->size;
      }
    } else {
      // empty Memory insertion
      this->p_head = new_proc;
      new_proc->base = 0;
    }
    
    return;
  }

  void stop_proc(std::string name) {
    Process * node = this->p_head;
    
    if (node == NULL) throw "Error: No processes in Memory\n";

    while (node != NULL) {
      if (node->name == name) {
	if (node->p_prev == NULL) {
	  if (node->p_next == NULL) {
	    // first node AND nothing follows
	    this->p_head = NULL;
	    delete node;
	    return;
	  } else {
	    // first node with something following
	    // make something following p_prev = NULL
	    // make this->p_head = something following
	    (node->p_next)->p_prev = NULL;
	    this->p_head = node->p_next;
	    delete node;
	    return;
	  }
	} else {
	  // we're NOT deleting the first node
	  if (node->p_next == NULL) {
	    // not first node with nothing following
	    // set node->p_prev->p_next = NULL
	    (node->p_prev)->p_next = NULL;
	    delete node;
	    return;
	  } else {
	    // not first node and something after
	    // change node->p_prev->p_next
	    // to equal node->p_next
	    // and node->p_next->p_prev
	    // to equal node->p_prev
	    (node->p_prev)->p_next = node->p_next;
	    (node->p_next)->p_prev = node->p_prev;
	    delete node;
	    return;
	  }
	}
      } else {
	node = node->p_next;
      }
    }

    // if we get here, process not found. Throw error
    throw "Error: Process not found in Memory\n";
    return;
  }

  Process * get_proc(std::string n) {
    Process * node = this->p_head;
    while (node != NULL) {
      if (node->pid == node->get_pid(n)) {
	return node;
      } else {
	if (node->p_next != NULL) {
	  node = node->p_next;
	} else return NULL;
      }
    }
    return node;    
  }

  bool proc_active(std::string n) {
    Process * node = this->p_head;
    while (node != NULL) {
      if (node->pid == (this->p_head)->get_pid(n)) {
	return node->act;
      }
      if (node->p_next != NULL) {
	node = node->p_next;
      } else return false;
    }
    return false;
  }

  int loc(std::string n, int va) {
    Process * p = this->get_proc(n);

    // convert below to throw error!
    if (p == NULL) {
      throw "Error: Attempted to locate on unactive process\n";
    }
    
    // TODO: validate p is active

    Process * node = this->p_head;
    int base = 0;
    while (node != p && p != NULL) {
      base += node->size;
      node = node->p_next;
    }

    return (base + va);
  }

  int loc1(std::string n, int v) {
    Process * p = this->get_proc(n);
    if (p == NULL) {
      throw "Error: Attempted to locate on unactive process\n";
    }

    if (v > p->size) {
      throw "Error: Attempted to locate offset > process size\n";
    }

    return p->base + v;
  }
};


std::ostream & operator<<(std::ostream & cout, const Mem &m) {
  cout << "MEMORY DUMP:\n[\n";
  Process * node = m.p_head;
  while (node != NULL) {
    cout << "\t{" << "Process: " << node->name << ", "
	 << "Base: " << node->base << ", "
	 << "Size: " << node->size << "}\n"; 
    node = node->p_next;      
  }
  cout << "]\n";
  return cout;
}


void get_cmd(std::string cmd, Mem * m) {
  // regexs:
  // START <proc name> <size>
  // <proc name> LOC <offset>
  // DUMP
  // STOP <proc name>
  std::regex start("START \\w\\w \\d+$");
  std::regex loc("\\w\\w LOC \\d+");
  std::regex dump("DUMP");
  std::regex stop("STOP \\w\\w");
  std::regex stopall("STOP");

  if (std::regex_match(cmd, start)) {
    // regex matches START <proc name> <size>

    // get proc name and proc size
    std::regex proc_name("P.");
    std::regex size("\\d+$");
    std::smatch m_proc_name;
    std::smatch m_size;
    std::regex_search(cmd, m_proc_name, proc_name);
    std::regex_search(cmd, m_size, size);
    
    if (m_proc_name.size() && m_size.size()) {
      // matched process name AND a size value      
      try {
	m->init_new_proc(stoi(m_size[0]), m_proc_name[0]);
      } catch (const char *e) {
	std::cout << e;
	return;
      }
    } else {
      std::cout << "Error: Unable to parse START instruction\n";
      return;
    }
  }
  else if (std::regex_match(cmd, loc)) {
    // regex matches LOC <proc name> <offset>

    // get proc name and offset
    std::regex proc_name("P.");
    std::regex size("\\d+$");
    std::smatch m_proc_name;
    std::smatch m_size;
    std::regex_search(cmd, m_proc_name, proc_name);
    std::regex_search(cmd, m_size, size);

    if (m_proc_name.size() && m_size.size()) {
      try {
	std::cout << m->loc1(m_proc_name[0], stoi(m_size[0])) << std::endl;
      } catch (const char *e) {
	std::cout << e;
	return;
      }
    } else {
      std::cout << "Error: Unable to parse LOC instruction\n";
      return;
    }
    
  }
  else if (std::regex_match(cmd, dump)) {
    // regex matches DUMP
    std::cout << *(m);
    return;
  }
  else if (std::regex_match(cmd, stop)) {
    // regex matches STOP <proc name>

    // get proc name
    std::regex proc_name("P.$");
    std::smatch m_proc_name;
    std::regex_search(cmd, m_proc_name, proc_name);

    if (m_proc_name.size()) {
      try {
	m->stop_proc(m_proc_name[0]);
      } catch (const char *e) {
	std::cout << e;
	return;
      }
    } else {
      std::cout << "Error: Unable to parse STOP process instruction\n";
      return;
    }
  }
  else if (std::regex_match(cmd, stopall)) {
    // regex matches STOP
    return;
  }
}


int main() {
  Mem m(8000);

  get_cmd("START P1 2000", &m);

  get_cmd("P1 LOC 17", &m);

  get_cmd("START P2 2000", &m);

  get_cmd("P2 LOC 17", &m);

  get_cmd("START P3 2000", &m);

  get_cmd("P3 LOC 17", &m);

  get_cmd("DUMP", &m);

  get_cmd("START P4 2000", &m);

  get_cmd("P4 LOC 17", &m);

  get_cmd("STOP P2", &m);

  get_cmd("STOP P3", &m);

  get_cmd("START P5 4000", &m);
  
  get_cmd("P1 LOC 17", &m);

  get_cmd("P4 LOC 17", &m);

  get_cmd("P5 LOC 17", &m);

  get_cmd("STOP", &m);

  // get_cmd("START P1 2000", &m);

  // get_cmd("P1 LOC 17", &m);

  // get_cmd("START P2 2000", &m);

  // get_cmd("P2 LOC 17", &m);

  // get_cmd("START P3 2000", &m);

  // get_cmd("P3 LOC 17", &m);

  // get_cmd("DUMP", &m);

  // get_cmd("START P4 2000", &m);

  // get_cmd("P4 LOC 17", &m);

  // get_cmd("STOP P1", &m);

  // get_cmd("STOP P3", &m);

  // get_cmd("DUMP", &m);

  // get_cmd("START P5 4000", &m);

  // get_cmd("DUMP", &m);
  
  // get_cmd("P1 LOC 17", &m);

  // get_cmd("P4 LOC 17", &m);

  // get_cmd("P5 LOC 17", &m);

  // get_cmd("STOP", &m);
  
  return 0;
}
