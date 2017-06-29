classdef Copter_get_control_mode < matlab.System 

   methods (Access = protected)
    
       function [mode] = stepImpl(~)
           mode = 0.0;
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
                mode = coder.ceval('copter_get_control_mode');

            end
      end
      
   end
end 

