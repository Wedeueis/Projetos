package br.edu.ufabc.padm.projetopadm.view;

import android.Manifest;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.controller.Controller;
import br.edu.ufabc.padm.projetopadm.model.Carteirinha;
import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.RG;

public class UpdateDocumentActivity extends AppCompatActivity {

    public static final String EXTRA_ID= "id";
    private static int id;
    private Button savebutton;
    private ImageButton gallerybutton;
    private ImageButton camerabutton;
    private Bitmap mBitmap;
    private File directory;
    private EditText imageView;
    Controller controller;
    String documentType;
    public final static String option = "UpdateDocument";
    private static final String LOGTAG = UpdateDocumentActivity.class.getName();

    private static final int CAPTURE_IMAGE_REQCODE = 200;
    private static final int MULTIPLE_PERMISSION_REQ_CODE = 0;


    private static PermissionsLogic permissionsLogic;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = this.getIntent();
        id = intent.getIntExtra(EXTRA_ID, -1);
        documentType = intent.getStringExtra(DocumentTypeActivity.DOCUMENT_TYPE);
        switch(documentType){
            case "RG":
                setContentView(R.layout.activity_edit_rg);
                setTitle(R.string.update_rg_title);
                break;
            case "CPF":
                setContentView(R.layout.activity_edit_cpf);
                setTitle(R.string.update_cpf_title);
                break;
            case "Carteirinha":{
                setContentView(R.layout.activity_edit_carteirinha);
                setTitle(R.string.update_carteirinha_title);
                break;
            }
        }
        init();
        bindHandlers();
        permissionsLogic.check();
    }

    public void init(){
        controller = new Controller(findViewById(android.R.id.content));
        mBitmap = null;
        permissionsLogic = new PermissionsLogic();
        switch (documentType){
            case "RG":{
                savebutton = (Button )findViewById(R.id.edit_rg_button);
                gallerybutton = (ImageButton)findViewById(R.id.editget_rgpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.editget_rgpicture_from_camera);
                RG rg = (RG)controller.getDocument(documentType, id);
                EditText nameView = (EditText) findViewById(R.id.edit_rg_name);
                nameView.setText(rg.getNome());
                EditText numberView = (EditText) findViewById(R.id.edit_rg_number);
                numberView.setText(rg.getNumero());
                EditText fatherView  = (EditText)findViewById(R.id.edit_rg_father);
                fatherView.setText(rg.getNomeDoPai());
                EditText motherView  = (EditText)findViewById(R.id.edit_rg_mother);
                motherView.setText(rg.getNomeDaMae());
                EditText birthView   = (EditText)findViewById(R.id.edit_rg_birth);
                birthView.setText(rg.getDataDeNascimento());
                EditText birthplaceView   = (EditText)findViewById(R.id.edit_rg_birthplace);
                birthplaceView.setText(rg.getNaturalidade());
                imageView   = (EditText)findViewById(R.id.edit_rg_image);
                imageView.setText(rg.getImagem());
                break;
            }
            case "CPF":{
                savebutton = (Button)findViewById(R.id.edit_cpf_button);
                gallerybutton = (ImageButton)findViewById(R.id.editget_cpfpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.editget_cpfpicture_from_camera);
                CPF cpf = (CPF)controller.getDocument(documentType, id);
                EditText nameView = (EditText) findViewById(R.id.edit_cpf_name);
                nameView.setText(cpf.getNome());
                EditText numberView = (EditText) findViewById(R.id.edit_cpf_number);
                numberView.setText(cpf.getNumero());
                EditText birthView   = (EditText)findViewById(R.id.edit_cpf_birth);
                birthView.setText(cpf.getDataDeNascimento());
                EditText emissionView   = (EditText)findViewById(R.id.edit_cpf_emission);
                emissionView.setText(cpf.getEmissao());
                imageView = (EditText)findViewById(R.id.edit_cpf_image);
                imageView.setText(cpf.getImagem());
                break;
            }
            case "Carteirinha":{
                savebutton = (Button)findViewById(R.id.edit_carteirinha_button);
                gallerybutton = (ImageButton)findViewById(R.id.editget_cartpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.editget_cartpicture_from_camera);
                Carteirinha carteirinha = (Carteirinha)controller.getDocument(documentType, id);

                EditText nameView = (EditText) findViewById(R.id.edit_carteirinha_name);
                nameView.setText(carteirinha.getNome());
                EditText courseView = (EditText) findViewById(R.id.edit_carteirinha_course);
                courseView.setText(carteirinha.getCurso());
                EditText numberView = (EditText) findViewById(R.id.edit_carteirinha_number);
                numberView.setText(carteirinha.getNumero());
                EditText universityView = (EditText) findViewById(R.id.edit_carteirinha_university);
                universityView.setText(carteirinha.getUniversidade());
                EditText validadeView = (EditText) findViewById(R.id.edit_carteirinha_validity);
                validadeView.setText(carteirinha.getValidade());
                imageView = (EditText) findViewById(R.id.edit_carteirinha_image);
                imageView.setText(carteirinha.getImagem());
                break;
            }
        }
        camerabutton.setEnabled(false);

    }

    private void bindHandlers() {
        savebutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                save();
            }
        });
        gallerybutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                galleryPick();
            }
        });
        camerabutton.setOnClickListener(new View.OnClickListener() {
                                            @Override
                                            public void onClick(View v) {cameraPick();
                                            }
                                        });
    }

    public void save(){
        boolean sucess = false;
        try {
            sucess = controller.processRequest(option, documentType);
        } catch (IllegalAccessException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_edit_document_error), e);
        } catch (InstantiationException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_edit_document_error), e);
        } catch (ClassNotFoundException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_edit_document_error), e);
        }

        if(sucess){
            sucess = saveToInternalStorage(mBitmap);
            System.out.println("entrei");
            if(sucess){

            }else{
                Toast.makeText(this, getString(R.string.edit_document_image_failure), Toast.LENGTH_SHORT).show();
            }
            Intent intent = new Intent(this, MainActivity.class);
            Toast.makeText(this, getString(R.string.document_update_sucess), Toast.LENGTH_SHORT).show();
            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(intent);
        } else {
            Toast.makeText(this, getString(R.string.new_document_add_failure), Toast.LENGTH_SHORT).show();
        }
    }

    private void galleryPick() {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);

        intent.setType("image/*");
        if (intent.resolveActivity(getPackageManager()) != null)
            startActivityForResult(intent, 0);
    }

    private void cameraPick(){
        Intent takePictureIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
        if (takePictureIntent.resolveActivity(getPackageManager()) != null)
            startActivityForResult(takePictureIntent, CAPTURE_IMAGE_REQCODE);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == 0 && resultCode == RESULT_OK) {
            Uri photoURI = data.getData();
            System.out.println("resultok");
            try {
                mBitmap = MediaStore.Images.Media.getBitmap(this.getContentResolver(), photoURI);
            } catch (IOException e) {
                e.printStackTrace();
            }
            ContextWrapper cw = new ContextWrapper(getApplicationContext());
            // path to /data/data/yourapp/app_data/imageDir
            directory = cw.getDir("imageDir", Context.MODE_PRIVATE);
            String image = directory.getAbsolutePath();
            imageView.setText(image);
        }else if(requestCode == CAPTURE_IMAGE_REQCODE && resultCode == RESULT_OK) {
            mBitmap = (Bitmap) data.getExtras().get("data");
            ContextWrapper cw = new ContextWrapper(getApplicationContext());
            // path to /data/data/yourapp/app_data/imageDir
            directory = cw.getDir("imageDir", Context.MODE_PRIVATE);
            String image = directory.getAbsolutePath();
            imageView.setText(image);
        }else if(resultCode == RESULT_CANCELED){
            Toast.makeText(this, getString(R.string.get_image_cancel), Toast.LENGTH_SHORT).show();
        }else {
            Toast.makeText(this, getString(R.string.get_image_error), Toast.LENGTH_SHORT).show();
        }
    }

    private boolean saveToInternalStorage(Bitmap bitmapImage){
        if(bitmapImage != null) {
            System.out.println("" +
                    "teste");
            String photoname = documentType + "_image.jpg";
            File mypath = new File(directory, photoname);
            FileOutputStream fos = null;
            try {
                fos = new FileOutputStream(mypath);
                // Use the compress method on the BitMap object to write image to the OutputStream
                bitmapImage.compress(Bitmap.CompressFormat.PNG, 100, fos);
            } catch (Exception e) {
                e.printStackTrace();
                return false;
            } finally {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }
    }

    private void enableUI() {
        camerabutton.setEnabled(true);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == MULTIPLE_PERMISSION_REQ_CODE) {
            if (grantResults.length > 1 &&
                    grantResults[0] == PackageManager.PERMISSION_GRANTED &&
                    grantResults[1] == PackageManager.PERMISSION_GRANTED)
                enableUI();
            else {
                permissionsLogic.showPermissionDeniedResponseDialog(R.string.camera_not_allowed);
            }
        }
    }

    private void requestPermission() {
        ActivityCompat.requestPermissions(this,
                new String[]{
                        Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.CAMERA},
                MULTIPLE_PERMISSION_REQ_CODE);
    }

    public class PermissionsLogic {
        private void showRationaleDialog() {
            final AppCompatActivity self = UpdateDocumentActivity.this;
            AlertDialog.Builder builder = new AlertDialog.Builder(self);
            AlertDialog dialog;

            builder.setMessage(R.string.camera_rationale);
            builder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.cancel();
                    requestPermission();
                }
            });
            dialog = builder.create();
            dialog.show();
        }

        private void showPermissionDeniedResponseDialog(int message) {
            final AppCompatActivity self = UpdateDocumentActivity.this;
            AlertDialog.Builder builder = new AlertDialog.Builder(self);
            AlertDialog dialog;


            builder.setMessage(message);
            builder.setPositiveButton(R.string.ok, new DialogInterface.OnClickListener() {
                @Override
                public void onClick(DialogInterface dialog, int which) {
                    dialog.cancel();
                    self.finish();
                }
            });
            dialog = builder.create();
            dialog.show();
        }

        private boolean hasAllPermissions() {
            return ContextCompat.checkSelfPermission(UpdateDocumentActivity.this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
                    &&
                    ContextCompat.checkSelfPermission(UpdateDocumentActivity.this,
                            Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED;
        }

        private boolean shouldShowAnyRationale() {
            return ActivityCompat.shouldShowRequestPermissionRationale(UpdateDocumentActivity.this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE) &&
                    ActivityCompat.shouldShowRequestPermissionRationale(UpdateDocumentActivity.this,
                            Manifest.permission.CAMERA);
        }

        public void check() {
            // we have permission: do the work
            if (hasAllPermissions())
                enableUI();
                // we do not have permission
            else {
                // show rationale
                if (shouldShowAnyRationale()) {
                    showRationaleDialog();
                } else // ask for permission without rationale
                    requestPermission();

            }
        }
    }
}
