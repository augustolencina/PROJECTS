package gestionLibros;

public class Libro {
	String isbn;
	String titulo;
	String autor;
	String edicion;
	String estado;
	
	public Libro(String isbn, String titulo, String autor, String edicion, String estado) {
		this.isbn = isbn;
        this.titulo = titulo;
        this.autor = autor;
        this.edicion = edicion;
        this.estado = estado;
	}
	
    public String getIsbn() {
		return isbn;
	}
    public void setIsbn(String isbn) {
    	this.isbn = isbn;
    }

	public String getTitulo() {
		return titulo;
	}
	public void setTitulo(String titulo) {
    	this.titulo = titulo;
    }

	public String getAutor() {
		return autor;
	}
	public void setAutor(String autor) {
    	this.autor = autor;
    }

	public String getEdicion() {
		return edicion;
	}
	public void setEdicion(String edicion) {
    	this.edicion = edicion;
    }

	public String getEstado() {
		return estado;
	}
	public void setEstado(String estado) {
    	this.estado = estado;
    }

}
