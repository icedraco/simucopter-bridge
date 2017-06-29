classdef RC < matlab.System 

   methods (Access = protected)
       function [thort, yawR, pitch, roll] = stepImpl(~)
         yawR = 0.0; 
         roll = 0.0; 
         pitch = 0.0; 
         thort = 0.0;  
         if coder.target('Rtw')
          coder.cinclude('simucopter.h');
          yawR = coder.ceval('copter_get_desired_yaw'); 
          roll = coder.ceval('copter_get_desired_roll'); 
          pitch = coder.ceval('copter_get_desired_pitch'); 
          thort = coder.ceval('copter_get_desired_throttle'); 
         end
   end
end 
end
