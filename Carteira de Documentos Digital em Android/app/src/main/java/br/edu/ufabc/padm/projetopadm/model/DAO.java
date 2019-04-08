package br.edu.ufabc.padm.projetopadm.model;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteException;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteStatement;
import android.util.Log;


import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

import br.edu.ufabc.padm.projetopadm.R;


public class DAO extends SQLiteOpenHelper {
    private static DAO dao;
    private  Context context;
    private SQLiteDatabase db;

    private static final String DB_NAME = "idVirtual.db";
    private static final int DB_VERSION = 1;

    private static final String LOGTAG = DAO.class.getName();

    protected DAO(Context context) {
        super(context, DB_NAME, null, DB_VERSION );
        this.context = context;
        this.db = getWritableDatabase();
    }

    public static DAO newInstance(Context c) {
        if(dao == null) {
            dao = new DAO(c);
        }else {
            dao.context = c;
        }
        return dao;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        String table1 = context.getString(R.string.create_table_documents_query);
        String table2 = context.getString(R.string.create_table_users_query);
        String table3 = context.getString(R.string.create_table_rg_query);
        String table4 = context.getString(R.string.create_table_carteirinha_query);
        String table5 = context.getString(R.string.create_table_cpf_query);

        try {
            db.execSQL(table1);
            db.execSQL(table2);
            db.execSQL(table3);
            db.execSQL(table4);
            db.execSQL(table5);
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_create_database), e);
        }
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        String queryStr1 = context.getString(R.string.drop_table_documents_query);
        String queryStr2 = context.getString(R.string.drop_table_users_query);
        String queryStr3 = context.getString(R.string.drop_table_rg_query);
        String queryStr4 = context.getString(R.string.drop_table_carteirinha_query);
        String queryStr5 = context.getString(R.string.drop_table_cpf_query);

        try {
            db.execSQL(queryStr1);
            db.execSQL(queryStr2);
            db.execSQL(queryStr3);
            db.execSQL(queryStr4);
            db.execSQL(queryStr5);
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_drop_table), e);
        }
    }

    //Documents table methods
    public int getDocumentsSize(){
        String queryStr = context.getString(R.string.count_documents_query);
        int count = -1;

        try{
            Cursor cursor = db.rawQuery(queryStr,new String[]{} );

            cursor.moveToFirst();
            count = cursor.getInt(0);
            cursor.close();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_count_documents), e);
        }

        return count;
    }


    //Login
    public boolean userRegistration(User user){
        String queryStr =  context.getString(R.string.insert_user_query);
        boolean status = true;
        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            //Inserir criptografia

            statement.bindString(1, user.getName());
            statement.bindString(2, user.getEmail());
            statement.bindString(3, user.getUser());
            statement.bindString(4, user.getPassword());
            statement.bindString(5, user.getConfirmPassword());
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
            status = false;
        }
        return status;
    }

    public boolean checkPermission(User user){
        boolean permission = false;

        //Take the register user
        User userReg = readUser(user.getUser());

        if(user != null && userReg != null){
            //check password
            //in future use cripto
            String userPass = user.getPassword();
            String userRegPass = userReg.getPassword();
            if(userPass.equals(userRegPass)) permission = true;
        }
        return permission;
    }

    public boolean isRegister(String user){
        String queryStr = context.getString(R.string.search_user_query) + "'" + user + "';";
        Boolean register = true;

        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            if (cursor!=null && !cursor.moveToFirst() && cursor.getCount()==0) {
                register = false;
            }
            cursor.close();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_find_user), e);
            register = false;
            System.out.println("NÃO EH REGISTRADO");
        }

        return register;
    }

    public User readUser(String user){
        String queryStr = context.getString(R.string.search_user_query) + "'" + user + "';";
        User readUser = new User();
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});

            if (cursor!=null && cursor.moveToFirst()) {
                readUser.setName(cursor.getString(1));
                readUser.setEmail(cursor.getString(2));
                readUser.setUser(cursor.getString(3));
                System.out.println(readUser.getUser());
                readUser.setPassword(cursor.getString(4));
                System.out.println(readUser.getPassword());
                readUser.setConfirmPassword(cursor.getString(5));
            }
            cursor.close();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_find_user), e);
            System.out.println("ESTOU NO CATCH DO READ USER");
        }

        return readUser;

    }

    public boolean createDocument(Document document) {
        String queryStr = context.getString(R.string.insert_document_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, document.getName());
            statement.bindString(2, document.getNumber());
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_document), e);
            status = false;
        }

        return status;
    }


    public Document readDcoumentById(int id) {
        String queryStr = context.getString(R.string.read_document_query) + id + ";";
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            cursor.moveToFirst();
            Document doc = new RG();
            doc.setId(id);
            doc.setName(cursor.getString(1));
            doc.setNumber(cursor.getString(2));
            cursor.close();
            return doc;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_find_documents), e);
            return null;
        }
    }

    public Document readDcoumentByType(String type) {
        Document doc = null;
        String queryStr = context.getString(R.string.read_document_by_type_query) + "'" + type + "';";
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            cursor.moveToFirst();
            doc = new Document();
            doc.setId(cursor.getLong(0));
            doc.setName(cursor.getString(1));
            doc.setNumber(cursor.getString(2));
            cursor.close();
            return doc;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_find_documents), e);
        }

        return doc;
    }

    public boolean updateDocument(Document newDocument) {
        String queryStr = context.getString(R.string.update_document_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, newDocument.getName());
            statement.bindString(2, newDocument.getNumber());
            statement.bindLong(3, newDocument.getId() );
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_document), e);
            status = false;
        }

        return status;
    }

    public boolean deleteDocument(Document document) {
        long id = document.getId();
        String queryStr = context.getString(R.string.delete_document_query) + id + ";";
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
            status = false;
        }

        return status;
    }


    public ArrayList<Document> listDocuments() {
        ArrayList<Document> tasks = new ArrayList<>();
        String queryStr = context.getString(R.string.list_documents_query);

        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});

            cursor.moveToFirst();
            while(!cursor.isAfterLast()) {
                Document document = new Document();

                document.setId(cursor.getLong(0));
                document.setName(cursor.getString(1));
                document.setNumber(cursor.getString(2));
                tasks.add(document);
                cursor.moveToNext();
            }
            cursor.close();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_list_documents), e);
        }

        return tasks;
    }

    //Users table methods
    public boolean createUser(User user) {
        String queryStr = context.getString(R.string.insert_user_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, user.getName());
            statement.bindString(2, user.getEmail());
            statement.bindString(3, user.getUser());
            statement.bindString(4, user.getPassword());
            statement.bindString(5, user.getConfirmPassword());
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
            status = false;
        }

        return status;
    }

    public Document readUserById(int id) {
        // TODO: select only one element in the documents table

        return null;
    }

    public boolean updateUser(User oldUser, User newUser) {
        // TODO: updateDocument the fields of the old document to have the fields of the new document
        return false;
    }

    public boolean deleteUser(User user) {
        // TODO: deleteDocument a document from the db

        return false;
    }

    //RG table methods
    public boolean createRG(RG rg) {
        String queryStr = context.getString(R.string.insert_rg_query);
        boolean status = false;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindLong(1, rg.getId());
            statement.bindString(2, rg.getNome());
            statement.bindString(3, rg.getNumero());
            statement.bindString(4, rg.getNomeDoPai());
            statement.bindString(5, rg.getNomeDaMae());
            statement.bindString(6, rg.getDataDeNascimento());
            statement.bindString(7, rg.getNaturalidade());
            statement.bindString(8, rg.getImagem());
            statement.execute();
            status = true;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_document), e);
            status = false;
        }

        return status;
    }


    public RG readRGById(int id) {
        String queryStr = context.getString(R.string.read_rg_query) + id + ";";
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            cursor.moveToFirst();
            RG rg = new RG();
            rg.setId(cursor.getLong(0));
            rg.setNome(cursor.getString(1));
            rg.setNumero(cursor.getString(2));
            rg.setNomeDoPai(cursor.getString(3));
            rg.setNomeDaMae(cursor.getString(4));
            rg.setDataDeNascimento(cursor.getString(5));
            rg.setNaturalidade(cursor.getString(6));
            rg.setImagem(cursor.getString(7));
            cursor.close();
            return rg;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_list_documents), e);
            return null;
        }

    }

    public boolean updateRG(RG newRG) {
        String queryStr = context.getString(R.string.update_rg_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, newRG.getNome());
            statement.bindString(2, newRG.getNumero());
            statement.bindString(3, newRG.getNomeDoPai());
            statement.bindString(4, newRG.getNomeDaMae());
            statement.bindString(5, newRG.getDataDeNascimento());
            statement.bindString(6, newRG.getNaturalidade());
            statement.bindString(7, newRG.getImagem());
            statement.bindLong(8, newRG.getId() );
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_update_document), e);
            status = false;
        }

        return status;
    }

    public boolean deleteRG(RG rg) {
        long id = rg.getId();
        String queryStr = context.getString(R.string.delete_rg_query) + id + ";";
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);
            statement.execute();
            Document doc = dao.readDcoumentById(((int)id));
            status = dao.deleteDocument(doc);
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
            status = false;
        }

        return status;
    }

    //CPF table methods
    public boolean createCPF(CPF cpf) {
        String queryStr = context.getString(R.string.insert_cpf_query);
        boolean status = false;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindLong(1, cpf.getId());
            statement.bindString(2, cpf.getNome());
            statement.bindString(3, cpf.getNumero());
            statement.bindString(4, cpf.getDataDeNascimento());
            statement.bindString(5, cpf.getEmissao());
            statement.bindString(6, cpf.getImagem());
            statement.execute();
            status = true;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_document), e);
            status = false;
        }

        return status;
    }


    public CPF readCPFById(int id) {
        String queryStr = context.getString(R.string.read_cpf_query) + id + ";";
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            cursor.moveToFirst();
            CPF cpf = new CPF();
            cpf.setId(cursor.getLong(0));
            cpf.setNome(cursor.getString(1));
            cpf.setNumero(cursor.getString(2));
            cpf.setDataDeNascimento(cursor.getString(3));
            cpf.setEmissao(cursor.getString(4));
            cpf.setImagem(cursor.getString(5));
            cursor.close();
            return cpf;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_list_documents), e);
            return null;
        }

    }

    public boolean updateCPF(CPF newCPF) {
        String queryStr = context.getString(R.string.update_cpf_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, newCPF.getNome());
            statement.bindString(2, newCPF.getNumero());
            statement.bindString(3, newCPF.getDataDeNascimento());
            statement.bindString(4, newCPF.getEmissao());
            statement.bindString(5, newCPF.getImagem());
            statement.bindLong(6, newCPF.getId() );
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_update_document), e);
            status = false;
        }

        return status;
    }

    public boolean deleteCPF(CPF cpf) {
        long id = cpf.getId();
        String queryStr = context.getString(R.string.delete_cpf_query) + id + ";";
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);
            statement.execute();
            Document doc = dao.readDcoumentById(((int)id));
            status = dao.deleteDocument(doc);
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
            status = false;
        }

        return status;
    }

    //Carteirinha table methods
    public boolean createCarteirinha(Carteirinha carteirinha) {
        String queryStr = context.getString(R.string.insert_carteirinha_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindLong(1, carteirinha.getId());
            statement.bindString(2, carteirinha.getNome());
            statement.bindString(3, carteirinha.getCurso());
            statement.bindString(4, carteirinha.getNumero());
            statement.bindString(5, carteirinha.getUniversidade());
            statement.bindString(6, carteirinha.getValidade());
            statement.bindString(7, carteirinha.getImagem());
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_insert_document), e);
            status = false;
        }

        return status;
    }


    public Carteirinha readCarteirinhaById(int id) {
        String queryStr = context.getString(R.string.read_carteirinha_query) + id + ";";
        try {
            Cursor cursor = db.rawQuery(queryStr, new String[]{});
            cursor.moveToFirst();
            Carteirinha carteirinha = new Carteirinha();

            carteirinha.setId(cursor.getLong(0));
            carteirinha.setNome(cursor.getString(1));
            carteirinha.setCurso(cursor.getString(2));
            carteirinha.setNumero(cursor.getString(3));
            carteirinha.setUniversidade(cursor.getString(4));
            carteirinha.setValidade(cursor.getString(5));
            carteirinha.setImagem(cursor.getString(6));
            cursor.close();
            return carteirinha;
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_list_documents), e);
            return null;
        }

    }

    //Arrumar - so esta fazendo update de documents
    public boolean updateCarteirinha(Carteirinha newCarteirinha) {
        String queryStr = context.getString(R.string.update_carteirinha_query);
        boolean status = true;

        try {
            SQLiteStatement statement = db.compileStatement(queryStr);

            statement.bindString(1, newCarteirinha.getNome());
            statement.bindString(2, newCarteirinha.getCurso());
            statement.bindString(3, newCarteirinha.getNumero());
            statement.bindString(4, newCarteirinha.getUniversidade());
            statement.bindString(5, newCarteirinha.getValidade());
            statement.bindString(6, newCarteirinha.getImagem());
            statement.bindLong(7, newCarteirinha.getId());
            statement.execute();
        } catch (SQLiteException e) {
            Log.e(LOGTAG, context.getString(R.string.failed_update_document), e);
            status = false;
        }

        return status;
    }

    public boolean deleteCarteirinha(Carteirinha carteirinha) {
      long id = carteirinha.getId();
      String queryStr = context.getString(R.string.delete_carteirinha_query) + id + ";";
      boolean status = true;

      try {
          SQLiteStatement statement = db.compileStatement(queryStr);
          statement.execute();
          Document doc = dao.readDcoumentById(((int)id));
          status = dao.deleteDocument(doc);
      } catch (SQLiteException e) {
          Log.e(LOGTAG, context.getString(R.string.failed_insert_user), e);
          status = false;
      }

      return status;
    }
}
