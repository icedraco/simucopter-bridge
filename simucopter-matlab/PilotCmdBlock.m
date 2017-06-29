classdef Gyro < matlab.System 

   methods (Access = protected)
      function validatePropertiesImpl(obj)
         if ((numel(obj.inc)>1) || (obj.inc <= 0))
            error('inc of delays must be positive non-zero scalar value.');
         end
         if (numel(obj.InitialOutput)>1)
            error('Initial Output must be scalar value.');
         end
      end

      function setupImpl(obj)
         obj.count = obj.InitialOutput;
      end
      
      function resetImpl(obj)
         obj.count = obj.InitialOutput;
      end
      
      function [x y z ] = outputImpl(obj)
         %y = obj.count;
         
         y = 0.0;
         y = coder.ceval('GET_GYRO_X');
      end
      function updateImpl(obj)
         obj.count = obj.count + obj.inc;
      end
      function flag = isInputDirectFeedthroughImpl(~,~)
         flag = false;
      end
   end
end 

