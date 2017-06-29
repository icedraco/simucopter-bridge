classdef Copter_throttle_state < matlab.System 

   methods (Access = protected)
   
       function [throttle] = stepImpl(~)
           throttle = 0.0;
     
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
                 throttle = coder.ceval('copter_get_state_throttle');
            end
      end
      
   end
end 

