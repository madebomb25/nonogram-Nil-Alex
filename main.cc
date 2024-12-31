#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> CharMatrix;
typedef vector<vector<unsigned int>> UIntMatrix;

//________________ UTILIDADES ________________

// Cuenta los digitos que tiene un número natural.
// Pre: un número natural.
// Post: devuelve la cantidad de digitos que tiene el número natural dado como un
// entero sin signo.
unsigned int count_digits(unsigned int n)
{
   unsigned int count = 0;

   while (n > 0)
   {
      // Inv: hemos extraido 'count' digitos de 'n'.
      ++count;
      n /= 10;
   }

   return count;
}

// Encuentra el largo del vector de pistas más grande de una matriz de pistas UIntMatrix.
// Pre: una matriz CharMatrix que contenga los vectores de pistas a comparar.
// Pos: devuelve un número natural que indica el tamaño del vector de pistas más grande encontrado.
unsigned int find_biggest_clue_size(UIntMatrix clue_matrix)
{
   // Asumimos por defecto que el vector más grande es el primero.
   unsigned int biggest_clue_vector_size = clue_matrix[0].size();

   for (unsigned int i = 1; i < clue_matrix.size(); ++i)
   {
      // Inv: hemos comprobado para 'i' vectores si alguno tenía un largo mayor que el primer
      // vector de la matriz.
      if (clue_matrix[i].size() > biggest_clue_vector_size)
      {
         biggest_clue_vector_size = clue_matrix[i].size();
      }
   }

   return biggest_clue_vector_size;
}

//
// Pre:
// Post:
UIntMatrix built_clues(unsigned int clue_package_size)
{
   UIntMatrix new_clue_package(clue_package_size);

   // Inv: hemos guardado i-1 pistas completas en el paquete de pistas 'new_clue_package'.
   for (unsigned int i = 0; i < clue_package_size; ++i)
   {
      unsigned int clue_size;
      cin >> clue_size;

      vector<unsigned int> clue(clue_size);

      // Inv: hemos guardado j-1 elementos de la pista 'i' en 'clue';
      for (unsigned int j = 0; j < clue_size; ++j)
         cin >> clue[j];

      new_clue_package[i] = clue;
   }

   return new_clue_package;
}

// __________________FUNCIONES PARA LA DE GESTIÓN DEL TABLERO ___________________

// Imprime las líneas horizontales que separan las leyendas horizontales de las columnas del tablero
// con el tablero en si.

// Pre: 'board_size_x' representa el número natural que nos indica el largo del tablero, mientras
// que 'board_size_y' es el número natural que aporta la altura que ayudará a poner los espacios
// en blanco a la izquierda de la fila.

// Post: no devuelve nada, solo imprime una línea de guiones en base al largo del tablero.
void print_horizontal_lines(unsigned int board_size_x, unsigned int board_size_y)
{

   // Añadimos el espacio en blanco que separa las líneas de la leyenda de las filas.
   cout << string(count_digits(board_size_y), ' ');

   // Con 'board_size_x - 1' obtenemos la cantidad de veces que habrá que poner 2 espacios en
   // blanco entre la leyenda de cada columna. Luego lo multiplicamos por 2 para obtener 2 espacios
   // por leyenda.
   unsigned int space_slashes = (board_size_x - 1) * 2;

   // Sumamos las longitudes de todos los números para encontrar la cantidad de '-' que necesitaremos
   // poner debajo de ellos.
   unsigned int total_sum_num_length = 0;

   for (unsigned int n = 1; n <= board_size_x; ++n)
   {
      // Inv: hemos sumado las longitudes de 'n' números.
      total_sum_num_length += count_digits(n);
   }

   // Imprimimos la línea entera ya sabiendo la cantidad de '-' que necesitaremos tanto
   // para los dobles espacios en blanco para cada número de la leyenda y la cantidad de '-'
   // que van debajo de cada número, lo que nos da la línea entera.
   cout << string(total_sum_num_length + (board_size_x - 1) * 2, '-') << endl;
}

// Imprime la parte superior del tablero.
// Pre:
// Post:
void print_board_top(unsigned int board_size_x, unsigned int board_size_y)
{
   // Restamos 1 por que ya hemos añadido un espacio con el primer elemento de la leyenda.
   cout << string(count_digits(board_size_y) - 1, '-');

   // Inv: hemos impreso i-1 leyendas para las colummas del tablero.
   for (unsigned int i = 1; i <= board_size_x; ++i)
      cout << " " << i << " ";

   cout << endl;

   print_horizontal_lines(board_size_x, board_size_y);
}

// Imprime la parte inferior del tablero la cual contiene las pistas para las columnas.
// Pre: un número natural que indique el tamaño del tablero (board_size_x), otro natural que indique
// el alto (board_size_y) y finalmente una matriz de naturales que contenga las pistas de las columnas
// (col_clues).
// Post: no devuelve nada, solo imprime la parte inferior del tablero.
void print_board_bottom(unsigned int board_size_x, unsigned int board_size_y, UIntMatrix &col_clues)
{
   print_horizontal_lines(board_size_x, board_size_y);

   for (unsigned int i = 0; i < find_biggest_clue_size(col_clues); ++i)
   {
      // Inv: hemos impreso 'i' líneas de pistas para las pistas de las columnas.

      // Añadimos el espacio en blanco que separa las líneas de la leyenda de las filas. Le restamos 2
      // para compensar con el primer elemento de las columnas, ya que cada elemento imprime 2 espacios
      // a la izquierda.
      cout << string(count_digits(board_size_y - 2), ' ');

      for (unsigned int j = 0; j < col_clues.size(); ++j)
      {
         // Inv: hemos impreso 'j' pistas para la línea 'i'.

         cout << "  ";

         if (i < col_clues[j].size())
            cout << col_clues[j][i];
         else
            cout << " ";
      }

      cout << endl;
   }
}

// Imprime el estado actual de la partida.
// Pre: la matriz de tipo CharMatrix que representa el tablero y las matrices tipo UIntMatrix que representan
// las pistas de las filas y de las columnas.
// Post: no devuelve nada.
void print_board(CharMatrix &board, UIntMatrix &row_clues, UIntMatrix &col_clues)
{

   // Imprimimos la leyenda para las columnas y las líneas que cierran la cara superior
   // del tablero.
   print_board_top(board[0].size(), board.size());

   //// Impresión del tablero principal ////

   for (unsigned int y = 0; y < board.size(); ++y)
   {
      // Inv: Hemos impreso y-1 filas del tablero.
      unsigned int num_length = count_digits(y);

      // Adaptamos la etiqueta de la fila para que siempre tenga el mismo
      // tamaño de espacios/texto independientemente de la cantidad de cifras
      // que tenga el número.
      cout << string(board.size() - num_length, ' ') << (y + 1);

      // Inv: hemos impreso x-1 elementos de la fila 'y' del tablero.
      for (unsigned int x = 0; x < board[0].size(); ++x)
         cout << ' ' << board[y][x] << ' ';

      cout << "|";

      // Inv: hemos impreso i-1 elementos de la pista para la columna 'y'.
      for (unsigned int i = 0; i < row_clues[y].size(); ++i)
         cout << ' ' << row_clues[y][i];
   }

   // Imprimimos las líneas que cierran la cara inferior del tablero y imprimimos
   // las pistas para las columnas.
   print_board_bottom(board[0].size(), board.size(), col_clues);
}

int main()
{
   unsigned int row_clue_boxes, col_clue_boxes;
   cin >> row_clue_boxes >> col_clue_boxes;

   CharMatrix board(row_clue_boxes, vector<char>(col_clue_boxes, '.'));

   UIntMatrix row_clues = built_clues(row_clue_boxes);
   UIntMatrix col_clues = built_clues(col_clue_boxes);
}
