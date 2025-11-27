package gestionLibros;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PanelBibliotecario extends JFrame implements ActionListener {
	private Biblioteca biblioteca;
	private JList<String> listaLibros;
    private JButton cambiarEstadoBtn;
    private JButton agregarLibroBtn;
    private JButton volverBtn;
	
	public PanelBibliotecario(Biblioteca biblioteca) {
        this.biblioteca = biblioteca;

        setTitle("Gestion de libros");
        setSize(400, 300);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        gui();
        actualizarListaLibros();
    }
	
	private void gui() {
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());

        listaLibros = new JList<>();
        JScrollPane scroll = new JScrollPane(listaLibros);
        panel.add(scroll, BorderLayout.CENTER);

        JPanel panelBotones = new JPanel();
        cambiarEstadoBtn = new JButton("Cambiar Estado");
        agregarLibroBtn = new JButton("Agregar Libro");
        volverBtn = new JButton("Volver");

        cambiarEstadoBtn.setActionCommand("CAMBIAR_ESTADO");
        agregarLibroBtn.setActionCommand("AGREGAR_LIBRO");
        volverBtn.setActionCommand("VOLVER");
        
        cambiarEstadoBtn.addActionListener(this);
        agregarLibroBtn.addActionListener(this);
        volverBtn.addActionListener(this);

        panelBotones.add(cambiarEstadoBtn);
        panelBotones.add(agregarLibroBtn);
        panelBotones.add(volverBtn);

        panel.add(panelBotones, BorderLayout.SOUTH);

        this.add(panel);
    }
	
	public void actualizarListaLibros() {
	    listaLibros.setListData(biblioteca.getGestorLibros().getTitulosConEstado());
	}
	
	@Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        if (comando.equals("CAMBIAR_ESTADO")) {
            int index = listaLibros.getSelectedIndex();
            if (index != -1) {
            	Libro libro = biblioteca.getGestorLibros().getLibros().get(index);
            	String[] estados = { "Disponible", "No Disponible", "Prestado", "Reservado" };
            	String nuevoEstado = (String) JOptionPane.showInputDialog(this,
            	        "Seleccione el nuevo estado para " + libro.getTitulo(), "Cambiar estado",
            	        JOptionPane.PLAIN_MESSAGE, null, estados, libro.getEstado());
            	if (nuevoEstado != null) {
            		if (nuevoEstado.equals("Disponible")) {
                        Usuario usuarioDeudor = biblioteca.obtenerUsuarioQueTieneElLibro(libro);
                        
                        if (usuarioDeudor != null) {
                            usuarioDeudor.setEstado("Activo");
                            biblioteca.eliminarPrestamo(libro);
                        }
                    }
            	    libro.setEstado(nuevoEstado);
            	    actualizarListaLibros();
            	}
            } else {
                JOptionPane.showMessageDialog(this, "Seleccione un libro primero");
            }
        } else if (comando.equals("AGREGAR_LIBRO")) {
            new PanelAgregarLibro(biblioteca, this).setVisible(true);
        } else if (comando.equals("VOLVER")) {
        	PanelLogin login = new PanelLogin();
        	login.setBiblioteca(biblioteca);
        	login.setVisible(true);
        	this.dispose();
        }
    }
}
