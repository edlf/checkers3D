import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.lang.reflect.Array;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Vector;

/**
 * This panel displays a 160-by-160 checkerboard pattern with
 * a 2-pixel black border.  It is assumed that the size of the
 * panel is set to exactly 164-by-164 pixels.  This class does
 * the work of letting the users play checkers, and it displays
 * the checkerboard.
 */

/**
 * Status List
 * 1x Whites
 * 2x Blacks
 * 3x Server/Client interactions (save, load game state)
 *
 * 10   : Ready, regular move
 * 11   : Ready, forced move
 * 19   : Victory
 *
 * 20   : Ready, regular move
 * 21   : Ready; forced move
 * 29   : Victory
 *
 * 30   : Load game state
 * 31   : Send game state
 *
 * -1   : The game has ended (new game can be asked)
 * -2   : Exit
 * -999 : Dead state (Error)
 */

public class BoardPanel extends JPanel {
    /* Sockets */
    private int portNumber = 1200;

    /* Game Logic */
    private int state;
    Board board;
    Vector<Board> boardVector = new Vector<>();
    boolean gameInProgress;
    boolean canRedo, mustErase;
    int vectorPos;

    /* The next three variables are valid only when the game is in progress. */
    /* Board.WHITE (1) and Board.BLACK (3) */
    int currentPlayer;

    /* Current selection */
    int selectedRow, selectedCol;

    /* An array containing the legal moves for the current player */
    CheckersMove[] legalMoves;

    BoardPanel() {
        canRedo = false;
        setBackground(Color.BLACK);
        boardVector.clear();
        board = new Board();
        boardVector.add(board);
        doNewGame();
    }

    public void runGame(){
        /* Server loop */
        while (true) {
            /* Reset game */
            resetGame();

            System.out.println(" > Creating server on port " + Integer.toString(portNumber));
            serverGameLoop();
            System.out.println(" > Server job is done");

        }

    }

    /* Communication is processed here */
    String processInput(String input){
        /* Split input */
        String[] commandArray = input.split("&&");
        int numberOfCommands = Array.getLength(commandArray);

        if (numberOfCommands < 1) {
            return "NO_COMMAND_SENT.";
        }

        /* Status indifferent commands here */
        if (commandArray[0].equals("HELLO.") && numberOfCommands == 1) {
            return "MINE_TURTLE.";
        }

        if (commandArray[0].equals("ISGAMEON.") && numberOfCommands == 1) {
            if (gameInProgress) {
                return "YES.";
            } else {
                return "NO.";
            }
        }

        /* Reset received */
        if (commandArray[0].equals("RESET.") && numberOfCommands == 1) {
            resetGame();
            return "RESET:OK.";
        }

        /* Send the current board */
        if (commandArray[0].equals("GET_BOARD.") && numberOfCommands == 1){
            return encodeBoard();
        }

        /* Load previous game state */
        if (commandArray[0].equals("LOAD_GAME_STATE.") && numberOfCommands == 2){
            decodeBoard(commandArray[1]);
            legalMoves = board.getLegalMoves(currentPlayer);
            return "LOAD_GAME_STATE_ON.";
        }

        /* Send current game state */
        if (commandArray[0].equals("GET_CURRENT_STATE.")){
            return "NOT_IMPLEMENTED.";
        }

        /* Get current piece highlight positions */
        if (commandArray[0].equals("GET_PIECE_HIGHLIGHT.")){
            return encodeValidMovesHighlights();
        }

        /* Get current destination highlight positions */
        if (commandArray[0].equals("GET_SEL_MOVES_HIGHLIGHT.")){
            return encodeValidDestinationsHighlights();
        }

        /* Get current selected piece */
        if (commandArray[0].equals("GET_SELECTED.")){
            return encodeCurrentSelected();
        }


    if (!gameInProgress){
        if (commandArray[0].equals("MOVIE.") && numberOfCommands == 1){
            board = boardVector.get(0);
            vectorPos = 0;
            repaint();
            return "MOVIE:OK.";
        }

        if (commandArray[0].equals("MOVIE_NEXT.") && numberOfCommands == 1){
            vectorPos++;
            if(vectorPos <= boardVector.size()) {
                board = boardVector.get(vectorPos);
            }
            repaint();
            return "MOVIE:OK.";
        }
    }
        /* No more status indifferent commands bellow */


        /* Ready */
        if (state == 0) {
            if (commandArray[0].equals("EXIT.") && numberOfCommands == 1){
                state = -2;
                return "EXIT:OK.";
            }

            if(commandArray[0].equals("GET_VALID_MOVES.")) {
                return getCurrentPlayerValidMoves();
            }

            if(commandArray[0].equals("SELECT_SQUARE.") && numberOfCommands == 2) {
                String[] tempIn = commandArray[1].split(";");

                char tempCX = tempIn[0].charAt(0);
                int tempX = Character.getNumericValue(tempCX);

                char tempCY = tempIn[1].charAt(0);
                int tempY = Character.getNumericValue(tempCY);

                doClickSquare(tempX - 1, tempY - 1);
                return "OK.";
            }

            if (commandArray[0].equals("UNDO.") && numberOfCommands == 1){
                if (boardVector.size() >= 2) {
                    mustErase = true;
                    swapPlayer();
                    /* Go back one */
                    vectorPos = boardVector.size() - 1;

                    //boardVector.remove(board);

                    /* Set current board as the old one */
                    board = boardVector.get(vectorPos);

                    /* Enable Redo */
                    canRedo = true;
                    return "UNDO:OK.";

                } else {
                    return "UNDO:FAIL.";
                }
            }

            if (commandArray[0].equals("REDO.") && numberOfCommands == 1){
                if (canRedo && vectorPos < boardVector.size()) {
                    swapPlayer();
                    vectorPos++;
                    board = boardVector.get(vectorPos);
                    repaint();
                    return "REDO:OK.";

                } else {
                    return "REDO:FAIL.";
                }
            }

            if (commandArray[0].equals("FORFEIT.") && numberOfCommands == 1){
                swapPlayer();
                return "FORFEIT:OK.";
            }

            if (commandArray[0].equals("TIMEUP.") && numberOfCommands == 1){
                gameOver();
                return "TIMEUP:OK.";
            }
        }

        /* The game has ended */
        if (state == -1) {
            return "THE_GAME_HAS_ALREADY_ENDED.";
        }

        if (state == -999) {
            /* Server is already in a dead state. Kill it */
            System.out.println("Server is in a dead state, exiting..");
            System.exit(-1);
        }

        return "INVALID_COMMAND.";
    }

    private void swapPlayer(){
        if (currentPlayer == Board.WHITE) {
            currentPlayer = Board.BLACK;
        } else {
            currentPlayer = Board.WHITE;
        }

        legalMoves = board.getLegalMoves(currentPlayer);
    }

    private void resetGame(){
        canRedo = false;
        gameOver();

        /* Reset game */
        state = 0;
        boardVector.clear();
        board = new Board();
        boardVector.add(board);
        currentPlayer = 1;
        doNewGame();
    }
    /**
     * Encodes the board in a string for the client to read.
     *
     * Example response:
     *
     * 30303030;03030303;30303030;00000000;00000000;01010101;10101010;01010101;.
     *
     */
    private String encodeBoard() {
        int temp [][] = board.getBoard();
        String encodedBoard = "";

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (temp[row][col] > 9 || temp[row][col] < 0) {
                    System.out.println("BUG: Bad value in board.");
                    System.exit(-1);
                }
                encodedBoard+=Integer.toString(temp[row][col]);
            }
            encodedBoard+=";";
        }
        encodedBoard+=Integer.toString(currentPlayer);
        encodedBoard+=";";
        encodedBoard+=".";

        return encodedBoard;
    }

    /**
     * Encodes current highlighted squares.
     * Avoids consecutive duplicated highlights.
     * */
    private String encodeValidMovesHighlights() {
        String encodedBoardHighlights = "";
        int tempRow = -1, tempCol = -1;

        for (CheckersMove legalMove : legalMoves) {

            if (((tempRow != legalMove.fromRow) || (tempCol != legalMove.fromCol))) {
                /* Keep last values to avoid duplicated entries */
                tempRow = legalMove.fromRow;
                tempCol = legalMove.fromCol;

                encodedBoardHighlights+=legalMove.fromRow;
                encodedBoardHighlights+=legalMove.fromCol;
                encodedBoardHighlights+=";";
            }

        }

        encodedBoardHighlights+=".";

        return encodedBoardHighlights;
    }

    private String encodeValidDestinationsHighlights(){
        String encodedBoardHighlights = "";

        for (CheckersMove legalMove : legalMoves) {

            if (((selectedRow == legalMove.fromRow) && (selectedCol == legalMove.fromCol))) {

                encodedBoardHighlights+=legalMove.toRow;
                encodedBoardHighlights+=legalMove.toCol;
                encodedBoardHighlights+=";";
            }

        }

        encodedBoardHighlights+=".";
        return encodedBoardHighlights;
    }

    private String encodeCurrentSelected(){
        String encodedBoardHighlights = "";
        encodedBoardHighlights+=selectedRow;
        encodedBoardHighlights+=selectedCol;
        encodedBoardHighlights+=";.";

        return encodedBoardHighlights;
    }
    /**
     * Decodes an board from a string.
     *
     * It's encoded like the encodeBoard method.
     */
    private void decodeBoard(String input) {
        /* boardRowString contains each board line */
        String[] boardRowString = input.split(";");

        int temp[][] = new int[8][8];

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                char currentChar = boardRowString[row].charAt(col);
                temp[row][col] = Character.getNumericValue(currentChar);

                if (temp[row][col] > 9 || temp[row][col] < 0) {
                    System.out.println("Bad value fed to board, check client.");
                    System.exit(-1);
                }

            }

        }

        char currentChar = boardRowString[8].charAt(0);
        currentPlayer = Character.getNumericValue(currentChar);

        board.receiveBoard(temp);
    }

    /* Returns a string with current player valid moves */
    private String getCurrentPlayerValidMoves() {
        String response = "VALID_MOVES:";

        for (CheckersMove legalMove1 : legalMoves) {
            response = response + "COL:" + Integer.toString(legalMove1.fromCol + 1) + "ROW:" + Integer.toString(legalMove1.fromRow + 1) + ";";
        }

        response = response + ".";

        return response;
    }

    /**
     * The server game loop, while the sockets connection is open
     * it will send the input to the processInput method for further processing
     */
    void serverGameLoop() {
        try (ServerSocket serverSocket = new ServerSocket(portNumber);
             Socket clientSocket = serverSocket.accept();
             PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));) {

            String inputLine, outputLine;

            /* Wait for input */
            while ((inputLine = in.readLine()) != null) {
                /* Show the input (DEBUG) */
                System.out.println("Input: " + inputLine);
                /* Process the input */
                outputLine = processInput(inputLine);
                /* Print the response (DEBUG) */
                System.out.println("Response: " + outputLine);
                /* Send the response */
                out.println(outputLine);

                /* End game */
                if (state == -2) {
                    break;
                }
                /* Call repaint to update the gui */
                repaint();
            }
        } catch (IOException e) {
            System.out.println("Error with sockets: ");
            e.printStackTrace();
        }
    }

    /**
     * Start a new game
     */
    void doNewGame() {
        if (gameInProgress) {
            /* This should not be possible, but it doesn't hurt to check. */
            return;
        }

        board.setUpGame();   // Set up the pieces.
        currentPlayer = Board.WHITE;   // WHITE moves first.
        legalMoves = board.getLegalMoves(currentPlayer);  // Get WHITE's legal moves.
        selectedRow = 9;   // WHITE has not yet selected a piece to move.
        selectedCol = 9;
        gameInProgress = true;
        repaint();
    }

    /**
     * The game ends.  The parameter, str, is displayed as a message
     * to the user.  The states of the buttons are adjusted so players
     * can start a new game.  This method is called when the game
     * ends at any point in this class.
     */
    void gameOver() {
        gameInProgress = false;
    }

    /**
     * This is called by mousePressed() when a player clicks on the
     * square in the specified row and col.  It has already been checked
     * that a game is, in fact, in progress.
     */
    void doClickSquare(int row, int col) {

        /** If the player clicked on one of the pieces that the player
         * can move, mark this row and col as selected and return.  (This
         * might change a previous selection.)  Reset the message, in
         * case it was previously displaying an error message. */

        if (gameInProgress){
        for (CheckersMove legalMove : legalMoves)
            if (legalMove.fromRow == row && legalMove.fromCol == col) {
                selectedRow = row;
                selectedCol = col;
                if (currentPlayer == Board.WHITE) {
                    //message.setText("WHITE:  Make your move.");
                } else {
                    //message.setText("BLACK:  Make your move.");
                }
                repaint();
                return;
            }


         /** If no piece has been selected to be moved, the user must first
          * select a piece.  Show an error message and return. */

        if (selectedRow < 0) {
            return;
        }

         /* If the user clicked on a square where the selected piece can be
          legally moved, then make the move and return. */

        for (CheckersMove legalMove : legalMoves)
            if (legalMove.fromRow == selectedRow && legalMove.fromCol == selectedCol
                    && legalMove.toRow == row && legalMove.toCol == col) {
                doMakeMove(legalMove);
                boardVector.add(board);
                vectorPos = boardVector.size();
                System.out.println(boardVector.size());
                return;
            }

        }

         /* If we get to this point, there is a piece selected, and the square where
          the user just clicked is not one where that piece can be legally moved.
          Show an error message. */

        //selectedCol = -1;
        //selectedRow = -1;
    }

    /**
     * This is called when the current player has chosen the specified
     * move.  Make the move, and then either end or continue the game
     * appropriately.
     */
    void doMakeMove(CheckersMove move) {

        board.makeMove(move);

         /* If the move was a jump, it's possible that the player has another
          * jump.  Check for legal jumps starting from the square that the player
          * just moved to.  If there are any, the player must jump.  The same
          * player continues moving.
          */

        if (move.isJump()) {
            legalMoves = board.getLegalJumpsFrom(currentPlayer, move.toRow, move.toCol);
            if (legalMoves != null) {
                if (currentPlayer == Board.WHITE) {
                    //message.setText("WHITE:  You must continue jumping.");
                } else {
                    //message.setText("BLACK:  You must continue jumping.");
                }

                selectedRow = move.toRow;  // Since only one piece can be moved, select it.
                selectedCol = move.toCol;
                repaint();
                return;
            }
        }

         /* The current player's turn is ended, so change to the other player.
          Get that player's legal moves.  If the player has no legal moves,
          then the game ends. */

        if (currentPlayer == Board.WHITE) {
            currentPlayer = Board.BLACK;
            legalMoves = board.getLegalMoves(currentPlayer);
            if (legalMoves == null)
                //"BLACK has no moves.  WHITE wins."
                gameOver();
            else if (legalMoves[0].isJump()) {
                //message.setText("BLACK:  Make your move.  You must jump.");
            }
            else {
                //message.setText("BLACK:  Make your move.");
            }
        } else {
            currentPlayer = Board.WHITE;
            legalMoves = board.getLegalMoves(currentPlayer);
            if (legalMoves == null)
                //"WHITE has no moves.  BLACK wins."
                gameOver();
            else if (legalMoves[0].isJump()) {
                //message.setText("WHITE:  Make your move.  You must jump.");
            } else{
                //message.setText("WHITE:  Make your move.");
            }
        }

         /* Set selectedRow = -1 to record that the player has not yet selected
          a piece to move. */

        selectedRow = -1;

         /* As a courtesy to the user, if all legal moves use the same piece, then
          select that piece automatically so the user won't have to click on it
          to select it. */

        if (legalMoves != null) {
            boolean sameStartSquare = true;
            for (int i = 1; i < legalMoves.length; i++)
                if (legalMoves[i].fromRow != legalMoves[0].fromRow
                        || legalMoves[i].fromCol != legalMoves[0].fromCol) {
                    sameStartSquare = false;
                    break;
                }
            if (sameStartSquare) {
                selectedRow = legalMoves[0].fromRow;
                selectedCol = legalMoves[0].fromCol;
            }
        }

         /* Make sure the board is redrawn in its new state. */
        repaint();
    }

    /**
     * Draw a checkerboard pattern in gray and lightGray.  Draw the
     * checkers.  If a game is in progress, highlight the legal moves.
     */
    public void paintComponent(Graphics g) {

        /* Draw a two-pixel black border around the edges of the canvas. */
        g.setColor(Color.black);
        g.drawRect(0, 0, getSize().width - 1, getSize().height - 1);
        g.drawRect(1, 1, getSize().width - 3, getSize().height - 3);

        /* Draw the squares of the checkerboard and the checkers. */
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {

                /* Background */
                if (row % 2 == col % 2) {
                    g.setColor(Color.LIGHT_GRAY);
                } else {
                    g.setColor(Color.DARK_GRAY);
                }
                g.fillRect(2 + col * 40, 2 + row * 40, 40, 40);

                /* Pieces */
                switch (board.pieceAt(row, col)) {
                    case Board.WHITE:
                        g.setColor(Color.WHITE);
                        g.fillOval(4 + col * 40, 4 + row * 40, 35, 35);
                        break;

                    case Board.BLACK:
                        g.setColor(Color.BLACK);
                        g.fillOval(4 + col * 40, 4 + row * 40, 35, 35);
                        break;

                    case Board.WHITE_KING:
                        g.setColor(Color.WHITE);
                        g.fillOval(4 + col * 40, 4 + row * 40, 35, 35);
                        g.setColor(Color.RED);
                        g.drawString("K", 15 + col * 40, 32 + row * 40);
                        break;

                    case Board.BLACK_KING:
                        g.setColor(Color.BLACK);
                        g.fillOval(4 + col * 40, 4 + row * 40, 35, 35);
                        g.setColor(Color.WHITE);
                        g.drawString("K", 13 + col * 40, 32 + row * 40);
                        break;
                }
            }
        }

        /**
         * If a game is in progress, highlight the legal moves.
         * Note that legalMoves is never null while a game is in progress.
         */
        if (gameInProgress) {
            /* First, draw a 2-pixel cyan border around the pieces that can be moved. */
            g.setColor(Color.cyan);
            for (CheckersMove legalMove1 : legalMoves) {
                g.drawRect(2 + legalMove1.fromCol * 40, 2 + legalMove1.fromRow * 40, 39, 39);
                g.drawRect(3 + legalMove1.fromCol * 40, 3 + legalMove1.fromRow * 40, 37, 37);
            }
            /* If a piece is selected for moving (i.e. if selectedRow >= 0), then
                draw a 2-pixel white border around that piece and draw green borders
                around each square that that piece can be moved to. */
            if (selectedRow >= 0) {
                g.setColor(Color.white);
                g.drawRect(2 + selectedCol * 40, 2 + selectedRow * 40, 39, 39);
                g.drawRect(3 + selectedCol * 40, 3 + selectedRow * 40, 37, 37);
                g.setColor(Color.green);
                for (CheckersMove legalMove : legalMoves) {
                    if (legalMove.fromCol == selectedCol && legalMove.fromRow == selectedRow) {
                        g.drawRect(2 + legalMove.toCol * 40, 2 + legalMove.toRow * 40, 39, 39);
                        g.drawRect(3 + legalMove.toCol * 40, 3 + legalMove.toRow * 40, 37, 37);
                    }
                }
            }
        }

    }
}
