classdef DemoColorDetector < matlab.System 
    
    methods (Access = protected)
 
        function [res]= stepImpl(obj,r,g,b,h,w)
           res  = 0.0;
           red  = sum(sum( r))/(h*w*255);
           blue = sum(sum( b))/(h*w*255);
           green =sum(sum( g))/(h*w*255);
           cal = max(0, (green-blue)) - max(0, (red-blue));
            if(abs(cal) <0.2)
                cal=0;
            else
                cal = (cal / abs(cal));
            end
           res=cal;
        end       
    end
end

