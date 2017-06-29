classdef sitl_Accel < matlab.System 
    
    methods (Access = protected)
 
        function [accel_x, accel_y, accel_z]= stepImpl(~)
            accel_x=0.0;
            accel_y=0.0;
            accel_z=0.0;
            
           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                accel_x=coder.ceval('sitl_get_accel_x');
                accel_y=coder.ceval('sitl_get_accel_y'); 
                accel_z=coder.ceval('sitl_get_accel_z'); 
                
            end
       
        end
        
    end
end
