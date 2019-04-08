package br.edu.ufabc.padm.projetopadm.view;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.widget.ImageView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.Carteirinha;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.RG;

public class ImageZoomActivity extends Activity {
    private float x1,x2;
    static final int MIN_DISTANCE = 150;
    String documentType;
    int id;
    DAO dao;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_image_zoom);
        init();
    }

    private void init(){
        Intent intent = getIntent();
        documentType = intent.getStringExtra(DocumentTypeActivity.DOCUMENT_TYPE);
        id = intent.getIntExtra(DetailDocumentActivity.EXTRA_ID, -1);
        ImageView imageView = (ImageView)findViewById(R.id.document_fullscreen);
        dao = DAO.newInstance(this);
        switch (documentType){
            case "RG":{
                RG rg = dao.readRGById(id);
                try {
                    String photo_name = "RG_image.jpg";
                    File f=new File(rg.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
                    imageView.setImageBitmap(b);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                break;
            }case "CPF":{
                CPF cpf = dao.readCPFById(id);
                try {
                    String photo_name = "CPF_image.jpg";
                    File f=new File(cpf.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
                    imageView.setImageBitmap(b);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                break;
            }case "Carteirinha":{
                Carteirinha carteirinha = dao.readCarteirinhaById(DetailDocumentActivity.id);
                try {
                    String photo_name = "Carteirinha_image.jpg";
                    File f=new File(carteirinha.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
                    imageView.setImageBitmap(b);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                break;
            }
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {
        switch(event.getAction())
        {
            case MotionEvent.ACTION_DOWN:
                x1 = event.getX();
                break;
            case MotionEvent.ACTION_UP:
                x2 = event.getX();
                float deltaX = x2 - x1;
                if (Math.abs(deltaX) > MIN_DISTANCE)
                {
                    Intent intent = new Intent(this, DetailDocumentActivity.class);
                    intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    intent.putExtra(UpdateDocumentActivity.EXTRA_ID, DetailDocumentActivity.id);
                    intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, documentType);
                    startActivity(intent);
                }
                else
                {
                    // consider as something else - a screen tap for example
                }
                break;
        }
        return super.onTouchEvent(event);
    }
}
