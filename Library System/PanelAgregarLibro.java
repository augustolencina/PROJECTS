package gestionLibros;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PanelAgregarLibro extends JFrame implements ActionListener {
    private Biblioteca biblioteca;
    private PanelBibliotecario panelPadre;
    private JTextField isbn, titulo, autor, edicion, estado;
    private JButton guardarBtn;

    public PanelAgregarLibro(Biblioteca biblioteca, PanelBibliotecario padre) {
        this.biblioteca = biblioteca;
        this.panelPadre = padre;

        setTitle("Agregar Libro");
        setSize(300, 250);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(DISPOSE_ON_CLOSE);

        gui();
    }

    private void gui() {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2));

        panel.add(new JLabel("ISBN:"));
        isbn = new JTextField();
        panel.add(isbn);

        panel.add(new JLabel("Titulo:"));
        titulo = new JTextField();
        panel.add(titulo);

        panel.add(new JLabel("Autor:"));
        autor = new JTextField();
        panel.add(autor);

        panel.add(new JLabel("Edicion:"));
        edicion = new JTextField();
        panel.add(edicion);

        panel.add(new JLabel("Estado:"));
        estado = new JTextField("Disponible");
        panel.add(estado);

        guardarBtn = new JButton("Guardar");
        guardarBtn.setActionCommand("GUARDAR_LIBRO");
        guardarBtn.addActionListener(this);

        panel.add(new JLabel());
        panel.add(guardarBtn);

        add(panel);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        if (comando.equals("GUARDAR_LIBRO")) {
            Libro nuevo = new Libro(
                    isbn.getText(),
                    titulo.getText(),
                    autor.getText(),
                    edicion.getText(),
                    estado.getText()
            );
            
            boolean sePudoAgregar = biblioteca.getGestorLibros().agregarLibro(nuevo);

            if (sePudoAgregar) {
                panelPadre.actualizarListaLibros();
                dispose();
            } else {
                JOptionPane.showMessageDialog(this, "Error: Se alcanzó el límite de 10 libros nuevos permitidos.");
            }
        }
    }
}
