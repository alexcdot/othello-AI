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

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("Black wins:    ");
    sb.append(blackWins);
    sb.append('\n');
    sb.append("White wins:    ");
    sb.append(whiteWins);
    sb.append('\n');
    sb.append("Ties:          ");
    sb.append(ties);
    sb.append('\n');
    sb.append("White error:   ");
    sb.append(whiteErrs);
    sb.append('\n');
    sb.append("Black error:   ");
    sb.append(blackErrs);
    sb.append('\n');
    sb.append("Server error:  ");
    sb.append(serverErrs);
    sb.append('\n');
    return sb.toString();
  }
}
