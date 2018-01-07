#ifndef PID_H
#define PID_H

class PID {
public:
  double prev_cte;
  
  /*
  * TWIDDLE
  */
  double best_error;
  double total_error;
  int step; // step counter
  int ind; // identifier of twiddled parameter
  int up; // bool if trying twiddling up 
  int down; // bool if trying twiddling down
  // twiddle offsets
  double dKp; 
  double dKi;
  double dKd;
  
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

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
  
  /*
  * Updates the PID parameters after int_steps+eval_steps of the simulator
  */
  void UpdateParam(int init_steps, int eval_steps);
  
  /*
  * Updates the PI parameters after int_steps+eval_steps of the simulator
  */
  void UpdateParamPI(int init_steps, int eval_steps);
  
  /*
  / Outputs the optimal steering value
  */
  double GetSteeringAngle();
};

#endif /* PID_H */
