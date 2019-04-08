package br.edu.ufabc.padm.projetopadm.view;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

import br.edu.ufabc.padm.projetopadm.R;

public class DownloadActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_download);
        Intent intent = getIntent();
        String key = intent.getStringExtra("key");
        TextView keyView = (TextView)findViewById(R.id.key);
        keyView.setText(key);
        TextView link = (TextView)findViewById(R.id.serverlink);
        link.setText(R.string.server_link);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_simple, menu);
        return true;
    }
}
