function [AverageTrainingAccuracy, AverageTestingAccuracy] = iris_neuronios_MLP(numeroDeNeuronios)
test=zeros(5,1);
train=zeros(5,1);
train_time=zeros(5,1);
testing_time=zeros(5,1);

for rnd = 1 : 5   
    iris_data;
    [learn_time, test_time, train_accuracy, test_accuracy]=mlp('iris_train','iris_test',1,numeroDeNeuronios);
    test(rnd,1)=test_accuracy;
    train(rnd,1)=train_accuracy;
    train_time(rnd,1)=learn_time;
    testing_time(rnd,1)=test_time;
end

AverageTrainingAccuracy=mean(train)
AverageTestingAccuracy=mean(test)