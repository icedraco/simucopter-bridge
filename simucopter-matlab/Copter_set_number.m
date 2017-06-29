classdef Copter_set_number < matlab.System 
    
    methods (Access = protected)
           function  stepImpl(obj,num)
            if coder.target('Rtw')
               coder.cinclude('simucopter.h'); 
               coder.ceval('copter_set_number', num);
            end
        end
        
    end
end




