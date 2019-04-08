function [P, T, TV] = iris_data

	iris = csvread('iris.data.csv');
	
	rand_sequence=randperm(size(iris,1));
    temp_dataset=iris;
    
    iris=temp_dataset(rand_sequence, :);
    
    P1=iris(1:100,1:4);
    T1=iris(1:100,5);
	
	X=iris(101:size(iris,1),1:4);
	Y=iris(101:size(iris,1),5);
	
	fid = fopen('iris_train','w');
	for i=1:size(P1,1)
        fprintf(fid,'%2.8f ',T1(i,1));
        for j=1:size(P1,2)
            fprintf(fid,' %2.8f', P1(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);
	
	fid = fopen('iris_test','w');    
    for i=1:size(X,1)
        fprintf(fid,'%2.8f ',Y(i,1));
        for j=1:size(X,2)
            fprintf(fid,' %2.8f', X(i,j));
        end
            fprintf(fid,'\n');
        end
    fclose(fid);