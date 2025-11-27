package gestionLibros;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PanelSolicitarPrestamo extends JFrame implements ActionListener {
    private Biblioteca biblioteca;
    private PanelUsuario panelPadre;

    private JList<String> listaLibros;
    private JScrollPane scroll;
    private JButton confirmarBtn;
    private JButton volverBtn;

    public PanelSolicitarPrestamo(Biblioteca biblioteca, PanelUsuario padre) {
        this.biblioteca = biblioteca;
        this.panelPadre = padre;

        setTitle("Solicitar Prestamo");
        setSize(400, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        gui();
        actualizarListaLibrosDisponibles();
    }

    private void gui() {
        setLayout(new BorderLayout());

        listaLibros = new JList<>();
        scroll = new JScrollPane(listaLibros);
        add(scroll, BorderLayout.CENTER);

        JPanel panelBotones = new JPanel();
        confirmarBtn = new JButton("Confirmar Prestamo");
        volverBtn = new JButton("Volver");

        confirmarBtn.setActionCommand("CONFIRMAR");
        volverBtn.setActionCommand("VOLVER");

        confirmarBtn.addActionListener(this);
        volverBtn.addActionListener(this);

        panelBotones.add(confirmarBtn);
        panelBotones.add(volverBtn);

        add(panelBotones, BorderLayout.SOUTH);
    }

    private void actualizarListaLibrosDisponibles() {
        listaLibros.setListData(biblioteca.getGestorLibros().getTitulosLibrosDisponibles());
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        if (comando.equals("CONFIRMAR")) {
            int index = listaLibros.getSelectedIndex();
            if (index == -1) {
                JOptionPane.showMessageDialog(this, "Seleccione un libro disponible.");
                return;
            }

            String titulo = listaLibros.getSelectedValue();
            Libro libro = biblioteca.getGestorLibros().buscarPorTitulo(titulo);

            if (libro != null && libro.getEstado().equals("Disponible")) {
                libro.setEstado("Prestado");
                panelPadre.getUsuario().setEstado("Inactivo");
                biblioteca.registrarPrestamo(panelPadre.getUsuario(), libro);
                JOptionPane.showMessageDialog(this, "Prestamo realizado con exito.");
                actualizarListaLibrosDisponibles();
                listaLibros.setEnabled(false);
                confirmarBtn.setEnabled(false);
            }

        } else if (comando.equals("VOLVER")) {
            this.dispose();
        }
    }
}