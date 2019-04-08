Contador de Ciclistas - versão de testes
==============================================

*Esta é uma versão de testes do contador, algumas características ainda estão sendo modificadas*

O diretório *Code* possui o código que está sendo modificado no momento.

O diretório *backup* possui uma versão estável do código seguido da data em que foi salvo.

O diretório *cyclist_images* possui algumas fotos tiradas com o contador para uso futuro em tarefas de aprendizado.

### Caracteristicas implementadas

#### Calibração da camera
Para habilitar o modo de calibracão inclua no makefile a flag *-DENABLE\_CAM\_CALIBRATION*.
*obs.: Caso seja necessário gerar uma matriz de calibração nova utilize o programa contido na pasta Code/cam_calib, inclua os valores encontrados para matriz da camêra e para os coeficientes de distorção na classe CyclistPreprocessor contida em modules/CyclistTracker.*

#### Medida de tempo das funções
Para habilitar o modo de debug inclua no makefile a flag *-DDEBUG*.
Foi incluído nesse modo o cálculo do tempo das principais chamadas do programa principal. Os tempos medidos serão salvos em um arquivo .csv cada vez que o aplicativo é executado.

#### Modo de redução de Glare
Para habilitar esse modo inclua a flag *-DENABLE_GLARE_MINIMIZATION*.
	
