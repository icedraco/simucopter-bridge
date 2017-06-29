% Replace BLOCK_TEMPLATE with the name of your block
% Example: Copter_Get_Pitch
% NOTE:    This name must match the filename! (Copter_Get_Pitch.m)
classdef BLOCK_TEMPLATE < matlab.System 

   methods (Access = protected)
       function result = stepImpl(~)
           result = 0.0;
         if coder.target('Rtw')
            coder.cinclude('simucopter.h');
            result = coder.ceval('copter_get_????');  % specify function
         end
      end
   end
end 
