# **PID Control Project**

## Goals

In this project we are given a car simulator. Our job is to make the car drive safely along the road and for that purpose we need to implement a PID controller.
We have some parameters that will help to build the controller: CTE (error in y coordinates), speed and steering angle.
To control the car we need to provide throttle and steering commands.

## Effect of the P,I, D components:

Proportional: The steering angle and the throttle is set in proportion to the existing error. The direction of the track may change and this error makes overshoot the system, that's why the derivative and the integral error are required.

Integral: There is a bias in the system. We need to avoid to get stucked in that bias, that's why we need this component. 

Derivative: It avoids the P component to overshoot. It tries to bring the change of rate to zero. It will make the car to reach the center line smoothly.

## How I tweaked the parameters

I selected the parameters manually. I use a loop to let the parameters settle down in the first 100 steps and then they start to twiddle in the next 2000 steps. I let the car to make a whole track with every parameter tweak, calculate the error and then tweak the parameters again. 

With the throttle I control the velocity of the car around the track. As it doesn't depend on left or right I just pass it the CTE. I use the same procedure as for the steering angle to minimize the error as much as possible. 
