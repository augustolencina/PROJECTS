package gestionLibros;

import java.util.ArrayList;

public class GestorLibros {
    private ArrayList<Libro> libros;
    private int contadorLibrosAgregados;

    public GestorLibros() {
        libros = new ArrayList<>();
        
        libros.add(new Libro("0000000000001", "Cien años de soledad", "Gabriel Garcia Marquez", "1ra", "Disponible"));
        libros.add(new Libro("0000000000002", "1984", "George Orwell", "2da", "Disponible"));
        libros.add(new Libro("0000000000003", "El Principito", "Antoine de Saint-Exupery", "3ra", "Disponible"));
        libros.add(new Libro("0000000000004", "Rayuela", "Julio Cortazar", "1ra", "Disponible"));
        libros.add(new Libro("0000000000005", "Don Quijote de la Mancha", "Miguel de Cervantes", "4ta", "Disponible"));
        libros.add(new Libro("0000000000006", "Crimen y castigo", "Fiodor Dostoyevski", "2da", "Disponible"));
        libros.add(new Libro("0000000000007", "Fahrenheit 451", "Ray Bradbury", "1ra", "Disponible"));
        libros.add(new Libro("0000000000008", "El Hobbit", "J.R.R. Tolkien", "3ra", "Disponible"));
        libros.add(new Libro("0000000000009", "Orgullo y prejuicio", "Jane Austen", "5ta", "Disponible"));
        libros.add(new Libro("0000000000010", "La Odisea", "Homero", "6ta", "Disponible"));
    }

    public ArrayList<Libro> getLibros() {
        return libros;
    }

    public boolean agregarLibro(Libro libro) {
    	if (contadorLibrosAgregados < 10) {
            libros.add(libro);
            contadorLibrosAgregados++;
            return true;
        } else {
            return false;
        }
    }
    
    public String[] getTitulosConEstado() {
        String[] titulos = new String[libros.size()];
        for (int i = 0; i < libros.size(); i++) {
            Libro l = libros.get(i);
            titulos[i] = l.getTitulo() + " - " + l.getEstado();
        }
        return titulos;
    }
    
    public String[] getTitulosLibrosDisponibles() {
        ArrayList<String> disponibles = new ArrayList<>();

        for (Libro l : libros) {
            if (l.getEstado().equalsIgnoreCase("Disponible")) {
                disponibles.add(l.getTitulo());
            }
        }

        return disponibles.toArray(new String[0]);
    }
    
    public Libro buscarPorTitulo(String titulo) {
        for (Libro l : libros) {
            if (l.getTitulo().equals(titulo)) {
                return l;
            }
        }
        return null;
    }
    
    public boolean tienePrestamoActivo() {
        for (Libro l : getLibros()) {
            if (l.getEstado().equals("Prestado")) {
                return true;
            }
        }
        return false;
    }
}
