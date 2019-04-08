package br.edu.ufabc.padm.projetopadm.view;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.controller.Controller;

public class LoginActivity extends Activity {
    private Button signin;
    Controller controllerLogin;
    String loginType="login";
    public final static String option = "Login";
    private static final String LOGTAG = LoginActivity.class.getName();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        controllerLogin = new Controller(findViewById(android.R.id.content));
    }

    public void signIn(View view){
        boolean sucess = false;
        try{
            sucess = controllerLogin.processRequest(option, loginType);
        }catch (ClassNotFoundException e){
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (InstantiationException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (IllegalAccessException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        }
        if(sucess){
            Intent intent = new Intent(this, MainActivity.class);
            Toast.makeText(this, getString(R.string.login_success), Toast.LENGTH_SHORT).show();
            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(intent);
            finish();
        }else{
            Toast.makeText(this, getString(R.string.login_failure), Toast.LENGTH_SHORT).show();
        }
/*
        if(user.length() == 0){
            userView.setError(this.getString(R.string.login_error_empty_user));
        }else if(password.length() == 0){
            passwordView.setError(this.getString(R.string.login_error_empty_password));
        }else{
            Intent intent = new Intent(this, MainActivity.class);
            startActivity(intent);
            finish();
        }
*/
    }

    public void signUp(View view){
        Intent intent = new Intent(this, RegisterActivity.class);
        startActivity(intent);
    }

    public void recoverPassword(View view){

    }
}
