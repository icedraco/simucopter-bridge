classdef Copter_Self_State < matlab.System 

   methods (Access = protected)
   
       function [yaw, roll, pitch] = stepImpl(~)
           yaw = 0.0;
           roll = 0.0;
           pitch = 0.0;
           
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
                yaw = coder.ceval('copter_get_state_yaw');
                roll = coder.ceval('copter_get_state_roll');
                pitch = coder.ceval('copter_get_state_pitch');
            end
      end
      
   end
end 

