#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<string>> StringMatrix;
typedef vector<vector<unsigned int>> UIntMatrix;

//
// Pre:
// Post:
UIntMatrix built_clues(unsigned int clue_package_size)
{
   UIntMatrix new_clue_package(clue_package_size);

   // Inv: hemos guardado i-1 pistas completas en el paquete de pistas 'new_clue_package'.
   for (unsigned int i=0; i < clue_package_size; ++i)
   {
      unsigned int clue_size;
      cin >> clue_size;

      vector<unsigned int> clue(clue_size);

      // Inv: hemos guardado j-1 elementos de la pista 'i' en 'clue';
      for (unsigned int j=0; j < clue_size; ++j) cin >> clue[j];

      new_clue_package[i] = clue;
   }

   return new_clue_package;
}

//////////////// FUNCIONES DE GESTIÓN DE TABLERO ///////////////////

//
// Pre:
// Post:
void print_horizontal_lines(unsigned int board_size_x, unsigned int board_size_y)
{
   unsigned int num_size = to_string(board_size_y).size();

   cout << string(num_size, '-');

   for (unsigned int i=1; i <= board_size_x; ++i)
   {
      // Inv: 'num_length' contiene el número de digitos de 'i'.
      unsigned int num_length = to_string(i).size();
      cout << string(i*num_length, '-');
   }

   cout << endl;
}

//
// Pre:
// Post:
void print_board_top(unsigned int board_size_x, unsigned int board_size_y)
{
   // Restamos 1 por que ya hemos añadido un espacio con el primer elemento de la leyenda.
   cout << string(to_string(board_size_y).size() - 1, '-');

   // Inv: hemos impreso i-1 leyendas para las colummas del tablero.
   for (unsigned int i=1; i <= board_size_x; ++i) cout << " " << i << " ";

   cout << endl;

   print_horizontal_lines(board_size_x, board_size_y);
}

//
// Pre:
// Post:
void print_board_bottom(unsigned int board_size_x, unsigned int board_size_y, UIntMatrix& col_clues)
{
   print_horizontal_lines(board_size_x, board_size_y);
   
   // Añadir función que ponga los espacios.
   unsigned int row = 0;
   bool exit = false;
   while(not exit)
   {
	   // Inv:
	   
	   exit = true;
	   for (unsigned int col=0; col < board_size_y; ++col)
	   {
		   //Inv:
		   
		   if (())
	   }
	   
	   
	   ++row;
   }
   
   
   
}

// Imprime el estado actual de la partida.
// Pre: la matriz de tipo StringMatrix que representa el tablero y las matrices tipo UIntMatrix que representan
// las pistas de las filas y de las columnas.
// Post: no devuelve nada.
void print_board(StringMatrix& board, UIntMatrix& row_clues, UIntMatrix& col_clues)
{

   // Imprimimos la leyenda para las columnas y las líneas que cierran la cara superior
   // del tablero.
   print_board_top(board[0].size(), board.size());

   //// Impresión del tablero principal ////

   for (unsigned int y = 0; y < board.size(); ++y)
   {
      // Inv: Hemos impreso y-1 filas del tablero.
      unsigned int num_length = to_string(y).size();

      // Adaptamos la etiqueta de la fila para que siempre tenga el mismo
      // tamaño de espacios/texto independientemente de la cantidad de cifras
      // que tenga el número.
      cout << string(board.size() - num_length, ' ') << (y+1);
      

      // Inv: hemos impreso x-1 elementos de la fila 'y' del tablero.
      for (unsigned int x = 0; x < board[0].size(); ++x) cout << ' ' << board[y][x] << ' ';

      cout << "|";

      // Inv: hemos impreso i-1 elementos de la pista para la columna 'y'.
      for (unsigned int i=0; i < row_clues[y].size(); ++i) cout << ' ' << row_clues[y][i];
   }

   // Imprimimos las líneas que cierran la cara inferior del tablero y imprimimos
   // las pistas para las columnas.
   print_board_bottom(board[0].size(), board.size(), col_clues);

}

int main()
{
   unsigned int row_clue_boxes, col_clue_boxes;
   cin >> row_clue_boxes >> col_clue_boxes;

   StringMatrix board(row_clue_boxes, vector<string>(col_clue_boxes, "."));

   UIntMatrix row_clues = built_clues(row_clue_boxes);
   UIntMatrix col_clues = built_clues(col_clue_boxes);
}
