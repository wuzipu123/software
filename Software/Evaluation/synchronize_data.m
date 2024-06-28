function retimed_timetable = synchronize_data(variables_cell,synchronize_time)
%sychronize_data shall synchronize the data given to it on the same
%timescale. Each cell in variables_cell correspond to one measurement and
%therefore one column in the final table. Each cell in variables_cell has 3
%different cells in it. 
%   1. Time (in datenum format) 
%   2. Data (PM data in double) 
%   3. Name (Name of the column
%Data is synchronized with function 'synchronize' and 'retime'. 
%'retime'-function needs to specify, how the values are synchronized.
%Parameter 'mean' was used, which means, that the mean of the data in the
%given timescale is used for the new value in the retimed timetable. 

%Input: 
%variables_cell{Measurement}{Data from measurement}
%Data for measurement: {time}{Data}{Name}
%Example: 
%{{Weiz_PM_2_5}{OPC_PM_2_5}}
%OPC_PM_2_5 ... {{ {time} {Data} {"OPC_PM_2_5"} }}

%synchronize_time can be any valid time argument. 
%Examples: minutes(30), hours(4), ... 

%Output: 
%Table where all columns are aligned in a single timetable



%timetable generated from all measurements 
data_timetable=cell(1,length(variables_cell));
for i=1:length(variables_cell)
    data_timetable{i}=timetable(datetime(variables_cell{i}{1},'ConvertFrom','datenum'),variables_cell{i}{2});
end

%names of the columns put into one cell 
names_of_variables=cell(1,length(variables_cell));
for i=1:length(variables_cell)
    names_of_variables{i}=variables_cell{i}{3};
end

%all columns are synchronized in one timetable 
%Times are on one timescale but data are not at the same times. 
%Example: Data from sensors measured at 00:10 and 00:25. Reference measures
%at 00:00 and 00:30. Therefore all times are included and at times where
%one measurement has no values, NaN is present. 
synchronized_timetable=data_timetable{1};
for i=2:length(variables_cell)
    synchronized_timetable=synchronize(synchronized_timetable,data_timetable{i});
end

%names of variables given by variables_cell are used as column names 
synchronized_timetable.Properties.VariableNames=names_of_variables;

%all columns in timetable are retimed on one timescale. 'mean' uses the
%mean of the data in between the given time from 'TimeStep'. IncludedEdge
%'right' means that if two times 00:10 and 00:25 are retimed on half and
%hour, they are put to the time of 00:30 and not 00:00 (which would be
%IncludedEdge 'left' and is the default setting) 
retimed_timetable=retime(synchronized_timetable,'regular','mean','TimeStep',synchronize_time,'IncludedEdge','right');
retimed_timetable.Properties.VariableNames=names_of_variables;

%delete rows with NaN values 
%If any additional value with a Nan is present, it is deleted here 
retimed_timetable(any(isnan(retimed_timetable{:,:}),2),:)=[];

