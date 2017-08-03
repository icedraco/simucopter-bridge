classdef Yaw_state < matlab.System   

   methods (Access = protected)
        
       function yaw = stepImpl(~)
           yaw=0.0;
          if coder.target('Rtw')
            coder.cinclude('simucopter.h');
            yaw = coder.ceval('copter_get_state_yaw');
         end
      end
      
   end
end 
