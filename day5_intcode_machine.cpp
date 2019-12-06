#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;


int opcode(int n)
{
  return (n % 10) + ((n / 10) % 10) * 10;
}

int mode_for_param(int n, int param)
{
     n = n / (int)pow(10, param + 1);
     return n % 10;
}

bool exec_next(vector<int>& mem,
	       int& start,
	       bool enable_param_mode=true)
{
  int op = mem[start];
  int orig_op = op;
  
  if (enable_param_mode) {
    op = opcode(op);
  }

  bool run_state = true;

  switch (op) {
  case 99:
    run_state = false;
    break;
  case 1:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];
      int arg3 = mem[start + 3];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);
      int mode3 = mode_for_param(orig_op, 3);

      mem[arg3] =
	(mode1? arg1 : mem[arg1]) + (mode2? arg2 : mem[arg2]);

      start += 4;
      
      break;
    }
  case 2:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];
      int arg3 = mem[start + 3];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);
      int mode3 = mode_for_param(orig_op, 3);

      mem[arg3] =
	(mode1? arg1 : mem[arg1]) * (mode2? arg2 : mem[arg2]);

      start += 4;
      
      break;
    }
  case 3:
    {
      int input;
      cin >> input;
      int arg = mem[start + 1];
      mem[arg] = input;
      start += 2;
      break;
    }
  case 4:
    {
      int arg = mem[start + 1];
      int mode = mode_for_param(orig_op, 1);
      
      cout << (mode? arg : mem[arg]) << endl;

      start += 2;

      break;
    }
  case 5:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);
      
      arg1 = mode1? arg1 : mem[arg1];
      arg2 = mode2? arg2 : mem[arg2];
      
      if (arg1)
	start = arg2;
      else
	start += 3;

      break;
    }
  case 6:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);
      
      arg1 = mode1? arg1 : mem[arg1];
      arg2 = mode2? arg2 : mem[arg2];
      
      if (!arg1)
	start = arg2;
      else
	start += 3;

      break;
    }
  case 7:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];
      int arg3 = mem[start + 3];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);
      
      arg1 = mode1? arg1 : mem[arg1];
      arg2 = mode2? arg2 : mem[arg2];
      
      if (arg1 < arg2) {
	mem[arg3] = 1;
      }
      else {
	mem[arg3] = 0;
      }

      start += 4;

      break;
    }
  case 8:
    {
      int arg1 = mem[start + 1];
      int arg2 = mem[start + 2];
      int arg3 = mem[start + 3];

      int mode1 = mode_for_param(orig_op, 1);
      int mode2 = mode_for_param(orig_op, 2);

      arg1 = mode1? arg1 : mem[arg1];
      arg2 = mode2? arg2 : mem[arg2];

      if (arg1 == arg2) {
	mem[arg3] = 1;
      }
      else {
	mem[arg3] = 0;
      }

      start += 4;

      break;
    }
  default:
    run_state = false;
    cerr << op << " Unknown instruction. HALT!" << endl;
  }

  return run_state;
}

int run_program(vector<int>& mem,
		int input1,
		int input2)
{
  mem[1] = input1;
  mem[2] = input2;
  
  int start = 0;
  
  while (exec_next(mem, start)) 
    ;
  
  return mem[0];
}

int run_program(vector<int>& mem)
{
  int start = 0;
  
  while (exec_next(mem, start))
    ;
  
  return mem[0];
}

void find_inputs(vector<int> memory,
		 int target,
		 int& input1,
		 int& input2)
{
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      auto copy_mem = memory;
      if (run_program(copy_mem, i, j) == target) {
	input1 = i;
	input2 = j;

	return;
      }
    }
  }
}


int main()
{
  vector<int> memory = {3,225,1,225,6,6,1100,1,238,225,104,0,1002,92,42,224,1001,224,-3444,224,4,224,102,8,223,223,101,4,224,224,1,224,223,223,1102,24,81,225,1101,89,36,224,101,-125,224,224,4,224,102,8,223,223,101,5,224,224,1,224,223,223,2,118,191,224,101,-880,224,224,4,224,1002,223,8,223,1001,224,7,224,1,224,223,223,1102,68,94,225,1101,85,91,225,1102,91,82,225,1102,85,77,224,101,-6545,224,224,4,224,1002,223,8,223,101,7,224,224,1,223,224,223,1101,84,20,225,102,41,36,224,101,-3321,224,224,4,224,1002,223,8,223,101,7,224,224,1,223,224,223,1,188,88,224,101,-183,224,224,4,224,1002,223,8,223,1001,224,7,224,1,224,223,223,1001,84,43,224,1001,224,-137,224,4,224,102,8,223,223,101,4,224,224,1,224,223,223,1102,71,92,225,1101,44,50,225,1102,29,47,225,101,7,195,224,101,-36,224,224,4,224,102,8,223,223,101,6,224,224,1,223,224,223,4,223,99,0,0,0,677,0,0,0,0,0,0,0,0,0,0,0,1105,0,99999,1105,227,247,1105,1,99999,1005,227,99999,1005,0,256,1105,1,99999,1106,227,99999,1106,0,265,1105,1,99999,1006,0,99999,1006,227,274,1105,1,99999,1105,1,280,1105,1,99999,1,225,225,225,1101,294,0,0,105,1,0,1105,1,99999,1106,0,300,1105,1,99999,1,225,225,225,1101,314,0,0,106,0,0,1105,1,99999,107,677,677,224,1002,223,2,223,1006,224,329,1001,223,1,223,1108,226,677,224,102,2,223,223,1006,224,344,101,1,223,223,1107,226,226,224,1002,223,2,223,1006,224,359,101,1,223,223,8,677,226,224,1002,223,2,223,1006,224,374,1001,223,1,223,1107,677,226,224,102,2,223,223,1005,224,389,1001,223,1,223,1008,677,677,224,1002,223,2,223,1006,224,404,1001,223,1,223,108,677,677,224,102,2,223,223,1005,224,419,1001,223,1,223,1107,226,677,224,102,2,223,223,1006,224,434,101,1,223,223,1008,226,226,224,1002,223,2,223,1006,224,449,1001,223,1,223,107,226,226,224,102,2,223,223,1006,224,464,1001,223,1,223,1007,677,226,224,1002,223,2,223,1006,224,479,1001,223,1,223,1108,226,226,224,102,2,223,223,1006,224,494,1001,223,1,223,8,226,226,224,1002,223,2,223,1005,224,509,1001,223,1,223,7,226,677,224,102,2,223,223,1005,224,524,101,1,223,223,1008,677,226,224,102,2,223,223,1005,224,539,101,1,223,223,107,226,677,224,1002,223,2,223,1006,224,554,1001,223,1,223,1108,677,226,224,102,2,223,223,1005,224,569,101,1,223,223,108,226,226,224,1002,223,2,223,1005,224,584,1001,223,1,223,7,677,226,224,1002,223,2,223,1005,224,599,1001,223,1,223,108,226,677,224,1002,223,2,223,1006,224,614,101,1,223,223,1007,677,677,224,1002,223,2,223,1006,224,629,101,1,223,223,7,677,677,224,102,2,223,223,1005,224,644,101,1,223,223,1007,226,226,224,1002,223,2,223,1006,224,659,1001,223,1,223,8,226,677,224,102,2,223,223,1005,224,674,1001,223,1,223,4,223,99,226};
  int start = 0;
  
  run_program(memory);
  cout << endl;
  
  return 0;
}
