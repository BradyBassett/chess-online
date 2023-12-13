class Piece {
  protected hasMoved: boolean = false;
  protected isCaptured: boolean = false;

  constructor(
    public x: number,
    public y: number,
    public color: string,
  ) {
    this.x = x;
    this.y = y;
    this.color = color;
  }

  public move(x: number, y: number) {
    this.x = x;
    this.y = y;
    if (!this.hasMoved) this.hasMoved = true;
  }

  public capture() {
    this.isCaptured = true;
  }
}