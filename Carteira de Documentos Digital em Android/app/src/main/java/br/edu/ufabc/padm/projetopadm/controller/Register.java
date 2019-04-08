package br.edu.ufabc.padm.projetopadm.controller;


import android.view.View;
import android.widget.EditText;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.User;

public class Register implements Action{
    @Override
    public boolean execute(String docType, View view) {
        boolean sucess = false;
        System.out.println("Entrei no execute do register");

        EditText nameView = (EditText) view.findViewById(R.id.register_name);
        String name = nameView.getText().toString();

        EditText emailView = (EditText) view.findViewById(R.id.register_email);
        String email = emailView.getText().toString();

        EditText userView = (EditText) view.findViewById(R.id.register_user);
        String user = userView.getText().toString();

        EditText passwordView = (EditText) view.findViewById(R.id.register_password);
        String password = passwordView.getText().toString();

        EditText confirmPasswordView = (EditText) view.findViewById(R.id.register_confirmPassword);
        String confirmPassword = confirmPasswordView.getText().toString();

        if (name.length() == 0) {
            nameView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (email.length() == 0) {
            emailView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (user.length() == 0) {
            userView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (password.length() == 0) {
            passwordView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (confirmPassword.length() == 0) {
            confirmPasswordView.setError(view.getContext().getString(R.string.newdocument_error_empty));
            sucess = false;
        } else if (!confirmPassword.equals(password)) {
            passwordView.setError(view.getContext().getString(R.string.register_no_match_password));
            confirmPasswordView.setError(view.getContext().getString(R.string.register_no_match_password));
            sucess = false;
        } else {
            DAO dao = DAO.newInstance(view.getContext());
            if(!dao.isRegister(user)) {
                User newUser = new User();
                newUser.setName(name);
                newUser.setEmail(email);
                newUser.setUser(user);
                newUser.setPassword(password);
                newUser.setConfirmPassword(confirmPassword);

                if (dao.userRegistration(newUser)) sucess = true;
                else sucess = false;
            }else{
                userView.setError(view.getContext().getString(R.string.register_user_exist));
                sucess = false;
            }
        }
        return sucess;
    }
}
