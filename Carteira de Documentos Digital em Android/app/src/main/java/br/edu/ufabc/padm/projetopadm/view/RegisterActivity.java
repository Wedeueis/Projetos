package br.edu.ufabc.padm.projetopadm.view;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.controller.Controller;

public class RegisterActivity extends AppCompatActivity {
    Controller controllerLogin;
    String registerType="register";
    public final static String option = "Register";
    private static final String LOGTAG = RegisterActivity.class.getName();
    private Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        init();
        bindHandlers();
    }

    private void init(){
        controllerLogin = new Controller(findViewById(android.R.id.content));
        button = (Button)findViewById(R.id.register_button);
    }

    private void bindHandlers() {
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                register();
            }
        });
    }

    public void register(){
        boolean sucess = false;
        System.out.println("entrei no registr");
        try{
            System.out.println("VOU CHAMAR O CONTROLLER");
            sucess = controllerLogin.processRequest(option, registerType);
            System.out.println("CHAMEI O CONTROLLER");
        }catch (ClassNotFoundException e){
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (InstantiationException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (IllegalAccessException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        }
        if(sucess){
            Intent intent = new Intent(this, LoginActivity.class);
            Toast.makeText(this, getString(R.string.new_register_add_success), Toast.LENGTH_SHORT).show();
            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(intent);
        }else{
            Toast.makeText(this, getString(R.string.new_register_add_failure),
                    Toast.LENGTH_SHORT).show();
        }
    }
}
