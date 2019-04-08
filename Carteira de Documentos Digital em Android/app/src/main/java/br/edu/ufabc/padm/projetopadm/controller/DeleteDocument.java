package br.edu.ufabc.padm.projetopadm.controller;

import android.view.View;

import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.Document;
import br.edu.ufabc.padm.projetopadm.model.RG;

import br.edu.ufabc.padm.projetopadm.model.Carteirinha;

public class DeleteDocument implements Action {
    public boolean execute(String docType, View view) {
        boolean sucess = false;
        switch (docType) {
            case "RG": {
                DAO dao = DAO.newInstance(view.getContext());
                Document doc = dao.readDcoumentByType("RG");
                int id = (int) doc.getId();
                RG rg = dao.readRGById(id);
                if (dao.deleteRG(rg) && dao.deleteDocument(doc)) {
                    sucess = true;
                } else {
                    sucess = false;
                }
                break;
            }case "CPF": {
                DAO dao = DAO.newInstance(view.getContext());
                Document doc = dao.readDcoumentByType("CPF");
                int id = (int) doc.getId();
                CPF cpf = dao.readCPFById(id);
                if (dao.deleteCPF(cpf) && dao.deleteDocument(doc)) {
                    sucess = true;
                } else {
                    sucess = false;
                }
                break;
            }case "Carteirinha": {
                DAO dao = DAO.newInstance(view.getContext());
                Document doc = dao.readDcoumentByType("Carteirinha");
                int id = (int) doc.getId();
                Carteirinha carteirinha = dao.readCarteirinhaById(id);
                if (dao.deleteCarteirinha(carteirinha) && dao.deleteDocument(doc)) {
                    sucess = true;
                } else {
                    sucess = false;
                }
                break;
            }
        }
        return sucess;
    }
}
