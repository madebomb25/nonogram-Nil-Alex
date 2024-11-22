#include <iostream>
#include <vector>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> CharMatrix;

// Genera un tablero inicial y devuelve la matriz que lo contiene.
// Pre: un natural que defina el alto y un natural que defina el ancho.
// Post: devuelve un CharMatrix que contiene el tablero inicial.
CharMatrix gen_board(unsigned int rows, unsigned int columns)
{
    return CharMatrix(rows, Row(columns, '.'));
}

// Imprime las opciones que el jugador tiene y devuelve la opción que haya seleccionado
// el jugador.
// Pre: haber impreso el tablero del jugador anteriormente.
// Post: devuelve un char con la opción seleccionada.
char ask_option()
{
    char option;
    cin >> option;

    ///////////////////////////////////////////////////////////////////
    // Hacer código para mostrar las opciones disponibles y que hacen.
    //////////////////////////////////////////////////////////////////

    return option;
}

void print_board(CharMatrix board)
{
    for (unsigned int y=0; y < board.size(); ++y)
    {
        for (unsigned int x=0; x < board[0].size(); ++x)
        {
            cout << board[y][x];
            cout << " ";
        }

        cout << endl;
    }
}

int main()
{
    ////////// LECTURA DE DATOS INICIAL //////////

    
    //////////// LOGICA DEL JUEGO ///////////////

    bool player_won = false;

    //Generamos el tablero inicial que el jugador tendrá.
    //(por ahora para hacer pruebas me los invento)
    CharMatrix player_board = gen_board(10, 10);

    // Mientras el jugador no haya ganado seguiremos ejecutando el juego.
    while(!player_won)
    {
        // Inv: seguimos actualizando el estado del juego, ya que el jugador
        // aún no ha ganado.

        print_board(player_board);

        // Después de imprimir el tablero le preguntamos al jugador que quiere
        // hacer.
        char option = ask_option();
    }

    //////// HACER EN EL FIN DEL JUEGO //////
    cout << "Enhorabona! Has resolt el nonograma." << endl;
}
