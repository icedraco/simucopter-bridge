classdef Copter_set_yaw < matlab.System 
    
    methods (Access = protected)
 
        function stepImpl(obj, yaw)
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
            
                if(yaw>=-1 && yaw <= 1)
                    coder.ceval('copter_motors_set_yaw', yaw);
                end
               
            end
        end
        
    end
end
