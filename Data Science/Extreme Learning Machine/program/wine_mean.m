testELM=zeros(10,1);
trainELM=zeros(10,1);
train_timeELM=zeros(10,1);
testing_timeELM=zeros(10,1);

testMLP=zeros(10,1);
trainMLP=zeros(10,1);
train_timeMLP=zeros(10,1);
testing_timeMLP=zeros(10,1);

wb=waitbar(0,'Please waiting...');

for rnd = 1 : 10
    
    waitbar(rnd/10,wb);
    
    wine_data;
    [learn_time, test_time, train_accuracy, test_accuracy]=elm('wine_train','wine_test',1,251);
    testELM(rnd,1)=test_accuracy;
    trainELM(rnd,1)=train_accuracy;
    train_timeELM(rnd,1)=learn_time;
    testing_timeELM(rnd,1)=test_time;
	
	[learn_time, test_time, train_accuracy, test_accuracy]=mlp('wine_train','wine_test',1,15);
	testMLP(rnd,1)=test_accuracy;
    trainMLP(rnd,1)=train_accuracy;
    train_timeMLP(rnd,1)=learn_time;
    testing_timeMLP(rnd,1)=test_time;
	
end
close(wb);

AverageTrainingTimeELM=mean(train_timeELM)
StandardDeviationofTrainingTimeELM=std(train_timeELM)
AvergeTestingTimeELM=mean(testing_timeELM)
StandardDeviationofTestingTimeELM=std(testing_timeELM)
AverageTrainingAccuracyELM=mean(trainELM)
StandardDeviationofTrainingAccuracyELM=std(trainELM)
AverageTestingAccuracyELM=mean(testELM)
StandardDeviationofTestingAccuracyELM=std(testELM)

AverageTrainingTimeMLP=mean(train_timeMLP)
StandardDeviationofTrainingTimeMLP=std(train_timeMLP)
AvergeTestingTimeMLP=mean(testing_timeMLP)
StandardDeviationofTestingTimeMLP=std(testing_timeMLP)
AverageTrainingAccuracyMLP=mean(trainMLP)
StandardDeviationofTrainingAccuracyMLP=std(trainMLP)
AverageTestingAccuracyMLP=mean(testMLP)
StandardDeviationofTestingAccuracyMLP=std(testMLP)