/**
 * Got it from math.hws.edu/javanotes/source/Checkers.java
 *
 * Original author:  David J. Eck  (eck@hws.edu)
 *
 * Main entry point.
 */

import java.awt.*;
import javax.swing.*;

class Checkers extends JPanel {
    private BoardPanel boardPanel;

    public static void main(String[] args) {
        JFrame window = new JFrame("Checkers");
        Checkers content = new Checkers();
        window.setContentPane(content);
        window.pack();
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        window.setLocation((screenSize.width - window.getWidth()) / 2, (screenSize.height - window.getHeight()) / 2);
        window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        window.setResizable(false);
        window.setVisible(true);

        /* Run the game loop */
        content.runGame();

        /* We are all done */
        System.exit(0);
    }

    private Checkers() {
        setLayout(null);
        setPreferredSize(new Dimension(324, 324));
        setBackground(new Color(160, 160, 160));

        /* Create the components and add them to the applet. */
        boardPanel = new BoardPanel();
        add(boardPanel);

        /* Set the position and size of each component by calling its setBounds() method */
        boardPanel.setBounds(0, 0, 324, 324);
    }

    private void runGame(){
        if (boardPanel != null) {
            boardPanel.runGame();
        }
    }

}