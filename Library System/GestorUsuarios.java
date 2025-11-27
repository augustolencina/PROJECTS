package gestionLibros;

import java.util.ArrayList;

public class GestorUsuarios {
    private ArrayList<Usuario> usuarios;

    public GestorUsuarios() {
        usuarios = new ArrayList<>();
        
        usuarios.add(new UsuarioBibliotecario("Ana", "Gomez", "ana@libros.com", "Ana01234", "Activo", "Bibliotecario"));
        usuarios.add(new UsuarioBasico("Juan", "Perez", "juan@libros.com", "Juan6677", "Activo", "Usuario"));
        usuarios.add(new UsuarioBasico("Laura", "Diaz", "laura@libros.com", "Laura3245", "Activo", "Usuario"));
    }

    public Usuario login(String email, String password) {
        for (Usuario u : usuarios) {
            if (u.getEmail().equals(email) && u.getPassword().equals(password) && u.getEstado().equals("Activo")) {
                return u;
            }
        }
        return null;
    }

    public ArrayList<Usuario> getUsuarios() {
        return usuarios;
    }
    
}
