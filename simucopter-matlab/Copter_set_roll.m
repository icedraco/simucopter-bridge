classdef Copter_set_roll < matlab.System 
    
    methods (Access = protected)
 
        function stepImpl(obj, roll)
            if coder.target('Rtw')
                coder.cinclude('simucopter.h');
            
                if(roll>=-1 && roll <= 1)
                    coder.ceval('copter_motors_set_roll', roll);
                end
               
            end
        end
        
    end
end
