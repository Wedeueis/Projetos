package br.edu.ufabc.padm.projetopadm.view;

import android.content.Context;
import android.util.SparseBooleanArray;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.model.Document;
import br.edu.ufabc.padm.projetopadm.model.DAO;

public class DocumentAdapter extends BaseAdapter {
    private DAO dao;
    private Context context;
    LayoutInflater inflater;
    ArrayList<Document> documents;
    SparseBooleanArray checkedDocuments;

    public DocumentAdapter(Context c) {
        context = c;
        dao = DAO.newInstance(context);
        inflater = (LayoutInflater )context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        documents = dao.listDocuments();
        checkedDocuments = new SparseBooleanArray();
    }

    @Override
    public int getCount() {
        return documents.size();
    }

    @Override
    public Object getItem(int position) {
        return documents.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }


    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        TextView nome;
        TextView number;
        TextView id;
        Document document = documents.get(position);

        if (convertView == null) {
            convertView = inflater.inflate(R.layout.list_item, null);
        }
        nome = (TextView )convertView.findViewById(R.id.document_type);
        nome.setText(document.getName());
        number = (TextView )convertView.findViewById(R.id.document_number);
        number.setText(document.getNumber());
        id = (TextView )convertView.findViewById(R.id.document_id);
        id.setText(Long.toString(document.getId()));

        return convertView;
    }

    public void  toggleSelection(int position) {
        selectView(position, !checkedDocuments.get(position));
    }

    public void  removeSelection() {
        checkedDocuments = new  SparseBooleanArray();
        notifyDataSetChanged();
    }

    public void selectView(int position, boolean value) {
        if (value)
            checkedDocuments.put(position,  value);
        else
            checkedDocuments.delete(position);
        notifyDataSetChanged();
    }

    public int  getSelectedCount() {
        return checkedDocuments.size();
    }

    public  SparseBooleanArray getSelectedIds() {
        return checkedDocuments;
    }
}
