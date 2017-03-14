public class Counter implements OthelloObserver {
  private int blackWins = 0;
  private int whiteWins = 0;
  private int blackErrs = 0;
  private int whiteErrs = 0;
  private int serverErrs = 0;
  private int ties = 0;

  public void OnMove(Move m, long black, long white) {
  }

  public void OnGameOver(OthelloResult result) {
    if (result.conclusion == OthelloResult.NORMAL_CONCLUSION) {
      OthelloSide winner = result.getWinner();
      if (winner == OthelloSide.BLACK) {
        blackWins++;
      } else if (winner == OthelloSide.WHITE) {
        whiteWins++;
      } else {
        ties++;
      }
    } else if (result.conclusion == OthelloResult.BLACK_ERROR_CONCLUSION) {
      blackErrs++;
    } else if (result.conclusion == OthelloResult.WHITE_ERROR_CONCLUSION) {
      whiteErrs++;
    } else {
      serverErrs++;
    }
  }

  public int getBlackWins() {
    return blackWins;
  }

  public int getWhiteWins() {
    return whiteWins;
  }

  public int getTies() {
    return ties;
  }

  public int getBlackErrors() {
    return blackErrs;
  }

  public int getWhiteErrors() {
    return whiteErrs;
  }

  public int getServerErrors() {
    return serverErrs;
  }
}
