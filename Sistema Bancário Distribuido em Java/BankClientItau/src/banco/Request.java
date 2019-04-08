package banco;

public class Request implements java.io.Serializable{       
    private String operacao;
    private Integer conta_origem;
    private Integer conta_destino;
    private Integer banco_origem;
    private Integer banco_destino;
    private Double valor;

    public String getOperacao() {
        return operacao;
    }

    public void setOperacao(String operacao) {
        this.operacao = operacao;
    }

    public Integer getConta_origem() {
        return conta_origem;
    }

    public void setConta_origem(Integer conta_origem) {
        this.conta_origem = conta_origem;
    }

    public Integer getConta_destino() {
        return conta_destino;
    }

    public void setConta_destino(Integer conta_destino) {
        this.conta_destino = conta_destino;
    }

    public Integer getBanco_origem() {
        return banco_origem;
    }

    public void setBanco_origem(Integer banco_origem) {
        this.banco_origem = banco_origem;
    }

    public Integer getBanco_destino() {
        return banco_destino;
    }

    public void setBanco_destino(Integer banco_destino) {
        this.banco_destino = banco_destino;
    }

    public Double getValor() {
        return valor;
    }

    public void setValor(Double valor) {
        this.valor = valor;
    }
}
