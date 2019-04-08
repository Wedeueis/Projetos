package br.edu.ufabc.padm.projetopadm.controller;

import android.view.View;
import android.widget.EditText;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.Carteirinha;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.Document;
import br.edu.ufabc.padm.projetopadm.model.RG;

public class CreateDocument implements Action {
    public boolean execute(String docType, View view){
        boolean sucess = false;
        switch (docType) {
            case "RG":{
                EditText nameView = (EditText) view.findViewById(R.id.new_rg_name);
                String name = nameView.getText().toString();
                EditText numberView = (EditText) view.findViewById(R.id.new_rg_number);
                String number = numberView.getText().toString();
                EditText fatherView = (EditText) view.findViewById(R.id.new_rg_father);
                String father = fatherView.getText().toString();
                EditText motherView = (EditText) view.findViewById(R.id.new_rg_mother);
                String mother = motherView.getText().toString();
                EditText birthView = (EditText) view.findViewById(R.id.new_rg_birth);
                String birth = birthView.getText().toString();
                EditText birthplaceView = (EditText) view.findViewById(R.id.new_rg_birthplace);
                String birthplace = birthplaceView.getText().toString();
                EditText imageView = (EditText) view.findViewById(R.id.new_rg_image);
                String image = imageView.getText().toString();
                if(name.length() == 0){
                    nameView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (number.length() == 0) {
                    numberView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (father.length() == 0) {
                    fatherView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (mother.length() == 0) {
                    motherView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (birth.length() == 0) {
                    birthView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (birthplace.length() == 0) {
                    birthplaceView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else {
                    DAO dao = DAO.newInstance(view.getContext());
                    Document doc = new Document();
                    doc.setName("RG");
                    doc.setNumber(number);
                    RG rg = new RG();

                    if (dao.createDocument(doc)) {
                        rg.setNome(name);
                        rg.setNumero(number);
                        rg.setNomeDaMae(mother);
                        rg.setNomeDoPai(father);
                        rg.setDataDeNascimento(birth);
                        rg.setNaturalidade(birthplace);
                        rg.setImagem(image);
                        doc = dao.readDcoumentByType("RG");
                        rg.setId(doc.getId());
                        if (dao.createRG(rg)) {
                            sucess = true;
                        } else {
                            dao.deleteDocument(doc);
                            sucess = false;
                        }
                    } else {
                        sucess = false;
                    }
                }
                break;
            }case "CPF": {
                EditText nameView = (EditText)view.findViewById(R.id.new_cpf_name);
                String name = nameView.getText().toString();
                EditText numberView  = (EditText)view.findViewById(R.id.new_cpf_number);
                String number = numberView.getText().toString();
                EditText birthView   = (EditText)view.findViewById(R.id.new_cpf_birth);
                String birth = birthView.getText().toString();
                EditText emissionView   = (EditText)view.findViewById(R.id.new_cpf_emission);
                String emission = emissionView.getText().toString();
                EditText imageView   = (EditText)view.findViewById(R.id.new_cpf_image);
                String image = imageView.getText().toString();
                if(name.length() == 0){
                    nameView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }else if(number.length() == 0) {
                    numberView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }else if(birth.length() == 0) {
                    birthView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }else if(emission.length() == 0) {
                    emissionView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }else {
                    DAO dao = DAO.newInstance(view.getContext());
                    Document doc = new Document();
                    doc.setName("CPF");
                    doc.setNumber(number);
                    CPF cpf = new CPF();

                    if( dao.createDocument(doc)) {
                        cpf.setNome(name);
                        cpf.setNumero(number);
                        cpf.setDataDeNascimento(birth);
                        cpf.setEmissao(emission);
                        cpf.setImagem(image);
                        doc = dao.readDcoumentByType("CPF");
                        cpf.setId(doc.getId());
                        if (dao.createCPF(cpf)) {
                            sucess = true;
                        } else {
                            dao.deleteDocument(doc);
                            sucess = false;
                        }
                    } else {
                        sucess = false;
                    }
                }
                break;
            } case "Carteirinha": {
                EditText nameViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_name);
                String nameCarteirinha = nameViewCarteirinha.getText().toString();

                EditText numberViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_number);
                String numberCarteirinha = numberViewCarteirinha.getText().toString();

                EditText courseViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_course);
                String courseCarteirinha = courseViewCarteirinha.getText().toString();

                EditText universityViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_university);
                String universityCarteirinha = universityViewCarteirinha.getText().toString();

                EditText validityViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_validity);
                String validityCarteirinha = validityViewCarteirinha.getText().toString();

                EditText imageViewCarteirinha = (EditText) view.findViewById(R.id.new_carteirinha_image);
                String imageCarteirinha = imageViewCarteirinha.getText().toString();

                if (nameCarteirinha.length() == 0) {
                    nameViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (numberCarteirinha.length() == 0) {
                    numberViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (courseCarteirinha.length() == 0) {
                    courseViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (universityCarteirinha.length() == 0) {
                    universityViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (validityCarteirinha.length() == 0) {
                    validityViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (imageCarteirinha.length() == 0) {
                    imageViewCarteirinha.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else {
                    DAO dao = DAO.newInstance(view.getContext());
                    Document doc = new Document();
                    doc.setName("Carteirinha");
                    doc.setNumber(numberCarteirinha);
                    Carteirinha carteirinha = new Carteirinha();

                    if (dao.createDocument(doc)) {
                        carteirinha.setNome(nameCarteirinha);
                        carteirinha.setNumero(numberCarteirinha);
                        carteirinha.setCurso(courseCarteirinha);
                        carteirinha.setUniversidade(universityCarteirinha);
                        carteirinha.setValidade(validityCarteirinha);
                        carteirinha.setImagem(imageCarteirinha);

                        doc = dao.readDcoumentByType("Carteirinha");
                        carteirinha.setId(doc.getId());
                        if (dao.createCarteirinha(carteirinha)) {
                            sucess = true;
                        } else {
                            dao.deleteDocument(doc);
                            sucess = false;
                        }
                    } else {
                        sucess = false;
                    }
                }
                break;
            }
        }

        return sucess;
    }
}
