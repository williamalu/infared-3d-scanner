clear all;

s = serial('COM5');
set(s, 'BaudRate', 9600);
fopen(s);
j = 0;
theta = [];
phi = [];
dist = [];
receivingData = true;

try
    while(receivingData)
        if s.BytesAvailable>=0
            j = j+1;
            serialLine = fscanf(s);
            position = sscanf(serialLine, '%d','%d','%d');
            endOf = sscanf(serialLine, '%s'); 
            %fprintf(,'%d');
            
            if strcmp(endOf, 'AWS')
                receivingData = false;
            else
                theta(j) = position(2);
                phi(j) = position(1);
                dist(j) = position(3);
            end
        end
    end
    fclose(s);
    delete(s);
    clear s
catch
    fclose(s);
    delete(s);
    clear s
end