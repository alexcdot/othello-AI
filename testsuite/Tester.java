// Adapted from TestGame
public class Tester {
    public static void main(String[] args) {
        int games = Integer.parseInt(args[0]);
        String[] gameArgs = new String[args.length - 1];
        for (int i = 0; i < gameArgs.length; i++) {
            gameArgs[i] = args[i + 1];
        }
        Tester tester = new Tester(gameArgs);
        for (int i = 0; i < games; i++) {
            tester.playGame();
        }
        System.out.println(tester.counter);
    }

    public Tester(String[] args) {
        counter = new Counter();
        this.args = args;
    }

    private String[] args;
    private Counter counter;

    public void playGame() {
        if (args.length != 2 && args.length != 3) {
            // Wrong number of arguments; print usage string.
            String s
                = "\nUsage: Tester BLACK WHITE [TIMELIMIT]\n"
                + "  BLACK/WHITE - c++ program name or:\n"
                + "    SimplePlayer, ConstantTimePlayer, BetterPlayer - AIs\n"
                + "    Human - manual input\n"
                + "  TIMELIMIT - optional timelimit for each player in milliseconds:\n";                           
            System.out.println(s);
            System.exit(-1);
        }
        
        // Initialize the players.
        int which = 1;
        OthelloPlayer[] players = new OthelloPlayer[2];
        for (int i = 0; i < 2; i++) {
            if (args[i].equalsIgnoreCase("SimplePlayer")) {
                players[i] = new SimplePlayer();
            } else if (args[i].equalsIgnoreCase("ConstantTimePlayer")) {
                players[i] = new ConstantTimePlayer();
            } else if (args[i].equalsIgnoreCase("BetterPlayer")) {
                players[i] = new BetterPlayer();
            } else if (args[i].equalsIgnoreCase("Human")) {
                players[i] = new OthelloDisplay(which++);
            } else {
                players[i] = new WrapperPlayer(args[i]);
            }             
        }
        
        // Start the game.
        OthelloGame g = null;
        if (args.length == 2) {
            // No timeout arg given; use unlimited time.
            g = new OthelloGame(players[0], players[1], counter);
        } else {
            // Parse timeout arg.       
            try {
                long timeout = Integer.parseInt(args[2]);        
                g = new OthelloGame(players[0], players[1], counter, timeout);                            
            } catch (Exception e) {
                System.out.println("Error: Could not parse integer from '" + args[2] + "'");
                System.exit(-1);
            }
        }
        System.out.println("Starting game");
        g.run();
    }
}
