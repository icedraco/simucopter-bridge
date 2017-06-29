classdef Copter_set_pitch < matlab.System 
    
    methods (Access = protected)
 
        function stepImpl(obj, pitch)
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
            
                if(pitch>=-1 && pitch <= 1)
                    coder.ceval('copter_motors_set_pitch', pitch);
                end
               
            end
        end
        
    end
end
