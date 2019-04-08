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
import android.view.Menu;
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

public class CreateDocumentActivity extends AppCompatActivity {
    private Button savebutton;
    private ImageButton gallerybutton;
    private ImageButton camerabutton;
    Controller controller;
    String documentType;
    public final static String option = "CreateDocument";
    private static final String LOGTAG = CreateDocumentActivity.class.getName();

    public static final int MEDIA_TYPE_IMAGE = 1;
    public static final int MEDIA_TYPE_VIDEO = 2;
    private static final int CAPTURE_IMAGE_REQCODE = 200;
    private static final int MULTIPLE_PERMISSION_REQ_CODE = 0;


    private static PermissionsLogic permissionsLogic;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Intent intent = this.getIntent();
        documentType = intent.getStringExtra(DocumentTypeActivity.DOCUMENT_TYPE);
        switch(documentType) {
            case "RG": {
                setContentView(R.layout.activity_create_rg);
                setTitle(R.string.create_rg_title);
                break;
            }
            case "CPF":{
                setContentView(R.layout.activity_create_cpf);
                setTitle(R.string.create_cpf_title);
                break;
            }
            case "Carteirinha": {
                setContentView(R.layout.activity_create_carteirinha);
                setTitle(R.string.create_carteirinha_title);
                break;
            }
        }
        init();
        bindHandlers();
        permissionsLogic.check();
    }

    private void init(){
        controller = new Controller(findViewById(android.R.id.content));
        permissionsLogic = new PermissionsLogic();
        switch (documentType){
            case "RG":{
                savebutton = (Button )findViewById(R.id.new_rg_button);
                gallerybutton = (ImageButton)findViewById(R.id.get_rgpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.get_rgpicture_from_camera);
                break;
            }
            case "CPF":{
                savebutton = (Button )findViewById(R.id.new_cpf_button);
                gallerybutton = (ImageButton)findViewById(R.id.get_cpfpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.get_cpfpicture_from_camera);
                break;
            }
            case "Carteirinha":{
                savebutton = (Button )findViewById(R.id.new_carteirinhag_button);
                gallerybutton = (ImageButton)findViewById(R.id.get_cartpicture_from_file);
                camerabutton = (ImageButton)findViewById(R.id.get_cartpicture_from_camera);
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
                public void onClick(View v) {
                    cameraPick();
                }
            }

        );
    }

    public void save() {
        boolean sucess = false;
        try{
            sucess = controller.processRequest(option, documentType);
        }catch (ClassNotFoundException e){
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (InstantiationException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        } catch (IllegalAccessException e) {
            Log.e(LOGTAG, this.getString(R.string.controller_create_document_error), e);
        }
        if(sucess){
            Intent intent = new Intent(this, MainActivity.class);
            Toast.makeText(this, getString(R.string.new_document_add_success), Toast.LENGTH_SHORT).show();
            intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(intent);
        }else{
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
            Bitmap mBitmap = null;
            Uri photoURI = data.getData();
            try {
                mBitmap = MediaStore.Images.Media.getBitmap(this.getContentResolver(), photoURI);
            } catch (IOException e) {
                e.printStackTrace();
            }

            String image = saveToInternalStorage(mBitmap);

            switch (documentType){
                case "RG": {
                    EditText imageView = (EditText) findViewById(R.id.new_rg_image);
                    imageView.setText(image);
                    break;
                }case "CPF":{
                    EditText imageView = (EditText) findViewById(R.id.new_cpf_image);
                    imageView.setText(image);
                    break;
                }case "Carteirinha":{
                    EditText imageView = (EditText) findViewById(R.id.new_carteirinha_image);
                    imageView.setText(image);
                    break;
                }
            }

        }else if(requestCode == CAPTURE_IMAGE_REQCODE && resultCode == RESULT_OK) {
            Bitmap photo = (Bitmap) data.getExtras().get("data");

            String image = saveToInternalStorage(photo);

            switch (documentType) {
                case "RG": {
                    EditText imageView = (EditText) findViewById(R.id.new_rg_image);
                    imageView.setText(image);
                    break;
                }
                case "CPF": {
                    EditText imageView = (EditText) findViewById(R.id.new_cpf_image);
                    imageView.setText(image);
                    break;
                }
                case "Carteirinha": {
                    EditText imageView = (EditText) findViewById(R.id.new_carteirinha_image);
                    imageView.setText(image);
                    break;
                }
            }
        }else {
                Toast.makeText(this, getString(R.string.get_image_error), Toast.LENGTH_SHORT).show();
        }
    }

    private String saveToInternalStorage(Bitmap bitmapImage){
        if(bitmapImage != null) {
            ContextWrapper cw = new ContextWrapper(getApplicationContext());
            // path to /data/data/yourapp/app_data/imageDir
            File directory = cw.getDir("imageDir", Context.MODE_PRIVATE);
            String photoname = documentType + "_image.jpg";
            File mypath = new File(directory, photoname);
            FileOutputStream fos = null;
            try {
                fos = new FileOutputStream(mypath);
                // Use the compress method on the BitMap object to write image to the OutputStream
                bitmapImage.compress(Bitmap.CompressFormat.PNG, 100, fos);
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return directory.getAbsolutePath();
        }else{
            String err = "Erro ao carregar a imagem";
            return err;
        }
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu){
        getMenuInflater().inflate(R.menu.menu_new_document, menu);
        return true;
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
            final AppCompatActivity self = CreateDocumentActivity.this;
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
            final AppCompatActivity self = CreateDocumentActivity.this;
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
            return ContextCompat.checkSelfPermission(CreateDocumentActivity.this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
                    &&
                    ContextCompat.checkSelfPermission(CreateDocumentActivity.this,
                            Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED;
        }

        private boolean shouldShowAnyRationale() {
            return ActivityCompat.shouldShowRequestPermissionRationale(CreateDocumentActivity.this,
                    Manifest.permission.WRITE_EXTERNAL_STORAGE) &&
                    ActivityCompat.shouldShowRequestPermissionRationale(CreateDocumentActivity.this,
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
