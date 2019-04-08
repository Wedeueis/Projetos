package br.edu.ufabc.padm.projetopadm.model;

import java.util.Date;

/**
 * Created by Camila Sass on 05/12/2016.
 */

public class Carteirinha extends Document{
    private long id;
    private String nome;
    private String curso;
    private String numero;
    private String universidade;
    private String validade;
    private String imagem;

    public Carteirinha() {
        nome = null;
        curso = null;
        numero = null;
        universidade = null;
        validade = null;
        imagem=null;
    }

    @Override
    public long getId() {
        return id;
    }

    @Override
    public void setId(long id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getCurso() {
        return curso;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String ra) {
        this.numero = ra;
    }

    public String getUniversidade() {
        return universidade;
    }

    public void setUniversidade(String universidade) {
        this.universidade = universidade;
    }

    public String getValidade() {
        return validade;
    }

    public void setValidade(String validade) {
        this.validade = validade;
    }

    public String getImagem() {
        return imagem;
    }

    public void setImagem(String imagem) {
        this.imagem = imagem;
    }
}
