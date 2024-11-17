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

void print_board(CharMatrix board)
{
    for (unsigned int y=0; y < board.size(); ++y)
    {

    }
}

int main()
{
    ////////// LECTURA DE DATOS INICIAL //////////

vector<int> extraerelementos(const vector<int>& entrada) {
    vector<int> pistas;

    int n = entrada[0] 
    if (n > 0 and n <= (entrada.size() - 1)) {
        for (int i = 1; i <= n; ++i) {
            pistas.push_back(entrada[i]);
        }
    }

    return pistas;
}

    //////////// LOGICA DEL JUEGO ///////////////

    bool player_won = false;

    // Mientras el jugador no haya ganado seguiremos ejecutando el juego.
    while(!player_won)
    {
        //Inv: 
    }

    //////// HACER EN EL FIN DEL JUEGO //////
    cout << "Enhorabona! Has resolt el nonograma." << endl;
}
