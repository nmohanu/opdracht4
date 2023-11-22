// DERIVED FROM EXAMPLE FILE PROVIDED BY TEACHER
// file board.h
class Square {
  public:
    char color;
    Square* neighbours[8];
    Square* next;
    Square ( );
};

class Board {
  private:
    Square* entrance;
    Square* exit;
    int height = 7;
    int width = 6;
    // TODO
  public:
    Board ( );
    Board (int width, int height);
    ~Board ( ); 
    void print ( );
    void setNeighbours(Square*);
    // TODO
};
