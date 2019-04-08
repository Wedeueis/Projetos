package br.edu.ufabc.padm.projetopadm.view;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.Arrays;

import br.edu.ufabc.padm.projetopadm.R;

public class DocumentTypeActivity extends AppCompatActivity {
    private ListView listView;
    private ArrayAdapter<String> listAdapter ;
    public  static final String DOCUMENT_TYPE = "documentType";
    public  static final String[] types = new String[] { "RG", "CPF", "Carteirinha" };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_document_type);
        setTitle(R.string.document_type_title);
        populateList();
    }

    private void populateList(){
        listView = (ListView )findViewById(R.id.documenttype_list);

        ArrayList<String> typeList = new ArrayList<String>();
        typeList.addAll( Arrays.asList(types) );

        listAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_selectable_list_item, typeList);

        // Set the ArrayAdapter as the ListView's adapter.
        listView.setAdapter( listAdapter );
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                switch(position){

                    //numbers here correponds to position in types
                    case 0: {
                        Intent intent = new Intent(parent.getContext(), CreateDocumentActivity.class);
                        intent.putExtra(DOCUMENT_TYPE, types[0]);
                        startActivity(intent);
                        break;
                    }

                    case 1: {
                        Intent intent = new Intent(parent.getContext(), CreateDocumentActivity.class);
                        intent.putExtra(DOCUMENT_TYPE, types[1]);
                        startActivity(intent);
                        break;
                    }

                    case 2: {
                        Intent intent = new Intent(parent.getContext(), CreateDocumentActivity.class);
                        intent.putExtra(DOCUMENT_TYPE, types[2]);
                        startActivity(intent);
                        break;
                    }
                }
            }
        });
    }


}
