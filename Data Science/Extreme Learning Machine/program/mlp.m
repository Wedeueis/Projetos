function [tempoTreinamento, tempoTeste, acertoTreino, acertoTeste] = mlp(dadosTreinamento, dadosTeste, tipo, nNeuroniosOcultos)


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


net=feedforwardnet(nNeuroniosOcultos);

net.trainParam.showWindow = false;
inicioTempoTreino = cputime;
[net,tr] = train(net,P,T);
fimTempoTreino=cputime;

tempoTreinamento=fimTempoTreino-inicioTempoTreino;

Y = net(P);
clear P;

if tipo == REGRESSAO
	acertoTreino=sqrt(mse(T - Y));
end	

inicioTempoTeste=cputime;
TY = net(TV.P);
clear TV.P;
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
