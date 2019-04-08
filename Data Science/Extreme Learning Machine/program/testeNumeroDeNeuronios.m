TrainingAccuracy = zeros(1,100);
TestingAccuracy = zeros(1,100);
minTrainingAccuracy = [100,0];
minTestingAccuracy = [100,0];
i = 1;

for trial = 220:20:500
	
	[AverageTrainingAccuracy, AverageTestingAccuracy] = wineq_neuronios_ELM(trial);
	TrainingAccuracy(i,1) = AverageTrainingAccuracy;
	TestingAccuracy(i,1) = AverageTestingAccuracy;
	
	if(AverageTrainingAccuracy<minTrainingAccuracy(1))
		minTrainingAccuracy(1) = AverageTrainingAccuracy;
		minTrainingAccuracy(2) = trial;
	end
	
	if(AverageTestingAccuracy<minTestingAccuracy(1))
		minTestingAccuracy(1) = AverageTestingAccuracy;
		minTestingAccuracy(2) = trial;
	end
	
	i=i+1;
	
end

plot(1:size(TrainingAccuracy),TrainingAccuracy);
minTrainingAccuracy
figure;
plot(1:size(TestingAccuracy),TestingAccuracy);
minTestingAccuracy