function [Weiz_adjusted] = Weiz_adjustment(Weiz)
%Since the data of Weiz have a different format than the data from the
%sensors, a function was written to adjust the format so it can be used
%in the function 'time_adjustment', which converts time and date to the
%datenum format. 
%Weiz is read in as a cell with a sub-cell for PM 2.5, PM 10, Humidity and 
%Temperature. Each sub-cell contains a row for date, time and measured
%data. 
%Rows with negative values are deleted for PM 2.5,PM 10 and Humidity.

%Input-format: 
%Weiz{dataseries}{date('dd.mm.yy'),time('HH.MM'),data}
%dateseries: {{PM 2.5}{PM 10}{Humidity}{Temperature}}

%Output-format:
%Weiz{dataseries}{date('dd.mm.yyyy'),time('HH.MM.SS'),data}
%seconds are added as '.00'


Weiz_adjusted=cell(1,length(Weiz));
%titles of tables
titles=Weiz{1}{4,1:3};

%1 PM 2,5
%2 PM 10
%3 Humidity
%4 Temperature 
for i=1:length(Weiz)
    %reads in data, changes it to a table and adds the header
    Weiz_adjusted{i}=table(Weiz{1,i}{5:end,1},Weiz{1,i}{5:end,2},nan(length(Weiz{1,i}{5:end,3}),1),'VariableNames',titles);
    %attaches seconds to the hours and minutes
    Weiz_adjusted{i}{:,2}=strcat(Weiz_adjusted{1,i}{:,2},':00');
    %splits the date at "." to change the format of the year 
    %our data: yyyy; Weiz data: yy (only last two digits)
    Weiz_date=split(Weiz_adjusted{1,i}{:,1},'.',2);
    Weiz_adjusted{i}{:,1}=strcat(Weiz_date(:,1),'.',Weiz_date(:,2),'.20',Weiz_date(:,3));
    clear Weiz_date
end

Values=cell(1,length(Weiz));
for i=1:length(Weiz)
    Values{i}=str2double(Weiz{i}{5:end,3});
    Weiz_adjusted{i}{:,3}=Values{i}(:,1);
end

%here the negative values given by Weiz are replaced with nan 
%negative values in concentrations are not meaningful and probably only
%artifacts; they also give problems with later use
for i=1:3
    Weiz_negative_values=Weiz_adjusted{i}{:,3}<0;
    Weiz_adjusted{i}{:,3}(Weiz_negative_values)=nan;
    clear Weiz_negative_values
end

%works only before year 2100 
