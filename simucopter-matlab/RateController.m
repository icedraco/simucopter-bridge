classdef RateController < matlab.System
    methods (Access = protected)
        function stepImpl(obj, yaw, pitch, roll)
            if coder.target('Rtw')
                coder.cinclude('simucopter-requester.h');
                coder.ceval('copter_set_rate_target_yaw',  yaw);                
                coder.ceval('copter_set_rate_target_pitch', pitch);
                coder.ceval('copter_set_rate_target_roll', roll);
            end
        end
    end
end
 