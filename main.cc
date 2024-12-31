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
unsigned int find_biggest_clue_size(const UIntMatrix &clue_matrix)
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

// Genera la línea de '-'s que cierra la parte superior e inferior del tablero.

// Pre: 'board_size_x' representa el número natural que nos indica el largo del tablero, mientras
// que 'board_size_y' es el número natural que aporta la altura que ayudará a poner los espacios
// en blanco a la izquierda de la fila.

// Post: devuelve un string con la línea ya formateada y preparada para su impresión directa.
string gen_horizontal_line(unsigned int board_size_x, unsigned int board_size_y)
{
   string slash_line = "";

   // Añadimos el espacio en blanco que separa las líneas de la leyenda de las filas.
   slash_line += string(count_digits(board_size_y), ' ');

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
   slash_line += string(total_sum_num_length + (board_size_x - 1) * 2, '-');

   return slash_line;
}

// Imprime la parte superior del tablero.
// Pre:
// Post:
void print_top_legend(unsigned int board_size_x, unsigned int board_size_y)
{
   // Restamos 1 por que ya hemos añadido un espacio con el primer elemento de la leyenda.
   cout << string(count_digits(board_size_y) - 1, '-');

   // Inv: hemos impreso i-1 leyendas para las colummas del tablero.
   for (unsigned int i = 1; i <= board_size_x; ++i)
      cout << " " << i << " ";

   cout << endl;
}

// Imprime la parte inferior del tablero la cual contiene las pistas para las columnas.
// Pre: un número natural que indique el tamaño del tablero (board_size_x), otro natural que indique
// el alto (board_size_y) y finalmente una matriz de naturales que contenga las pistas de las columnas
// (col_clues).
// Post: no devuelve nada, solo imprime la parte inferior del tablero.
void print_bottom_clues(unsigned int board_size_x, unsigned int board_size_y, const UIntMatrix &col_clues)
{
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

// Imprime el estado actual de la partida. No incluye los elementos decorativos como las pistas.
//
// Pre: la matriz de tipo CharMatrix que representa el tablero y las matrices tipo UIntMatrix que representan
// las pistas de las filas y de las columnas.
//
// Post: no devuelve nada.
void print_core_board(CharMatrix &board, const UIntMatrix &row_clues, const UIntMatrix &col_clues)
{

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
}

void draw_game(const UIntMatrix &row_clues, const UIntMatrix &col_clues, CharMatrix &board, string slash_line)
{
   unsigned int board_size_x = board[0].size();
   unsigned int board_size_y = board.size();

   print_top_legend(board_size_x, board_size_y); // Imprimimos la leyenda de las columnas.
   cout << slash_line << endl;                   // Imprimimos las '-'s que cierran techo del tablero.

   print_core_board(board, row_clues, col_clues); // Imprimimos el tablero.

   cout << slash_line << endl; // Imprimimos las '-'s que cierran el suelo del tablero.

   print_bottom_clues(board_size_x, board_size_y, col_clues);
}

// ________ FUNCIONES DE ACCIÓN _________

// Se marca o desmarca la casilla en las coordenadas X (selected_x) e Y (selected_y) en el tablero (board). Dependiendo de la opción,
// no haremos nada en los casos que ya estén marcadas/desmarcadas.
//
// Pre: dos números naturales (para las coordenadas en selected_x e selected_y) y una matriz de caracteres
// a modificar (el tablero). Finalmente, un boleano 'check' que nos indica si deseamos marcar (True) o
// desmarcar (False).
//
// Pos: la función no devuelve nada, pero si modifica la variable 'board' para editar el tablero que esta
// contiene.
void do_action_AE(bool check, unsigned int selected_x, unsigned int selected_y, CharMatrix &board)
{
   if (check and board[selected_y][selected_x] == '.')
      board[selected_y][selected_x] = 'X';
   else if (!check and board[selected_y][selected_x] == 'X')
      board[selected_y][selected_x] = '.';
}

// Se marcan o desmarcan todas las casillas dentro del rectangulo que delimitan las coordenadas X e Y indicadas dependiendo
// de si desea marcar o desmarcar. Además, dependiendo de la opción, no se modificarán aquellas casillas que
// ya estuvieran marcadas/desmarcadas.
//
// Pre: 4 números naturales que indiquen las coordenadas X de inicio, X final, Y inicio e Y final y una matriz
// CharMatrix que contenga el tablero a modificar. Finalmente, un boleano que nos indica si queremos marcar casillas
// (true) o desmarcarlas (false).
//
// Pos: no devuelve nada, pero modifica el grupo de casillas dentro del rectangulo que dibujan las coordenadas
// en el tablero 'board'.
void do_action_BF(bool check, unsigned int x_start, unsigned int x_end,
                  unsigned int y_start, unsigned int y_end, CharMatrix &board)
{
   for (unsigned int y = y_start; y <= y_end; ++y)
   {
      // Inv: hemos marcado las casillas de 'y - y_end' filas del rectangulo.

      for (unsigned int x = x_start; x <= x_end; ++x)
      {
         // Inv: hemos marcado 'x - x_start' casillas de la fila 'y' del rectangulo.

         if (check and board[y][x] == '.')
            board[y][x] = 'X';
         else if (!check and board[y][x] == 'X')
            board[y][x] = '.';
      }
   }
}

// Devuelve el contador de acciones realizadas a 0 y reinicia el tablero.
//
// Pre: una variable que contenga de tipo número natural cuyo contenido sea la cantidad de acciones
// hechas (action_counter) y una variable de tipo CharMatrix cuyo contenido sea el tablero que
// deseamos reiniciar.
//
// Pos: no devuelve nada, pero pone la variable 'action_counter' a 0 y rellena todo el tablero (board)
// con '.'s, devolviendolo a su estado inicial.
void do_action_R(unsigned int &action_counter, CharMatrix &board)
{
   action_counter = 0;

   for (unsigned int y = 0; y < board.size(); ++y)
   {
      // Inv: hemos llenado 'y' filas con '.'s.
      for (unsigned int x = 0; x < board[0].size(); ++x)
      {
         // Inv: hemos reemplazado 'x' elementos de la fila 'y' con '.'s.

         if (board[y][x] == 'X')
            board[y][x] = '.';
      }
   }
}

// Las acciones S y Z están implementadas directamente sobre main().

int main()
{
   // ______ Inicialización de variables _______

   unsigned int row_clue_boxes, col_clue_boxes;
   cin >> row_clue_boxes >> col_clue_boxes;

   unsigned int action_counter = 0;

   CharMatrix board(row_clue_boxes, vector<char>(col_clue_boxes, '.'));

   UIntMatrix row_clues = built_clues(row_clue_boxes);
   UIntMatrix col_clues = built_clues(col_clue_boxes);

   string slash_line = gen_horizontal_line(board[0].size(), board.size());

   // _________ Impresión de la partida ___________

   draw_game(row_clues, col_clues, board, slash_line);

   bool win = false; // Para determinar si el jugador ha ganado o ha salido forzadamente.
   bool end_game = false;

   while (!end_game)
   {
      // Inv: el jugador no ha ganado el juego y tampoco ha decidido rendirse.

      // ________ Entrada de opción ________

      char option_letter;
      cin >> option_letter;

      if (option_letter == 'A' or option_letter == 'E')
      {
         unsigned int x, y;
         cin >> x >> y;

         // Comprobamos si la opción era la A o la E. Ya que si era la A, siempre ibamos a pasar
         // como parámetro en 'check' un boleano True. En caso de E, siempre es False.
         bool check = (option_letter == 'A'); 

         do_action_AE(check, x, y, board);

      } 
      
      else if (option_letter == 'B' or option_letter == 'F')
      {
         unsigned int x_start, x_end, y_start, y_end;
         cin >> x_start >> y_start >> x_end >> y_end;

         // Comprobamos si la opción era la B o la F. Ya que si era la B, siempre ibamos a pasar
         // como parámetro en 'check' un boleano True. En caso de F, siempre es False.
         bool check = (option_letter == 'B');

         do_action_BF(check, x_start, x_end, y_start, y_end, board);
      }

      else if (option_letter == 'R')
      {
         do_action_R(action_counter, board);
      }

      else if (option_letter == 'S')
      {
         draw_game(row_clues, col_clues, board, slash_line);
      }
      else
      {
         // Como todos los inputs son correctos (según la documentación), tenemos garantizado que
         // si no se ha ejecutado cualquiera de las anteriores acciones es por que el jugador ha
         // introducido una 'Z', por lo que salimos del juego.

         end_game = true;
      }
   }

   if (win) cout << "Enhorabona! Has resolt el nonograma.";
   else "Has sortit del joc. Fins aviat!";
}
