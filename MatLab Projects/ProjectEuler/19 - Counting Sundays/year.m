classdef year
    % The year class takes the year number and the starting day of the week
    % in order to calculate the number of sunday's that happened on the
    % first of the year
    % 0 - Sunday, 6 - Saturday
    properties
        first_weekday
        last_weekday
        year_num
        months
        sundays
    end
    
    methods
        function init(obj, first_weekday_, year_num_)
            %UNTITLED Construct an instance of this class
            %   Detailed explanation goes here
            obj.first_weekday = first_weekday_;
            obj.year_num = year_num_;
            obj.sundays = 0;
            if isLeapYear(obj)
                obj.last_weekday = mod(366, 7) + obj.first_weekday;
            else
                obj.last_weekday = mod(365, 7) + obj.first_weekday;
            end
            
        end
        
        function result = isLeapYear(obj)
            result = mod(obj.year_num, 4) == 0 && ...
                (~(mod(obj.year_num, 100) == 0) || ...
                (mod(obj.year_num, 400) == 0));
        end
        
        function outputArg = method1(obj,inputArg)
            %METHOD1 Summary of this method goes here
            %   Detailed explanation goes here
            outputArg = obj.Property1 + inputArg;
        end
    end
end

