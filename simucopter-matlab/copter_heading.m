classdef copter_heading< matlab.System 
    
    methods (Access = protected)
 
        function [degrees]= stepImpl(~)
            degrees=0.0;
                  
           if coder.target('Rtw')
                coder.cinclude('simucopter.h'); 
                degrees=coder.ceval('copter_get_heading');      
            end
       
        end
        
    end
end
