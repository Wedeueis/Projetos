package br.edu.ufabc.padm.projetopadm.controller;

import android.view.View;
import android.widget.EditText;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.Document;
import br.edu.ufabc.padm.projetopadm.model.RG;
import br.edu.ufabc.padm.projetopadm.model.Carteirinha;

public class UpdateDocument implements Action {
    public boolean execute(String docType, View view) {
        boolean sucess = false;
        switch (docType) {
            case "RG": {
                EditText nameView = (EditText) view.findViewById(R.id.edit_rg_name);
                String name = nameView.getText().toString();
                EditText numberView = (EditText) view.findViewById(R.id.edit_rg_number);
                String number = numberView.getText().toString();
                EditText fatherView = (EditText) view.findViewById(R.id.edit_rg_father);
                String father = fatherView.getText().toString();
                EditText motherView = (EditText) view.findViewById(R.id.edit_rg_mother);
                String mother = motherView.getText().toString();
                EditText birthView = (EditText) view.findViewById(R.id.edit_rg_birth);
                String birth = birthView.getText().toString();
                EditText birthplaceView = (EditText) view.findViewById(R.id.edit_rg_birthplace);
                String birthplace = birthplaceView.getText().toString();
                EditText imageView = (EditText) view.findViewById(R.id.edit_rg_image);
                String image = imageView.getText().toString();
                if (name.length() == 0) {
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
                    RG rg = new RG();
                    rg.setNome(name);
                    rg.setNumero(number);
                    rg.setNomeDaMae(mother);
                    rg.setNomeDoPai(father);
                    rg.setDataDeNascimento(birth);
                    rg.setNaturalidade(birthplace);
                    rg.setImagem(image);
                    Document doc = dao.readDcoumentByType("RG");
                    doc.setNumber(number);
                    rg.setId(doc.getId());
                    if (dao.updateRG(rg) && dao.updateDocument(doc)) {
                        sucess = true;
                    } else {
                        sucess = false;
                    }
                }
                break;
            }case "CPF": {
                EditText nameView = (EditText) view.findViewById(R.id.edit_cpf_name);
                String name = nameView.getText().toString();
                EditText numberView = (EditText) view.findViewById(R.id.edit_cpf_number);
                String number = numberView.getText().toString();
                EditText birthView = (EditText) view.findViewById(R.id.edit_cpf_birth);
                String birth = birthView.getText().toString();
                EditText emissionView = (EditText) view.findViewById(R.id.edit_cpf_emission);
                String emission = emissionView.getText().toString();
                EditText imageView = (EditText) view.findViewById(R.id.edit_cpf_image);
                String image = imageView.getText().toString();
                if (name.length() == 0) {
                    nameView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (number.length() == 0) {
                    numberView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }  else if (birth.length() == 0) {
                    birthView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (emission.length() == 0) {
                    emissionView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else {
                    DAO dao = DAO.newInstance(view.getContext());
                    CPF cpf = new CPF();
                    cpf.setNome(name);
                    cpf.setNumero(number);
                    cpf.setDataDeNascimento(birth);
                    cpf.setEmissao(emission);
                    cpf.setImagem(image);
                    Document doc = dao.readDcoumentByType("CPF");
                    doc.setNumber(number);
                    cpf.setId(doc.getId());
                    if (dao.updateCPF(cpf) && dao.updateDocument(doc)) {
                        sucess = true;
                    } else {
                        sucess = false;
                    }
                }
                break;
            }case "Carteirinha": {
                EditText nameView = (EditText) view.findViewById(R.id.edit_carteirinha_name);
                String name = nameView.getText().toString();

                EditText courseView = (EditText) view.findViewById(R.id.edit_carteirinha_course);
                String course = courseView.getText().toString();

                EditText numberView = (EditText) view.findViewById(R.id.edit_carteirinha_number);
                String number = numberView.getText().toString();

                EditText universityView = (EditText) view.findViewById(R.id.edit_carteirinha_university);
                String university = universityView.getText().toString();

                EditText validityView = (EditText) view.findViewById(R.id.edit_carteirinha_validity);
                String validity = validityView.getText().toString();

                EditText imageView = (EditText) view.findViewById(R.id.edit_carteirinha_image);
                String image = imageView.getText().toString();

                if (name.length() == 0) {
                    nameView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (course.length() == 0) {
                    courseView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (number.length() == 0) {
                    numberView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (university.length() == 0) {
                    universityView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                } else if (validity.length() == 0) {
                    validityView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                     sucess = false;
                } else if (image.length() == 0) {
                    imageView.setError(view.getContext().getString(R.string.newdocument_error_empty));
                    sucess = false;
                }else {
                    DAO dao = DAO.newInstance(view.getContext());
                    Carteirinha carteirinha = new Carteirinha();
                    carteirinha.setNome(name);
                    carteirinha.setCurso(course);
                    carteirinha.setNumero(number);
                    carteirinha.setUniversidade(university);
                    carteirinha.setValidade(validity);
                    carteirinha.setImagem(image);
                    Document doc = dao.readDcoumentByType("Carteirinha");
                    doc.setNumber(number);
                    carteirinha.setId(doc.getId());
                    if (dao.updateCarteirinha(carteirinha) && dao.updateDocument(doc)) {
                        sucess = true;
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
