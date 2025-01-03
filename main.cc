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
// Pre: una matriz CharMatrix que contenga los vectores de pistas a comparar. La matriz no debe estar vacía y debe contener
// un vector de pistas como mínimo.
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

// Construye un vector de pistas.
// Pre: la cantidad de pistas que construiremos (no confundir la cantidad de grupos/elementos de dentro de la pista), representadas
// por un número natural.
// Post: devuelve una matriz UIntMatrix que contiene 'clue_package_size' pistas.
UIntMatrix built_clues(unsigned int clue_package_size)
{
   UIntMatrix new_clue_package(clue_package_size);

   for (unsigned int i = 0; i < clue_package_size; ++i)
   {
      // Inv: hemos guardado i-1 pistas completas en el paquete de pistas 'new_clue_package'.

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
   slash_line += string(count_digits(board_size_y) + 2, ' ');
   slash_line += string(3 * board_size_x - 1, '-');

   return slash_line;
}

// Imprime la parte superior del tablero.
// Pre: el tamaño del tablero en el eje X (columnas) como un número natural y otro para el tamaño del tablero en el eje Y (filas).
// Post: no devuelve nada, solo imprime la leyenda de la parte superior.
void print_top_legend(unsigned int board_size_x, unsigned int board_size_y)
{
   // Añadimos espaciado a la leyenda para que encaje donde debe.
   cout << string(count_digits(board_size_x), ' ');

   // Inv: hemos impreso i-1 leyendas para las colummas del tablero.
   for (unsigned int i = 1; i <= board_size_x; ++i)
   {
      if (i <= 10)
         cout << "  " << i;
      else
         cout << ' ' << i;

      if (i == board_size_x)
      {
         cout << ' ';
      }
   }
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
      // Inv: hemos impreso 'i' filas de grupos/elementos de las pistas.

      // Añadimos el espacio en blanco que separa las líneas de la leyenda de las filas.
      cout << string(count_digits(board_size_y) + 2, ' ');

      for (unsigned int j = 0; j < col_clues.size(); ++j)
      {
         // Inv: hemos impreso 'j' pistas de la fila.
         string spacing;

         if (j != 0)
         {
            // Si el número anterior tiene 2 dígitos, ponemos un solo espacio.
            if (col_clues[j - 1].size() > i and col_clues[j - 1][i] >= 10)
               spacing = " ";
            else
               spacing = "  ";
         }

         // Imprimimos el número actual. Si no hay número porque no hay pista en ese punto,
         // lo rellenamos con un espacio.
         if (i < col_clues[j].size())
            cout << spacing << col_clues[j][i];
         else
            cout << spacing << ' ';
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

      unsigned int num_digit_length = count_digits(y + 1);
      unsigned int board_digit_length = count_digits(board.size() + 1);

      // Adaptamos la etiqueta de la fila para que siempre tenga el mismo
      // tamaño de espacios/texto independientemente de la cantidad de cifras
      // que tenga el número.
      cout << string(board_digit_length - num_digit_length, ' ') << (y + 1) << " |";

      for (unsigned int x = 0; x < board[0].size(); ++x)
         // Inv: hemos impreso x-1 elementos de la fila 'y' del tablero.
         if (x + 1 < board[0].size())
            cout << board[y][x] << "  ";
         else
            cout << board[y][x] << ' ';

      cout << "|";

      // Inv: hemos impreso i-1 elementos de la pista para la columna 'y'.
      for (unsigned int i = 0; i < row_clues[y].size(); ++i)
         cout << ' ' << row_clues[y][i];

      cout << endl;
   }
}

void draw_game(const UIntMatrix &row_clues, const UIntMatrix &col_clues, CharMatrix &board, string slash_line)
{
   unsigned int board_size_x = board[0].size();
   unsigned int board_size_y = board.size();

   // Imprimimos la leyenda de las columnas.
   print_top_legend(board_size_x, board_size_y);
   // Imprimimos las '-'s que cierran techo del tablero.
   cout << slash_line << endl;

   print_core_board(board, row_clues, col_clues);

   // Imprimimos las '-'s que cierran el suelo del tablero.
   cout << slash_line << endl;
   print_bottom_clues(board_size_x, board_size_y, col_clues);
   cout << endl;
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

// _________ COMPROBACIÓN DEL TABLERO _________

// Valida una 'línea', que sería una fila o una columna dependiendo del modo de corrección que hayamos elegido.
// Pre: una matriz CharMatrix que represente el tablero (board), una matriz UIntMatrix que contenga las pistas a revisar para la fila (clues), un número natural
// que nos haga de indice de que fila queremos comprobar (line_index) y un boleano para seleccionar el modo de corrección (is_row).
// Post: devuelve un boleano indicando si la fila es correcta (True) o no (False).
bool validate_line(const CharMatrix &board, const UIntMatrix &clues, unsigned int line_index, bool is_row)
{
   int current_group_index = -1; // Aún no hemos alcanzado ningún grupo.
   unsigned int group_marked_tiles = 0;
   bool solved = true; // Asumiremos por defecto que esta fila o columna es correcta.

   unsigned int x = 0, y = 0;
   while (solved and y < board.size() and x < board[0].size())
   {
      // Inv: hemos validado 'y' grupos si is_row es True y 'x' grupos si is_row es False.

      // Obtenemos lo que haya en la casilla (una X o un .) dependiendo de si estamos
      // corrigiendo por fila o columna.
      char current_tile;
      if (is_row)
         current_tile = board[line_index][x];
      else
         current_tile = board[y][line_index];

      if (current_tile == 'X')
      {
         ++group_marked_tiles;

         // Si estamos en el primer elemento o detrás hay un punto, avanzamos el índice del grupo. Todo este
         // lio es para garantizar que estamos buscando bien tanto si estamos en modo fila como columna.
         if ((is_row and x == 0) or (!is_row and y == 0) or
             (is_row and board[line_index][x - 1] == '.') or
             (!is_row and board[y - 1][line_index] == '.'))
         {
            ++current_group_index;

            // Si excedemos la cantidad de pistas, la línea no es válida.
            if (current_group_index >= int(clues[line_index].size()))
            {
               solved = false;
            }
         }

         // Si es el último elemento o detrás hay un punto, validamos el grupo actual.
         if ((is_row and x == board[0].size() - 1) or
             (!is_row and y == board.size() - 1) or
             (is_row and board[line_index][x + 1] == '.') or
             (!is_row and board[y + 1][line_index] == '.'))
         {
            if (clues[line_index][current_group_index] != group_marked_tiles)
            {
               solved = false;
            }
            // Reiniciar el contador para el siguiente grupo.
            group_marked_tiles = 0;
         }
      }
      // Si es un punto, asegurarse de que no quedan más Xs sin validar.
      else if (current_tile == '.')
      {
         if (group_marked_tiles > 0 and current_group_index < int(clues[line_index].size()))
         {
            if (clues[line_index][current_group_index] != group_marked_tiles)
            {
               solved = false;
            }
            group_marked_tiles = 0;
         }
      }

      // Avanzar en fila/columna.
      if (is_row)
         ++x;
      else
         ++y;
   }

   // Verificar si todos los grupos esperados fueron procesados.
   if (current_group_index != int(clues[line_index].size()) - 1)
      solved = false;

   return solved;
}

// Función principal para comprobar si el nonograma está resuelto
// Pre: una matriz UIntMatrix con las pistas de fila, una matriz UIntMatrix con las de columna y una matriz CharMatrix para el tablero.
// Pos: devuelve un boleano True en caso de que el Nonograma haya sido resuelto correctamente y un False en caso contrario.
bool is_nono_solved(const UIntMatrix &row_clues, const UIntMatrix &col_clues, CharMatrix &board)
{
   bool solved = true;

   // _____ Comprobación de filas ______
   unsigned int y = 0;
   while (solved and y < board.size())
   {
      // Inv: hemos válidado 'y' filas.
      if (!validate_line(board, row_clues, y, true))
         solved = false;
      else
         ++y;
   }

   // _____ Comprobación de columnas ______
   unsigned int x = 0;
   while (solved and x < board[0].size())
   {
      // Inv: hemos válidado 'x' filas.
      if (!validate_line(board, col_clues, x, false))
         solved = false;
      else
         ++x;
   }

   return solved;
}

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

   while (!end_game and !win)
   {
      // Inv: el jugador no ha ganado el juego y tampoco ha decidido rendirse.

      // ________ Entrada de opción ________

      char option_letter;
      cin >> option_letter;

      if (option_letter == 'A' or option_letter == 'E')
      {
         unsigned int y, x;
         cin >> y >> x; // Fila y luego columna

         // Comprobamos si la opción era la A o la E. Ya que si era la A, siempre ibamos a pasar
         // como parámetro en 'check' un boleano True. En caso de E, siempre es False.
         bool check = (option_letter == 'A');

         // Restamos 1 porque desde el punto de vista del usuario la coordenada X e Y empiezan
         // por 1 y no 0.
         do_action_AE(check, x - 1, y - 1, board);
      }

      else if (option_letter == 'B' or option_letter == 'F')
      {
         unsigned int x_start, x_end, y_start, y_end;
         cin >> y_start >> x_start >> y_end >> x_end;

         // Comprobamos si la opción era la B o la F. Ya que si era la B, siempre ibamos a pasar
         // como parámetro en 'check' un boleano True. En caso de F, siempre es False.
         bool check = (option_letter == 'B');

         do_action_BF(check, x_start - 1, x_end - 1, y_start - 1, y_end - 1, board);
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

      // Si hemos modificado el tablero, hacemos una corrección para ver si está bien.
      if ((option_letter == 'A' or option_letter == 'B' or option_letter == 'E' or option_letter == 'F') and !end_game)
      {
         ++action_counter;
         win = is_nono_solved(row_clues, col_clues, board);
      }
   }

   if (win)
   {
      draw_game(row_clues, col_clues, board, slash_line);
      cout << "Enhorabona! Has resolt el nonograma." << endl;
   }
   else
      cout << "Has sortit del joc. Fins aviat!" << endl;

   cout << "Nombre de moviments: " << action_counter << endl;
}