// DERIVED FROM EXAMPLE FILE PROVIDED BY TEACHER
// file board.h
class Square {
  public:
    char color;
    Square* buren[8];
    Square ( );
};

class Board {
  private:
    Square* ingang;
    int height, width;
    // TODO
  public:
    Board ( );
    Board (int width, int height);
    ~Board ( );
    void print ( );
    // TODO
};
