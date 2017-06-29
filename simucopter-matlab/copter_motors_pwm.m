classdef copter_motors_pwm < matlab.System 
    
    methods (Access = protected)
 
        function [motor1,motor2, motor3, motor4]= stepImpl(~)
            motor1=0.0;
            motor2=0.0;
            motor3=0.0;
            motor4=0.0;

           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                motor1=coder.ceval('copter_get_pwm_motor1');
                motor2=coder.ceval('copter_get_pwm_motor2'); 
                motor3=coder.ceval('copter_get_pwm_motor3'); 
                motor4=coder.ceval('copterl_get_pwm_motor4'); 
  
            end
       
        end
        
    end
end
