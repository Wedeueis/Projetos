package br.edu.ufabc.padm.projetopadm.model;

/**
 * Created by wedeu on 14/11/2016.
 */

public class Document {
    private long id;
    private long userId;
    private String name;
    private String number;

    public Document() {
        name = null;
        number = null;
    }

    public long getId(){
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getName(){
        return name;
    }

    public void setName(String name){
        this.name = name;
    }

    public String getNumber(){
        return number;
    }

    public void setNumber(String number){
        this.number = number;
    }
}
