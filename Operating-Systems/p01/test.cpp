#include <iostream>
#include <string>

// move base, size, and limit to Process

// base[] = [0, 2000, ... ]
// lim [] = [1999, ... ]
// act [] = [1, 0, 0, 0, ... ]

struct mem {
  int size;
  int base[10];
  int lim[10];
  bool act[10];
};

void print_main_memory(int mem[], int l) {
  std::cout << "Main Memory:\n";
  std::cout << '[';

  for (int i = 0; i < l; ++i) {
    if (i < l - 1) {
      std::cout << mem[i] << ", ";
    } else {
      std::cout << mem[i] << "]\n";
    }
  }

  return;
}

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


bool init_process(std::string p_name, int size, Mem m) {
  int pid = get_pid(p_name);
  if (pid == -1) return false;

  // 1, check that process isn't already active
  if (m.act[pid] == 1) return false;

  // 2, check that we have contiguous space avail.
  
}


int main() {
  mem m;

  // m has base[10], which holds int values for the base location of each process i of base[i]
  // m has lim[10], which holds int values for the limit of the process at i of lim[i]
  // m has act[10], which holds bool values for the "start" value of the process at i of act[i]

  // simulate START P1 2000
  // *  Update m according to process identifier (P1 -> 0)
  //    by setting base[0] = 0 and
  //    by setting lim[0] = 2000 and
  //    then setting act[0] = 1 or True

  // get PID from "P1" -> 0
  m.base[0] = 0;
  m.lim[0] = 2000;
  m.act[0] = true;
  m.size = 8000;

  // write print functions
  for (int i = 0; i < 10; ++i) {
    std::cout << "Examining Process " << i << " ... \n";
    std::cout << "m.base[" << i << "] = " << m.base[i] << '\n';
    std::cout << "m.lim[" << i << "] = " << m.lim[i] << '\n';
    std::cout << "m.act[" << i << "] = " << m.act[i] << '\n';
  }

  
  std::cout << get_pid("P1");
  
  return 0;
}
