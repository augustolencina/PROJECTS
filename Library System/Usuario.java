package gestionLibros;

public abstract class Usuario {
    protected String nombre;
    protected String apellido;
    protected String email;
    protected String password;
    protected String estado;
    protected String tipo;

    public Usuario(String nombre, String apellido, String email, String password, String estado, String tipo) {
        this.nombre = nombre;
        this.apellido = apellido;
        this.email = email;
        this.password = password;
        this.estado = estado;
        this.tipo = tipo;
    }

    public String getNombre() {
    	return nombre;
    }
    public void setNombre(String nombre) {
    	this.nombre = nombre;
    }
    
    public String getApellido() {
    	return apellido;
    }
    public void setApellido(String apellido) {
    	this.apellido = apellido;
    }
    
    public String getEmail() {
    	return email;
    }
    public void setEmail(String email) {
    	this.email = email;
    }
    
    public String getPassword() {
    	return password;
    }
    public void setPassword(String password) {
    	this.password = password;
    }
    
    public String getEstado() {
    	return estado;
    }
    public void setEstado(String estado) {
    	this.estado = estado;
    }
    
    public String getTipo() {
    	return tipo;
    }
    public void setTipo(String tipo) {
    	this.tipo = tipo;
    }
}