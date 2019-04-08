#Introdução à Neurociência Computacional
#Nome: Wedeueis Braz RA: 11004813
#Testes de aprendizado em Perceptrons com diferentes esparsidades na saída.

clear;clf;

#Matriz com padrões de entrada

load pattern1;
rIn = reshape(pattern1',156,26);

#Matrizes de Pesos

wOut1 = rand(20,156)-0.5;
wOut2 = rand(20,156)-0.5;
wOut3 = rand(20,156)-0.5;

#Resposta desejada 

#esparsidade de 0.1

A1 = [ones(1,19);diag(ones(1,19))];
B1 = [zeros(1,7);ones(1,7);diag(ones(1,7));zeros(11,7)];
rDes1 = [A1 B1];

#esparsidade de 0.2

A2 = [ones(3,17);diag(ones(1,17))];
B2 = [ones(2,9);zeros(1,9);ones(1,9);diag(ones(1,9));zeros(7,9)];
rDes2 = [A2 B2];

#esparsidade de 0.3

A3 = [ones(5,15);diag(ones(1,15))];
B3 = [ones(4,11);zeros(1,11);ones(1,11);diag(ones(1,11));zeros(3,11)];
rDes3 = [A3 B3];

#Listas de erro
errorList1 = zeros(1,20);
errorList2 = zeros(1,20);
errorList3 = zeros(1,20);

#Aprendizado

for step=1:35

	rOut1 = (wOut1*rIn)>0;
	rOut2 = (wOut2*rIn)>0;
	rOut3 = (wOut3*rIn)>0;

	nErros1 = sum(sum(abs(rDes1-rOut1)));
	nErros2 = sum(sum(abs(rDes2-rOut2)));
	nErros3 = sum(sum(abs(rDes3-rOut3)));

	errorList1(step) = nErros1;
	errorList2(step) = nErros2;
	errorList3(step) = nErros3;

	wOut1 = wOut1 + 0.1*(rDes1-rOut1)*rIn';
	wOut2 = wOut2 + 0.1*(rDes2-rOut2)*rIn';
	wOut3 = wOut3 + 0.1*(rDes3-rOut3)*rIn';

 end

#Gráficos de queda do erro

subplot(3,1,1)
	plot(1:35,errorList1);

subplot(3,1,2)
	plot(1:35,errorList2,"r");

subplot(3,1,3)
	plot(1:35,errorList3,"g");


figure;hold;
plot(1:35,errorList1);
plot(1:35,errorList2,"r");
plot(1:35,errorList3,"g");
title("Aprendizado com diferentes esparsidades")
xlabel('Iterações de Aprendizado')
ylabel('Magnitude do Erro Global')
legend("esparsidade 0.1","esparsidade 0.2","esparsidade 0.3");

#Fim de Algoritmo