classdef Gyro < matlab.System 

   methods (Access = protected)
       function [x, y, z] = stepImpl(~)
         x=0.0;
         y=0.0;
         z=0.0;
         if coder.target('Rtw')
         coder.cinclude('simucopter.h');
         x = coder.ceval('copter_get_gyro_x');
         y = coder.ceval('copter_get_gyro_y');
         z = coder.ceval('copter_get_gyro_z');
         end
      end
   end
end 

