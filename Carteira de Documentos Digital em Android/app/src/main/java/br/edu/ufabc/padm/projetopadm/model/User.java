package br.edu.ufabc.padm.projetopadm.model;

/**
 * Created by Camila Sass on 15/11/2016.
 */

public class User {
    private Long id;
    private String name;
    private String email;
    private String user;
    private String password;
    private String confirmPassword;

    public User(){
        name = null;
        email = null;
        user = null;
        password = null;
        confirmPassword = null;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getConfirmPassword() {
        return confirmPassword;
    }

    public void setConfirmPassword(String confirmPassword) {
        this.confirmPassword = confirmPassword;
    }
}
