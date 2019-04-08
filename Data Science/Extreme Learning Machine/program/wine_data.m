function [P, T, TV] = wine_data

	wine = csvread('wine.data.csv');
	
	rand_sequence=randperm(size(wine,1));
    temp_dataset=wine;
    
    wine=temp_dataset(rand_sequence, :);
    
    P1=wine(1:118,2:14);
    T1=wine(1:118,1);
	
	X=wine(119:size(wine,1),2:14);
	Y=wine(119:size(wine,1),1);
	
	fid = fopen('wine_train','w');
	for i=1:size(P1,1)
        fprintf(fid,'%2.8f ',T1(i,1));
        for j=1:size(P1,2)
            fprintf(fid,' %2.8f', P1(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);
	
	fid = fopen('wine_test','w');    
    for i=1:size(X,1)
        fprintf(fid,'%2.8f ',Y(i,1));
        for j=1:size(X,2)
            fprintf(fid,' %2.8f', X(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);