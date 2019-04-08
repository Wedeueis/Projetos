package br.edu.ufabc.padm.projetopadm.controller;

import android.view.View;

import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.Document;


public class Controller {
    private View view;

    public Controller(View view){
        this.view = view;
    }

    public boolean processRequest(String option, String doctype) throws ClassNotFoundException, IllegalAccessException, InstantiationException {
            String nomeDaClasse = "br.edu.ufabc.padm.projetopadm.controller."+ option;
            Class<?> _class = Class.forName(nomeDaClasse);
            Action action = (Action) _class.newInstance();
            boolean resp = action.execute(doctype, view);
            return resp;
    }

    public Document getDocument(String type, int id){
        Document document = null;
        DAO dao = DAO.newInstance(view.getContext());
        switch(type){
            case "RG":
                document = dao.readRGById(id);
                break;
            case "CPF":
                document = dao.readCPFById(id);
                break;
            case "Carteirinha":{
                document = dao.readCarteirinhaById(id);
                break;
            }
            case "DOCUMENT":
                document = dao.readDcoumentById(id);
                break;
        }
        return document;
    }

}
