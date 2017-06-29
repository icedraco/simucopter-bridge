classdef Pitch_state < matlab.System 

   methods (Access = protected)
       function pitch = stepImpl(~)
           pitch =0.0;
         if coder.target('Rtw')
            coder.cinclude('simucopter.h');
            pitch = coder.ceval('copter_get_state_pitch');
         end
      end
   end
end 
