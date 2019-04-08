package br.edu.ufabc.padm.projetopadm.view;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.support.design.widget.FloatingActionButton;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.util.SparseBooleanArray;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

import android.view.View;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Iterator;

import javax.net.ssl.HttpsURLConnection;

import br.edu.ufabc.padm.projetopadm.R;
import br.edu.ufabc.padm.projetopadm.controller.Controller;
import br.edu.ufabc.padm.projetopadm.model.Document;

public class MainActivity extends AppCompatActivity {
    private ListView listView;
    private DocumentAdapter adapter;
    FloatingActionButton fab;
    Controller controller;
    public final static String option_download = "DownloadDocument";
    public final static String option_delete = "DeleteDocument";
    public static final String APP_NAME = "IdentidadeVirtual";
    private static final String LOGTAG = MainActivity.class.getName();
    static final String AB = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static SecureRandom rnd = new SecureRandom();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        PreferenceManager.setDefaultValues(this, R.xml.preferences, false);
        init();
        populateList();
    }

    @Override
    protected void onResume(){
        super.onResume();
        init();
        populateList();
    }

    private void init() {
        listView = (ListView )findViewById(R.id.document_list);
        fab = (FloatingActionButton) findViewById(R.id.float_button);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Click action
                Intent intent = new Intent(MainActivity.this, DocumentTypeActivity.class);
                startActivity(intent);
            }
        });
        controller = new Controller(findViewById(android.R.id.content));

    }

    private void populateList() {
        adapter = new DocumentAdapter(this);
        final MainActivity self = this;
        listView.setAdapter(adapter);
        listView.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE_MODAL);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                TextView idView = (TextView) view.findViewById(R.id.document_id);
                TextView typeView = (TextView) view.findViewById(R.id.document_type);
                String type = typeView.getText().toString();
                int docId = Integer.parseInt(idView.getText().toString());
                Intent intent = new Intent(parent.getContext(), DetailDocumentActivity.class);
                intent.putExtra(DetailDocumentActivity.EXTRA_ID, docId);
                intent.putExtra(DocumentTypeActivity.DOCUMENT_TYPE, type);
                startActivity(intent);
            }
        });
        listView.setMultiChoiceModeListener(new AbsListView.MultiChoiceModeListener() {
            @Override
            public void onItemCheckedStateChanged(ActionMode mode, int position,
                                                  long id, boolean checked) {
                final int checkedCount  = listView.getCheckedItemCount();
                mode.setTitle(checkedCount  + "  Selecionados");
                adapter.toggleSelection(position);
            }

            @Override
            public boolean onActionItemClicked(final ActionMode mode, MenuItem item) {

                switch (item.getItemId()) {
                    case R.id.action_context_delete:
                        AlertDialog.Builder alert = new AlertDialog.Builder(self);
                        alert.setTitle(R.string.alert_title);
                        alert.setMessage(R.string.alert_content);
                        alert.setPositiveButton(R.string.alert_yes, new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                SparseBooleanArray checkedDocuments = adapter.getSelectedIds();
                                boolean sucess = false;
                                for (int i =  (checkedDocuments.size() - 1); i >= 0; i--) {
                                    if  (checkedDocuments.valueAt(i)) {
                                        Document selectedDocument = (Document)adapter.getItem(i);
                                        try {
                                            sucess = controller.processRequest(option_delete, selectedDocument.getName());
                                        } catch (ClassNotFoundException e) {
                                            Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                                        } catch (IllegalAccessException e) {
                                            Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                                        } catch (InstantiationException e) {
                                            Log.e(LOGTAG, getParent().getString(R.string.controller_delete_document_error), e);
                                        }
                                    }
                                }
                                mode.finish();
                                if (sucess) {
                                    Intent intent = new Intent(self, MainActivity.class);
                                    startActivity(intent);
                                    Toast.makeText(self, getString(R.string.remove_contact), Toast.LENGTH_LONG).show();
                                } else {
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

                        return true;
                    case R.id.action_download:
                        SparseBooleanArray checkedDocuments = adapter.getSelectedIds();
                        ArrayList<String> types = new ArrayList<String>();
                        String key = randomString(6);
                        types.add(key);

                        for (int i =  (checkedDocuments.size() - 1); i >= 0; i--) {
                            if  (checkedDocuments.valueAt(i)) {
                                Document selectedDocument = (Document) adapter.getItem(i);
                                types.add(selectedDocument.getName());
                            }
                        }
                        if(isNetworkConnected()){
                            new SendPostRequest().execute(types);
                        }
                        mode.finish();
                        Intent intent = new Intent(self, DownloadActivity.class);
                        intent.putExtra("key", key);
                        startActivity(intent);
                        return true;
                    default:
                        return false;
                }
            }

            @Override
            public boolean onCreateActionMode(ActionMode mode, Menu menu) {
                MenuInflater inflater = mode.getMenuInflater();
                inflater.inflate(R.menu.menu_cab_documentlist, menu);
                return true;
            }

            @Override
            public void onDestroyActionMode(ActionMode mode) {}

            @Override
            public boolean onPrepareActionMode(ActionMode mode, Menu menu) {return false;}
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public boolean isNetworkConnected() {
        boolean status = false;

        ConnectivityManager connectivityManager =
                (ConnectivityManager )getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connectivityManager.getActiveNetworkInfo();

        if (networkInfo != null && networkInfo.isConnected())
            status = true;

        return status;
    }


    public class SendPostRequest extends AsyncTask<ArrayList<String>, Void, String> {

        protected void onPreExecute(){}

        protected String doInBackground(ArrayList<String>... params) {

            try {

                URL url = new URL("http://10.0.2.2:8080/ServerProjetoPADM/dataservlet"); // here is your URL path

                ArrayList<String> data = params[0];
                String size = Integer.toString(data.size());
                JSONObject postDataParams = new JSONObject();
                postDataParams.put("size", size);
                postDataParams.put("key", data.get(0));

                for(int i=1; i<data.size(); i++) {
                    String docNum = "document" + i;
                    postDataParams.put(docNum, data.get(i));
                }

                Log.e("params",postDataParams.toString());

                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setReadTimeout(15000 /* milliseconds */);
                conn.setConnectTimeout(15000 /* milliseconds */);
                conn.setRequestMethod("POST");
                conn.setDoInput(true);
                conn.setDoOutput(true);

                OutputStream os = conn.getOutputStream();
                BufferedWriter writer = new BufferedWriter(
                        new OutputStreamWriter(os, "UTF-8"));
                writer.write(getPostDataString(postDataParams));

                writer.flush();
                writer.close();
                os.close();

                int responseCode=conn.getResponseCode();

                if (responseCode == HttpsURLConnection.HTTP_OK) {

                    BufferedReader in=new BufferedReader(new
                            InputStreamReader(
                            conn.getInputStream()));

                    StringBuffer sb = new StringBuffer("");
                    String line="";

                    while((line = in.readLine()) != null) {

                        sb.append(line);
                        break;
                    }

                    in.close();
                    return sb.toString();

                }
                else {
                    return new String("false : "+responseCode);
                }
            }
            catch(Exception e){
                return new String("Exception: " + e.getMessage());
            }

        }

        @Override
        protected void onPostExecute(String result) {
            Toast.makeText(getApplicationContext(), result,
                    Toast.LENGTH_LONG).show();
        }
    }

    public String getPostDataString(JSONObject params) throws Exception {

        StringBuilder result = new StringBuilder();
        boolean first = true;

        Iterator<String> itr = params.keys();

        while(itr.hasNext()){

            String key= itr.next();
            Object value = params.get(key);

            if (first)
                first = false;
            else
                result.append("&");

            result.append(URLEncoder.encode(key, "UTF-8"));
            result.append("=");
            result.append(URLEncoder.encode(value.toString(), "UTF-8"));

        }
        return result.toString();
    }

    String randomString( int len ){
        StringBuilder sb = new StringBuilder( len );
        for( int i = 0; i < len; i++ )
            sb.append( AB.charAt( rnd.nextInt(AB.length()) ) );
        return sb.toString();
    }

}
