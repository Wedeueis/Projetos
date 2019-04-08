function [P, T, TV] = wineq_data

	wineq = csvread('winequality-red.csv');
	
	rand_sequence=randperm(size(wineq,1));
    temp_dataset=wineq;
    
    wineq=temp_dataset(rand_sequence, :);
    
    P1=wineq(1:1332,1:11);
    T1=wineq(1:1332,12);
	
	X=wineq(1333:size(wineq,1),1:11);
	Y=wineq(1333:size(wineq,1),12);
	
	fid = fopen('wineq_train','w');
	for i=1:size(P1,1)
        fprintf(fid,'%2.8f ',T1(i,1));
        for j=1:size(P1,2)
            fprintf(fid,' %2.8f', P1(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);
	
	fid = fopen('wineq_test','w');    
    for i=1:size(X,1)
        fprintf(fid,'%2.8f ',Y(i,1));
        for j=1:size(X,2)
            fprintf(fid,' %2.8f', X(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);