classdef Copter_get_number < matlab.System 
    
    methods (Access = protected)
 
        function [Xout]= stepImpl(~)
            Xout=0.0;
           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                Xout=coder.ceval('copter_get_number'); 
            end
       
        end
        
    end
end
