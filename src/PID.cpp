#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Kd, double Ki) {
  // set the PID parameter accordingording to the inputs
  PID::Kp = Kp;
  PID::Kd = Kd;
  PID::Ki = Ki;
  
  // initialize all other variables
  prev_cte = 0;
  p_error = 0;
  d_error = 0;
  i_error = 0;
  best_error = 1000000; // initial best error
  total_error = 0;
  step = 0;
  ind = 0;
  up = 1; // let's start with twiddling up
  down = 0;
  
  // set the twiddle offsets to max of either tenth of the parameter or 0.001
  if (Kp!=0) {
    dKp = 0.1*Kp;
    }
  else {
    dKp = 0.001;
    }
  if (Kd!=0) {
    dKd = 0.1*Kd;
    }
  else {
    dKd = 0.001;
    }
  if (Ki!=0) {
    dKi = 0.1*Ki;
    }
  else {
    dKi = 0.001;
    }
    
  // first run will be twiddle up in K_p
  Kp = Kp+dKp;
  
  
}

void PID::UpdateParamPI(int init_steps, int eval_steps) {
  /*
  * some action is performed only if PID::step is equal to init_steps or eval_steps
  */
  
  // reset total error after settling phase
  if (step==init_steps) {
    total_error = 0;
  }
  
  // update PID parameters after evaluation phase with twiddle
  else if (step==eval_steps) {
    // print out log of the elapsed run
    std::cout<<" Parameters: "<<Kp<<" "<<Kd<<" "<<Ki<<" Total error: "<<total_error<<" Best error: "<<best_error<<std::endl;
    // go here if we were twiddling up
    if (up==1) {
      // go here if this run was the best ever
      if (total_error<best_error) {
        // set new best_error
        best_error = total_error;
        // increase the twiddling offset in current parameter and twiddle up the next one 
        if (ind==0) {
          dKp *=1.1;
          Kd += dKd;
        }
        else if (ind==1) {
          dKd *=1.1;
          Kp += dKp;
        }
        // let's move to next parameter
        ind = (ind + 1) % 2;
      }
      // if the run was not the best
      else {
        // lets try twiddling down now
        if (ind==0) {
          Kp -= 2*dKp;
        }
        else if (ind==1) {
          Kd -= 2*dKd;
        }
        up = 0;
        down = 1;
        
      }    
    }
    // go here if we were twiddling down in the last run
    else if (down==1) {
      // go here if this run was the best ever
      if (total_error<best_error) {
        // set new best_error
        best_error = total_error;
        // increase the twiddling offset in current parameter
        if (ind==0) {
          dKp *=1.1;
        }
        else if (ind==1) {
          dKd *=1.1;
        } 
      }
      // if the run was not the best
      else {
        // let's decrease twiddled parameter's offset
        if (ind==0) {
          Kp += dKp;
          dKp *=0.9;
        }
        else if (ind==1) {
          Kd += dKd;
          dKd *=0.9;
        }
      }
      // in any case let's prepare the next parameter for twiddling up
      if (ind==0) {
        Kd += dKd;
      }
      else if (ind==1) {
        Kp += dKp;
      }
      up = 1;
      down = 0;
      ind = (ind + 1) % 2;
    }
    // reset the step counter and total error
    step = 0;
    total_error = 0; 
  }
  
}


void PID::UpdateParam(int init_steps, int eval_steps) {
  /*
  * same structure as PID::UpdateParamPI, just 3 parameters instead of 2
  */

  if (step==init_steps) {
    total_error = 0;
  }
  else if (step==eval_steps) {
    std::cout<<" Parameters: "<<Kp<<" "<<Kd<<" "<<Ki<<" Total error: "<<total_error<<" Best error: "<<best_error<<std::endl;
      if (up==1) {
      if (total_error<best_error) {
        best_error = total_error;
        if (ind==0) {
          dKp *=1.1;
        }
        else if (ind==1) {
          dKd *=1.1;
        }
        else if (ind==2) {
          dKi *=1.1;
        }  
        if (ind==0) {
          Kd += dKd;
        }
        else if (ind==1) {
          Ki += dKi;
        }
        else if (ind==2) {
          Kp += dKp;
        } 
        up = 1;
        down = 0;
        ind = (ind + 1) % 3;
        
        
         
      }
      else {
        if (ind==0) {
          Kp -= 2*dKp;
        }
        else if (ind==1) {
          Kd -= 2*dKd;
        }
        else if (ind==2) {
          Ki -= 2*dKi;
        }

        up = 0;
        down = 1;
        
      }
      
    }
    else if (down==1) {
      if (total_error<best_error) {
        best_error = total_error;
        if (ind==0) {
          dKp *=1.1;
        }
        else if (ind==1) {
          dKd *=1.1;
        }
        else if (ind==2) {
          dKi *=1.1;
        } 
      }
      else {
        if (ind==0) {
          Kp += dKp;
        }
        else if (ind==1) {
          Kd += dKd;
        }
        else if (ind==2) {
          Ki += Ki;
        }
        if (ind==0) {
          dKp *=0.9;
        }
        else if (ind==1) {
          dKd *=0.9;
        }
        else if (ind==2) {
          dKi *=0.9;
        }
      }
      if (ind==0) {
        Kd += dKd;
      }
      else if (ind==1) {
        Ki += dKi;
      }
      else if (ind==2) {
        Kp += dKp;
      } 
      up = 1;
      down = 0;
      ind = (ind + 1) % 3;
    }
    step = 0;
    total_error = 0; 
  }
  
}

void PID::UpdateError(double cte) {
  // update the errors based on the cross traffic error
  
  p_error = cte; // proportional error
  d_error = cte - prev_cte; // differential error
  i_error += cte;  // integral error
  prev_cte = cte; // update previous cte
  total_error += cte*cte; // total squared error over this run
  
}

double PID::GetSteeringAngle() {
  // outputs the optimal steering value
  double steer_value = -Kp*p_error -Kd*d_error -Ki*i_error;
  return steer_value;
}

