#include "PID.h"
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

/*
* TODO: Complete the PID class.
*/
int previous_cte=0; //Puede que empiece siendo cte
int sum_cte=0;
int p_error=0;
int i_error=0;
int d_error=0;
int diff_cte=0;

PID::PID() {
    
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    PID::Kp = Kp;
    PID::Ki = Ki;
    PID::Kd = Kd;  

    p_error = i_error = d_error = 0.0;

    param_index = 2;
    n_settle_steps = 100;
    n_eval_steps = 2000;
    total_error = 0;
    best_error = numeric_limits<double>::max();
    tried_adding = false;
    tried_substracting = false;
    step = 1;


    //best_error = run(p);
    //sum(dp) > 0.0001;
    p = {Kp, Kd, Ki};
    dp = {0.1*p[0], 0.1*p[1], 0.1*p[2]};
    

    
    /*for(int i=0; i<3; i++)
    {
        p[i] += dp[i]; 
        error = TotalError();

        if(error < best_error){
            best_error = error;
            dp[i] *= 1.1;

            else{
                p[i] -= 2*dp[i];
                error = TotalError();
                if (error < best_error){
                    best_error = error;
                    
                }
                else{
                    p[i] += dp[i];
                    dp[i] *= 0.9;
                }
            }


        }
    }*/

}

void PID::UpdateError(double cte) {
    //steer = -p_error*Kp - d_error*Kd - i_error*Ki;
    cout << "Entro en el bucle" << endl;

    if (step==1){
        previous_cte = cte;
    }

    p_error = cte;
    d_error = cte - previous_cte;;
    i_error += cte;

    /*not sure
   * steer_value = -p[0]*p_error - p[1]*d_error - p[2]*i_error;
    */
   previous_cte = cte; 
   cout << "step: " << step << endl;

    if(step % (n_settle_steps + n_eval_steps) > n_settle_steps){
        total_error += pow(cte, 2);
    }

    
    if(step % (n_settle_steps + n_eval_steps) == 0){
        //p[param_index] += dp[param_index];
        cout << "step: " << step << endl;
        cout << "total error: " << total_error << endl;
        cout << "best error: " << best_error << endl;
        
        if (total_error < best_error){
            cout << "Change in dp" << endl;
            best_error = total_error;
            //La siguiente vez que paso?
            if(step != n_settle_steps + n_eval_steps){
                dp[param_index] *= 1.1;
            }
            //next parameter (loop 0, 1, 2)
            param_index = (param_index + 1) % 3;
            tried_adding = tried_substracting = false;
        }
        if(!tried_adding && !tried_substracting ){
            p[param_index] += dp[param_index];
            tried_adding = true;
        }
        else if (tried_adding && !tried_substracting){
            //tried substracting dp[i] from params[i]
            p[param_index] -= 2*dp[param_index];
            tried_substracting = true;

        }
        else{
            p[param_index] += dp[param_index];
            dp[param_index] *= 0.9;
            //next parameter
            param_index = (param_index + 1) %3;
            tried_adding = tried_substracting = false;
        }

        total_error = 0;
        cout << "new parameters" << endl;
        cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << endl;

    }
    step++;
}

double PID::TotalError() {
 /*
        error += cte**2; //No estoy seguro de esta parte

    return error/100;
    */

    return 0.0;
}

