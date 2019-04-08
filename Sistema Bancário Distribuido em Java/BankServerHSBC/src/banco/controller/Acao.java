package banco.controller;

import banco.Request;
import banco.Response;


public interface Acao {
    public Response executa(Request req) throws Exception;
}
