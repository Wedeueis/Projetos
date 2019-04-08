function [tempoTreinamento, tempoTeste, acertoTreino, acertoTeste] = elm(dadosTreinamento, dadosTeste, tipo, nNeuroniosOcultos)

%%tipos
REGRESSAO = 0;
CLASSIFICADOR = 1;

%%carregando dados de treino
dados_treino = load(dadosTreinamento);
T = dados_treino(:,1)';%saida desejada
P = dados_treino(:,2:size(dados_treino,2))';%entradas
clear dados_treino;

%%carregando dados de teste
dados_teste = load(dadosTeste);
TV.T = dados_teste(:,1)';%saida desejada
TV.P = dados_teste(:,2:size(dados_teste,2))';%entradas
clear dados_teste; 


nDadosTreino = size(P,2);
nDadosTeste = size(TV.P,2);
nNeuroniosEntrada = size(P,1);
nNeuroniosSaida = 1;

if tipo ~= REGRESSAO
	%%%pre processamento para classificacao
	saida_ordenada = sort(cat(2,T,TV.T),2);
	%%printf('%g',saida_ordenada);
	rotulo = zeros(1,1);
	rotulo(1,1)=saida_ordenada(1,1);
    j=1;
    for i = 2:(nDadosTreino+nDadosTeste) %contagem do numero de classes
        if saida_ordenada(1,i) ~= rotulo(1,j)
            j=j+1;
            rotulo(1,j) = saida_ordenada(1,i);
        end
    end
    nClasse = j;
    nNeuroniosSaida = nClasse;
	
	%%%pre processamento das saidas alvo para treinamento
    temp_T=zeros(nNeuroniosSaida, nDadosTreino);
    for i = 1:nDadosTreino
        for j = 1:nClasse
            if rotulo(1,j) == T(1,i)
                break; 
            end
        end
        temp_T(j,i)=1;
    end
    T=temp_T*2-1;
	
    %%% pre processamento das saidas alvo para teste
    temp_TV_T=zeros(nNeuroniosSaida, nDadosTeste);
    for i = 1:nDadosTeste
        for j = 1:nClasse
            if rotulo(1,j) == TV.T(1,i)
                break; 
            end
        end
        temp_TV_T(j,i)=1;
    end
    TV.T=temp_TV_T*2-1;
	
end

%%% Calculo dos pesos
inicioTempoTreino = cputime;

%%% Pesos aleatorios de entrada (w_i) e limiares aleatorios (b_i) dos neuronios da camada oculta
i=2;
E=T';
pesoSaida = zeros(1,nNeuroniosSaida);
pesoEntrada=rand(1,nNeuroniosEntrada)*2-1;
limiarCamadaOculta = rand(1,1);
tempH=pesoEntrada*P;
ind=ones(1,nDadosTreino);
matrizLimiar=limiarCamadaOculta(:,ind);
tempH=tempH+matrizLimiar;
H = (1 ./ (1 + exp(-tempH)))';
clear tempH;

for j = 1:nNeuroniosSaida
	pesoSaida(:,j)=((H'*E(:,j))/(H'*H))';
end


for j = 1:nNeuroniosSaida
	E(:,j) = E(:,j) - (pesoSaida(:,j)*H);
end
tempP = zeros(1,nNeuroniosSaida);

while((i<nNeuroniosOcultos) & (norm(E) > 0.5))
	pesoEntrada=[pesoEntrada; rand(1,nNeuroniosEntrada)*2-1];
	limiarCamadaOculta=[limiarCamadaOculta;rand(1,1)];
	tempH=pesoEntrada*P;
	ind=ones(1,nDadosTreino);
	matrizLimiar=limiarCamadaOculta(:,ind);
	tempH=tempH+matrizLimiar;

	%%%Aplicando a funcao de ativacao sigmoide na camada oculta
	H = (1 ./ (1 + exp(-tempH)))';
	clear tempH;
	for j = 1:nNeuroniosSaida
		tempP(1,j)=( H(:,i)'* E(:,j) )/(H(:,i)'*H(:,i))';
	end
	 
	%%%Calculos dos pesos de saida (beta_i)
	pesoSaida=[pesoSaida; tempP];
	
	for j = 1:nNeuroniosSaida
		E(:,j) = E(:,j) - (H(:,i-1)'*pesoSaida(i-1,j))';
	end

	i = i+1;
end

fimTempoTreino=cputime;
tempoTreinamento=fimTempoTreino-inicioTempoTreino;

tempH=pesoEntrada*P;
ind=ones(1,nDadosTreino);
matrizLimiar=limiarCamadaOculta(:,ind);
tempH=tempH+matrizLimiar;

%%%Aplicando a funcao de ativacao sigmoide na camada oculta
H = 1 ./ (1 + exp(-tempH));
clear tempH;


%%%Calculo da eficiencia do treinamento
Y=(H' * pesoSaida)';
if tipo == REGRESSAO
    acertoTreino=sqrt(mse(T - Y));
end
clear H;

%%%%%%%%%%% Calculo da saida do teste
inicioTempoTeste=cputime;
tempH_teste=pesoEntrada*TV.P;
clear TV.P;            
ind=ones(1,nDadosTeste);
matrizLimiar=limiarCamadaOculta(:,ind);
tempH_teste=tempH_teste + matrizLimiar;

%%%Saida do teste
H_teste = 1 ./ (1 + exp(-tempH_teste));
TY=(H_teste' * pesoSaida)';
fimTempoTeste=cputime;
tempoTeste=fimTempoTeste-inicioTempoTeste;

if tipo == REGRESSAO
    acertoTeste=sqrt(mse(TV.T - TY));
end

if tipo == CLASSIFICADOR
%%%%%%%%%% Calculo do acerto do treinamento e teste do classificador
    taxaErro_Treino=0;
    taxaErro_Teste=0;

    for i = 1 : size(T, 2)
        [x, rotulo_indice_esperado]=max(T(:,i));
        [x, rotulo_indice_atual]=max(Y(:,i));
        if rotulo_indice_atual~=rotulo_indice_esperado
            taxaErro_Treino=taxaErro_Treino+1;
        end
    end
    acertoTreino=1-taxaErro_Treino/size(T,2);
    for i = 1 : size(TV.T, 2)
        [x, rotulo_indice_esperado]=max(TV.T(:,i));
        [x, rotulo_indice_atual]=max(TY(:,i));
        if rotulo_indice_atual~=rotulo_indice_esperado
            taxaErro_Teste=taxaErro_Teste+1;
        end
    end
    acertoTeste=1-taxaErro_Teste/size(TV.T,2);
end
