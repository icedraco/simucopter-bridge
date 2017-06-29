classdef Roll_state < matlab.System 

   methods (Access = protected)
   
       function roll = stepImpl(~)
           roll= 0.0;
          if coder.target('Rtw')
            coder.cinclude('simucopter.h');
            roll = coder.ceval('copter_get_state_roll');
         end
      end
   end
end 
