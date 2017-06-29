classdef sitl_get_height < matlab.System 
    
    methods (Access = protected)
 
        function [altitude]= stepImpl(~)
            altitude=0.0;
           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                altitude=coder.ceval('sitl_get_height'); 
            end
       
        end
        
    end
end
