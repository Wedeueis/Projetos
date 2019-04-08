package banco.model;

import java.sql.Date;
import java.sql.Time;

/*
    Tipos de transacao
    0 - Saque
    1 - Depósito
    2 - Transferencia enviada
    3 - Transferencia recebida
    4 - Doc/Ted enviado
    5 - Doc/Ted recebido
*/

public class Transacao {
    private int id;
    private int type;
    private int conta_origem;
    private int conta_destino;
    private int banco_origem;
    private int banco_destino;
    private double valor;
    private Date data;
    private Time horario;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getConta_origem() {
        return conta_origem;
    }

    public void setConta_origem(int conta_origem) {
        this.conta_origem = conta_origem;
    }

    public int getConta_destino() {
        return conta_destino;
    }

    public void setConta_destino(int conta_destino) {
        this.conta_destino = conta_destino;
    }

    public int getBanco_origem() {
        return banco_origem;
    }

    public void setBanco_origem(int banco_origem) {
        this.banco_origem = banco_origem;
    }

    public int getBanco_destino() {
        return banco_destino;
    }

    public void setBanco_destino(int banco_destino) {
        this.banco_destino = banco_destino;
    }

    public double getValor() {
        return valor;
    }

    public void setValor(double valor) {
        this.valor = valor;
    }

    public Date getData() {
        return data;
    }

    public void setData(Date data) {
        this.data = data;
    }

    public Time getHorario() {
        return horario;
    }

    public void setHorario(Time horario) {
        this.horario = horario;
    }
    
}
