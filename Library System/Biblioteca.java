package gestionLibros;

import java.util.ArrayList;

public class Biblioteca {
    private GestorUsuarios gestorUsuarios;
    private GestorLibros gestorLibros;
    private ArrayList<Prestamo> prestamosActivos;

    public Biblioteca() {
        gestorUsuarios = new GestorUsuarios();
        gestorLibros = new GestorLibros();
        prestamosActivos = new ArrayList<>();
    }

    public GestorUsuarios getGestorUsuarios() {
        return gestorUsuarios;
    }

    public GestorLibros getGestorLibros() {
        return gestorLibros;
    }
    
    public void registrarPrestamo(Usuario usuario, Libro libro) {
        Prestamo nuevo = new Prestamo(usuario, libro);
        prestamosActivos.add(nuevo);
    }

    public Usuario obtenerUsuarioQueTieneElLibro(Libro libro) {
        Usuario usuarioEncontrado = null;
        int i = 0;
        
        while (i < prestamosActivos.size() && usuarioEncontrado == null) {
            Prestamo p = prestamosActivos.get(i);
            if (p.getLibro().getIsbn().equals(libro.getIsbn())) {
                usuarioEncontrado = p.getUsuario();
            }
            i++;
        }
        return usuarioEncontrado;
    }

    public void eliminarPrestamo(Libro libro) {
        boolean eliminado = false;
        int i = 0;
        
        while (i < prestamosActivos.size() && !eliminado) {
            if (prestamosActivos.get(i).getLibro().getIsbn().equals(libro.getIsbn())) {
                prestamosActivos.remove(i);
                eliminado = true;
            }
            i++;
        }
    }
}
