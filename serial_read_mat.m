clear all;

s = serial('COM8');
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
thetarad = theta.*(pi./180);
phirad = phi.*(pi./180);
x = dist.*cos(thetarad).*sin(phirad);
y = dist.*sin(thetarad).*sin(phirad);
z = dist.*cos(thetarad);
plot3(x,y,z,'ro');