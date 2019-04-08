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


#Troca de conexões

#Matriz de pesos 1
w=wOut1;
wAux=ones(20,156);
k=1;


while sum(sum(abs(wAux)))~=0

	i=randperm(20,1);
	j=randperm(156,1);
	
	if wAux(i,j)~=0
	
		wAux(i,j)=0;
		
		w=w.*wAux;
		
		for step=1:35
		
			r1 = (w*rIn)>0;
			
			w = w + 0.1*(rDes1-r1)*rIn';
			
			w=w.*wAux;
		end	
			
		r1 = (w*rIn)>0;
		
		erro_perc1(k)= (sum(sum(rDes1&r1)))/52*100;
		
		kList1(k)=((k-1)/3120)*100;
		
		k=k+1;
		
	 end
 end	
 

#Matriz de pesos 2
w=wOut2;
wAux=ones(20,156);
k=1;

while sum(sum(abs(wAux)))~=0

	i=randperm(20,1);
	j=randperm(156,1);
	
	if wAux(i,j)~=0
	
		wAux(i,j)=0;
		w=w.*wAux;
		
		for step=1:35
		
			r1 = (w*rIn)>0;
			
			w = w + 0.1*(rDes2-r1)*rIn';
			
			w=w.*wAux;
		end	
			
		r1 = (w*rIn)>0;
		
		erro_perc2(k)= (sum(sum(rDes2&r1)))/104*100;
		
		kList2(k)=((k-1)/3120)*100;
		
		k=k+1;
		
	 end
 end	
 

#Matriz de pesos 3
w=wOut3;
wAux=ones(20,156);
k=1;

while sum(sum(abs(wAux)))~=0

	i=randperm(20,1);
	j=randperm(156,1);
	
	if wAux(i,j)~=0
	
		wAux(i,j)=0;
		w=w.*wAux;
		
		for step=1:35
		
			r1 = (w*rIn)>0;
			
			w = w + 0.1*(rDes3-r1)*rIn';
			
			w=w.*wAux;
		end	
			
		
		r1 = (w*rIn)>0;
		
		erro_perc3(k)= (sum(sum(rDes3&r1)))/156*100;
		
		kList3(k)=((k-1)/3120)*100;
		
		k=k+1;
		
	 end
 end	
	



#Gráficos de queda do erro por remoção de conexões

subplot(3,1,1)
	plot(kList1,erro_perc1);

subplot(3,1,2)
	plot(kList2,erro_perc2,"r");

subplot(3,1,3)
	plot(kList3,erro_perc3,"g");



figure;hold;
plot(kList1,erro_perc1);
plot(kList2,erro_perc2,"r");
plot(kList3,erro_perc3,"g");
title("Queda do erro por remoção de conexões")
xlabel('Percentual de Conexões Removidas')
ylabel("Percentual de Acertos")
legend("esparsidade 0.1","esparsidade 0.2","esparsidade 0.3","location","southwest");

#Fim de Algoritmo