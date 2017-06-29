classdef Motors < matlab.System 
    
    methods (Access = protected)
 
        function stepImpl(obj, roll, pitch, yaw, throttle)
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');                 
                if(roll>=-1 && roll <= 1)
                    coder.ceval('copter_motors_set_roll', roll);
                end
                
                if(pitch>=-1 && pitch <= 1)
                    coder.ceval('copter_motors_set_pitch', pitch);
                end
                
                if(yaw>=-1 && yaw <= 1)
                    coder.ceval('copter_motors_set_yaw', yaw);
                end
                
                if(throttle>=0 && throttle <= 1)
                    coder.ceval('copter_motors_set_throttle', throttle);
                end
            end
        end
        
    end
end
