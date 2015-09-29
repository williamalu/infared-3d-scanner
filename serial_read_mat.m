clear all;

s = serial('COM5');
set(s, 'BaudRate', 250000);
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
            position = sscanf(serialLine, '%d %d %d');
            endOf = sscanf(serialLine, '%s');
            %fprintf(,'%d');

            if strcmp(endOf, 'AWS')
                disp('ending data');
                receivingData = false;
            else
                theta(j) = position(2);
                phi(j) = position(1);
                dist(j) = position(3);
            end
        end
    end
        disp('Out while');
        fclose(s);
        delete(s);
        clear s
catch
    disp('Catch')
    fclose(s);
    delete(s);
    clear s
end

w = 1;
 for j = 1:71
     for i = 1:61
         A(i,j) = dist(w);
         w = w + 1;
     end
 end
 A = rot90(A,2);
 pcolor(A);