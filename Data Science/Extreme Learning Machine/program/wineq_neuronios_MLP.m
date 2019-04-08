function [AverageTrainingAccuracy, AverageTestingAccuracy] = wineq_neuronios_MLP(numeroDeNeuronios)
test=zeros(5,1);
train=zeros(5,1);
train_time=zeros(5,1);
testing_time=zeros(5,1);

for rnd = 1 : 5      
    wineq_data;
    [learn_time, test_time, train_accuracy, test_accuracy]=mlp('wineq_train','wineq_test',0,numeroDeNeuronios);
    test(rnd,1)=test_accuracy;
    train(rnd,1)=train_accuracy;
    train_time(rnd,1)=learn_time;
    testing_time(rnd,1)=test_time;
end

AverageTrainingAccuracy=mean(train)
AverageTestingAccuracy=mean(test)