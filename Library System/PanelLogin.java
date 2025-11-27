package gestionLibros;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class PanelLogin extends JFrame implements ActionListener {
	JTextField usuario = new JTextField(20);
	JPasswordField pass = new JPasswordField(20);
	JLabel etiquetaUsuario = new JLabel ("Usuario: ");
	JLabel etiquetaContrasenia = new JLabel ("Contraseña: ");
	JButton ingresar = new JButton("Ingresar");
	JButton borrar = new JButton("Borrar");
	private Biblioteca biblioteca;
	
	public PanelLogin() {
		setTitle("Inicio de sesion");
		setSize(400, 150);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		biblioteca = new Biblioteca();
		
		gui();
	}
	
	public void setBiblioteca(Biblioteca biblioteca) {
        this.biblioteca = biblioteca;
    }
	
	private void gui() {
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(3, 2));
		panel.setBackground(Color.lightGray);
		this.getContentPane().add(panel);
		
		panel.add(etiquetaUsuario);
		panel.add(usuario);
		panel.add(etiquetaContrasenia);
		panel.add(pass);
		panel.add(ingresar);
		panel.add(borrar);
		
		ingresar.addActionListener(this);
		borrar.addActionListener(this);
		ingresar.setActionCommand("INGRESAR");
		borrar.setActionCommand("BORRAR");
	}
	
	@Override
    public void actionPerformed(ActionEvent e) {
        String comando = e.getActionCommand();

        if (comando.equals("INGRESAR")) {
        	String email = usuario.getText();
            String password = new String(pass.getPassword());
            String regexEmail = "^[A-Za-z0-9]+@[A-Za-z]+\\.[A-Za-z]{2,}$";
            String regexPassword = "^(?=.*[A-Z])(?=.*\\d).{8,}$";
            
            if (!email.matches(regexEmail)) {
                JOptionPane.showMessageDialog(this, "Email no valido");
                return;
            }

            if (!password.matches(regexPassword)) {
                JOptionPane.showMessageDialog(this, "Password invalida. Debe tener al menos 8 caracteres, una letra mayuscula y un numero.");
                return;
            }
            
            Usuario u = biblioteca.getGestorUsuarios().login(email, password);

            if (u != null) {
                if (u.getTipo().equals("Bibliotecario")) {
                    JOptionPane.showMessageDialog(this, "Bienvenido bibliotecario/a " + u.getNombre());
                    new PanelBibliotecario(biblioteca).setVisible(true);
                    this.dispose();
                } else {
                    JOptionPane.showMessageDialog(this, "Bienvenido usuario " + u.getNombre());
                    new PanelUsuario(biblioteca, u).setVisible(true);
                    this.dispose();
                } 
            } else {
                JOptionPane.showMessageDialog(this, "Usuario o password incorrectos");
            }
        }

        if (comando.equals("BORRAR")) {
            usuario.setText("");
            pass.setText("");
        }
    }
}