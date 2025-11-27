package gestionLibros;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class PanelUsuario extends JFrame implements ActionListener {
    private Biblioteca biblioteca;
    private Usuario usuario;

    private JPanel panelBotones;

    private JButton consultarBtn;
    private JButton solicitarBtn;
    private JButton devolverBtn;
    private JButton volverBtn;

    public PanelUsuario(Biblioteca biblioteca, Usuario usuario) {
        this.biblioteca = biblioteca;
        this.usuario = usuario;

        setTitle("Libreria");
        setSize(400, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        gui();
    }
    
    public Usuario getUsuario() {
        return usuario;
    }

    private void gui() {
        panelBotones = new JPanel();
        panelBotones.setLayout(new GridLayout(4, 1, 10, 10));

        consultarBtn = new JButton("Consultar Libros Disponibles");
        solicitarBtn = new JButton("Solicitar Préstamo");
        devolverBtn = new JButton("Devolver Libro");
        volverBtn = new JButton("Volver");

        consultarBtn.setActionCommand("CONSULTAR");
        solicitarBtn.setActionCommand("SOLICITAR");
        devolverBtn.setActionCommand("DEVOLVER");
        volverBtn.setActionCommand("VOLVER");

        consultarBtn.addActionListener(this);
        solicitarBtn.addActionListener(this);
        devolverBtn.addActionListener(this);
        volverBtn.addActionListener(this);

        panelBotones.add(consultarBtn);
        panelBotones.add(solicitarBtn);
        panelBotones.add(devolverBtn);
        panelBotones.add(volverBtn);

        add(panelBotones);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        if (comando.equals("CONSULTAR")) {
            String[] disponibles = biblioteca.getGestorLibros().getTitulosLibrosDisponibles();
            JOptionPane.showMessageDialog(this, new JList<>(disponibles), "Libros disponibles", JOptionPane.PLAIN_MESSAGE);

        } else if (comando.equals("SOLICITAR")) {
        	if (usuario.getEstado().equals("Inactivo")) {
                JOptionPane.showMessageDialog(this, "Ya tenés un prestamo activo.");
                return;
            }
            new PanelSolicitarPrestamo(biblioteca, this).setVisible(true);

        } else if (comando.equals("DEVOLVER")) {
        	if (usuario.getEstado().equals("Inactivo")) {
        		Libro libroA_Devolver = null;
                boolean encontrado = false;
                int i = 0;
                ArrayList<Libro> todosLosLibros = biblioteca.getGestorLibros().getLibros();

                while (i < todosLosLibros.size() && !encontrado) {
                    Libro l = todosLosLibros.get(i);
                    Usuario u = biblioteca.obtenerUsuarioQueTieneElLibro(l);
                    
                    if (u != null && u.getEmail().equals(usuario.getEmail())) {
                        libroA_Devolver = l;
                        encontrado = true;
                    }
                    i++;
                }

                if (encontrado) {
                    libroA_Devolver.setEstado("Disponible");
                    usuario.setEstado("Activo");
                    biblioteca.eliminarPrestamo(libroA_Devolver);
                    JOptionPane.showMessageDialog(this, "Devolucion realizada con exito.");
                } else {
                     usuario.setEstado("Activo");
                     JOptionPane.showMessageDialog(this, "No se encontró registro de libro, estado corregido.");
                }
            } else {
                JOptionPane.showMessageDialog(this, "No tenes un prestamo activo.");
            }
      
        } else if (comando.equals("VOLVER")) {
            PanelLogin login = new PanelLogin();
            login.setBiblioteca(biblioteca);
            login.setVisible(true);
            this.dispose();
        }
    }
}
