package br.edu.ufabc.padm.projetopadm.controller;


import android.view.View;
import android.widget.EditText;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.User;

public class Login implements Action{
    @Override
    public boolean execute(String docType, View view) {
        boolean sucess = false;

        EditText userView = (EditText) view.findViewById(R.id.login_user);
        String user = userView.getText().toString();

        EditText passwordView = (EditText) view.findViewById(R.id.login_password);
        String password = passwordView.getText().toString();

        if (user.length() == 0) {
            //userView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (password.length() == 0) {
            //passwordView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else {
            DAO dao = DAO.newInstance(view.getContext());
            User newUser = new User();
            newUser.setUser(user);
            newUser.setPassword(password);

            if (dao.checkPermission(newUser)) sucess = true;
            else sucess = false;
        }

         return sucess;
    }
}
