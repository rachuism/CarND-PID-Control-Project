#ifndef PID_H
#define PID_H
#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double throttle;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd; 

  /*
  * My own variables
  */
  std::vector<double> dp;
  std::vector<double> p;
  int step, param_index; 
  int n_settle_steps, n_eval_steps;
  double total_error, best_error;
  //No se si me sirven
  bool tried_adding, tried_substracting;

  /*
  * Constructor
  */
  PID(); 

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  void AddToParameterAtIndex(int index, double amount);
  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
