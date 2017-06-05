#include <matrix_vector.h>
#include <data_cell.h>
#include <iostream>

using namespace std;

#include <sys/time.h>
#include <sys/resource.h>

/// print resource usage of a process
/// 
/// \param[in] r object stores various resource usage statistics
/// \return non-zero on internal error
int print_memory_status(struct rusage *r)
{
  int err = 0;
  cout << "==================================================\n";
  cout << "maximum resident set size : "    << r->ru_maxrss   << " kByte\n";
  cout << "integral shared memory size : "  << r->ru_ixrss    << "\n";
  cout << "integral unshared data size : "  << r->ru_idrss    << "\n";
  cout << "integral unshared stack size : " << r->ru_isrss    << "\n";
  cout << "page reclaims : "                << r->ru_minflt   << "\n";
  cout << "page faults : "                  << r->ru_majflt   << "\n";
  cout << "swaps : "                        << r->ru_nswap    << "\n";
  cout << "block input operations : "       << r->ru_inblock  << "\n";
  cout << "block output operations : "      << r->ru_oublock  << "\n";
  cout << "messages sent : "                << r->ru_msgsnd   << "\n";
  cout << "messages received : "            << r->ru_msgrcv   << "\n";
  cout << "signals received : "             << r->ru_nsignals << "\n";
  cout << "voluntary context switches : "   << r->ru_nvcsw    << "\n";
  cout << "involuntary context switches : " << r->ru_nivcsw   << "\n";
  cout << "--------------------------------------------------\n";
  
  return err;
}; 
  

/// do multiple data cell operations
///
int do_data_cell_operations(void)
{
  int err = 0;  
  double data[9] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
  DATACELL<double> A(3,3,data), B, C(4,4,1.0);
  B = A;
  C = A;
  B.add2row(A);
  C.add2col(A);
  return err;
}

int main(int argc,char *argv[])
{
  int err = 0;
  struct rusage r;

  for(int ia=0; ia<10000; ia++)
    err += do_data_cell_operations();
  
  // get current resource usage
  err += getrusage(RUSAGE_SELF, &r);
  long mem_0 = r.ru_maxrss;
    
  for(int ia=0; ia<10000; ia++)
    err += do_data_cell_operations();
  
  // get resource usage after more data cell operations
  // if memory increaces, there are memory leaks due to
  // data cell operations
  err += getrusage(RUSAGE_SELF, &r);
  long mem_1 = r.ru_maxrss;

  // print results
  cout << "Initial measured memory : " << mem_0 << "kByte\n";
  cout << "Final measured memory :  " << mem_1 << "kByte\n";  
    
  if(mem_0 == mem_1)
    cout << ">> No memory leak found. Test passed\n";
  else
    cout << ">> WARNING: Memory leak found. Test failed\n";
        
  return err;
}
