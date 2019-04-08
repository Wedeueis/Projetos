package br.edu.ufabc.padm.projetopadm.view;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.controller.Controller;

public class DetailDocumentActivity extends AppCompatActivity {
    final Context self = this;
    Controller controller;
    public static final String EXTRA_ID = "id";
    public static int id;
    String documentType;
    public final static String option_read = "ReadDocument";
    public final static String option_delete = "DeleteDocument";

    private static final String LOGTAG = DetailDocumentActivity.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = this.getIntent();
        documentType = intent.getStringExtra(DocumentTypeActivity.DOCUMENT_TYPE);
        id = intent.getIntExtra(EXTRA_ID, -1);
        switch(documentType){
            case "RG": {
                setContentView(R.layout.activity_detail_rg);
                setTitle(R.string.detail_rg_title);
                break;
            }
            case "CPF": {
                setContentView(R.layout.activity_detail_cpf);
                setTitle(R.string.detail_cpf_title);
                break;
            }
            case "Carteirinha": {
                setContentView(R.layout.activity_detail_carteirinha);
                setTitle(R.string.detail_carteirinha_title);
                break;
            }
        }

        init();
    }

    public void init(){
        controller = new Controller(findViewById(android.R.id.content));
        try {
            controller.processRequest(option_read, documentType);
        } catch (IllegalAccessException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_read_document_error), e);
        } catch (InstantiationException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_read_document_error), e);
        } catch (ClassNotFoundException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_read_document_error), e);
        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_detail, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();

        if (id == R.id.action_settings) {
            return true;
        } else if (id == R.id.action_edit) {
            Intent intent = new Intent(this, UpdateDocumentActivity.class);
            intent.putExtra(UpdateDocumentActivity.EXTRA_ID, DetailDocumentActivity.id);
            intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, documentType);
            startActivity(intent);

            return true;
        }else if (id == R.id.action_remove) {
            AlertDialog.Builder alert = new AlertDialog.Builder(self);
            alert.setTitle(R.string.alert_title);
            alert.setMessage(R.string.alert_content);
            alert.setPositiveButton(R.string.alert_yes, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    boolean sucess = false;
                    try {
                       sucess = controller.processRequest(option_delete, documentType);
                    } catch (ClassNotFoundException e) {
                        Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                    } catch (IllegalAccessException e) {
                        Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                    } catch (InstantiationException e) {
                        Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                    }
                    if(sucess) {
                        Intent intent = new Intent(self, MainActivity.class);
                        startActivity(intent);
                        finish();
                        Toast.makeText(self, getString(R.string.remove_contact), Toast.LENGTH_LONG).show();
                        dialog.dismiss();
                    }else{
                        Toast.makeText(self, getString(R.string.remove_contact_fail), Toast.LENGTH_LONG).show();
                        dialog.dismiss();
                    }
                }
            });
            alert.setNegativeButton(R.string.alert_no, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.dismiss();
                }
            });
            alert.show();
        }

        return super.onOptionsItemSelected(item);
    }
}
