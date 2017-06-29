classdef sitl_get_Motors_state < matlab.System 
    
    methods (Access = protected)
 
        function [yaw, roll, pitch]= stepImpl(~)
            roll=0.0;
            pitch=0.0;
            yaw=0.0;
            
           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                roll=coder.ceval('sitl_get_state_roll');
                pitch=coder.ceval('sitl_get_state_pitch'); 
                yaw=coder.ceval('sitl_get_state_yaw'); 
                
            end
       
        end
        
    end
end
