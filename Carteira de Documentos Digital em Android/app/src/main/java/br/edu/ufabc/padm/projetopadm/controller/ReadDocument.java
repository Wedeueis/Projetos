package br.edu.ufabc.padm.projetopadm.controller;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import br.edu.ufabc.padm.projetopadm.view.DetailDocumentActivity;
import br.edu.ufabc.padm.projetopadm.view.DocumentTypeActivity;
import br.edu.ufabc.padm.projetopadm.view.ImageZoomActivity;
import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.view.UpdateDocumentActivity;
import br.edu.ufabc.padm.projetopadm.model.CPF;
import br.edu.ufabc.padm.projetopadm.model.DAO;
import br.edu.ufabc.padm.projetopadm.model.RG;
import br.edu.ufabc.padm.projetopadm.model.Carteirinha;

public class ReadDocument implements Action {
    public boolean execute(String docType, final View view) {
        boolean sucess = false;
        switch (docType) {
            case "RG": {
                DAO dao = DAO.newInstance(view.getContext());
                RG rg = dao.readRGById(DetailDocumentActivity.id);

                TextView nameView = (TextView) view.findViewById(R.id.detail_rg_name);
                nameView.setText(rg.getNome());

                TextView numberView = (TextView) view.findViewById(R.id.detail_rg_number);
                numberView.setText(rg.getNumero());

                TextView fatherView = (TextView) view.findViewById(R.id.detail_rg_father);
                fatherView.setText(rg.getNomeDoPai());

                TextView motherView = (TextView) view.findViewById(R.id.detail_rg_mother);
                motherView.setText(rg.getNomeDaMae());

                TextView birthView = (TextView) view.findViewById(R.id.detail_rg_birth);
                birthView.setText(rg.getDataDeNascimento());

                TextView birthplaceView = (TextView) view.findViewById(R.id.detail_rg_birthplace);
                birthplaceView.setText(rg.getNaturalidade());

                try {
                    String photo_name = "RG_image.jpg";
                    File f=new File(rg.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    ImageView imageView= (ImageView)view.findViewById(R.id.rg_image);
                    imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
                    imageView.setImageBitmap(b);
                    imageView.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            Intent intent = new Intent(view.getContext(), ImageZoomActivity.class);
                            intent.putExtra(UpdateDocumentActivity.EXTRA_ID, DetailDocumentActivity.id);
                            intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, "RG");
                            view.getContext().startActivity(intent);
                        }
                    });
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                break;
            }case "CPF": {
                DAO dao = DAO.newInstance(view.getContext());
                CPF cpf = dao.readCPFById(DetailDocumentActivity.id);

                TextView nameView = (TextView) view.findViewById(R.id.detail_cpf_name);
                nameView.setText(cpf.getNome());

                TextView numberView = (TextView) view.findViewById(R.id.detail_cpf_number);
                numberView.setText(cpf.getNumero());

                TextView birthView = (TextView) view.findViewById(R.id.detail_cpf_birth);
                birthView.setText(cpf.getDataDeNascimento());

                TextView emissionView = (TextView) view.findViewById(R.id.detail_cpf_emission);
                emissionView.setText(cpf.getEmissao());

                try {
                    String photo_name = "CPF_image.jpg";
                    File f=new File(cpf.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    ImageView imageView=(ImageView) view.findViewById(R.id.cpf_image);
                    imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
                    imageView.setImageBitmap(b);
                    imageView.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            Intent intent = new Intent(view.getContext(), ImageZoomActivity.class);
                            intent.putExtra(UpdateDocumentActivity.EXTRA_ID, DetailDocumentActivity.id);
                            intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, "CPF");
                            view.getContext().startActivity(intent);
                        }
                    });
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
                break;
            }case "Carteirinha": {
                DAO dao = DAO.newInstance(view.getContext());
                Carteirinha carteirinha = dao.readCarteirinhaById(DetailDocumentActivity.id);

                TextView nameView = (TextView) view.findViewById(R.id.detail_carteirinha_name);
                nameView.setText(carteirinha.getNome());

                TextView courseView = (TextView) view.findViewById(R.id.detail_carteirinha_course);
                courseView.setText(carteirinha.getCurso());

                TextView numberView = (TextView) view.findViewById(R.id.detail_carteirinha_number);
                numberView.setText(carteirinha.getNumero());

                TextView universityView = (TextView) view.findViewById(R.id.detail_carteirinha_university);
                universityView.setText(carteirinha.getUniversidade());

                TextView validityView = (TextView) view.findViewById(R.id.detail_carteirinha_validity);
                validityView.setText(carteirinha.getValidade());

                try {
                    String photo_name = "Carteirinha_image.jpg";
                    File f=new File(carteirinha.getImagem(), photo_name);
                    Bitmap b = BitmapFactory.decodeStream(new FileInputStream(f));
                    ImageView imageView=(ImageView) view.findViewById(R.id.carteirinha_image);
                    imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
                    imageView.setImageBitmap(b);
                    imageView.setOnClickListener(new View.OnClickListener() {
                        public void onClick(View v) {
                            Intent intent = new Intent(view.getContext(), ImageZoomActivity.class);
                            intent.putExtra(UpdateDocumentActivity.EXTRA_ID, DetailDocumentActivity.id);
                            intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, "Carteirinha");
                            view.getContext().startActivity(intent);
                        }
                    });
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }

                break;
            }
        }
        return sucess;
    }
}

