#include <stdio.h>

#include "rodcut.h"
#include "vec.h"

#define MAX_PIECES 100

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Error Invalid Argument Count.\nUse this format:  %s <rod_length>\n",
           argv[0]);
    return 1;
  }

  int rod_length = 0;
  if (sscanf(argv[1], "%d", &rod_length) != 1 || rod_length <= 0) {
    printf("Error Invalid rod length.\n");
    return 1;
  }

  printf("Please enter piece value options in the format of <length>, <value> "
         "(ctrl+d to input) "
         "where both are integers:\n");

  PieceLengthValue pieces[MAX_PIECES];
  int num_pieces = 0;

  while (!feof(stdin)) {
    if (scanf("%d, %d", &pieces[num_pieces].length,
              &pieces[num_pieces].value) == 2) {
      num_pieces++;
    } else {
      break;
    }
  }
  // Initialize counts array
  int piece_counts[num_pieces];
  for (int index = 0; index < num_pieces; index++) {
    piece_counts[index] = 0;
  }

  int remainder = 0;

  int max_rodcut =
      rod_cutting(rod_length, pieces, num_pieces, piece_counts, &remainder);

  printf("\nRod Length: %d\n", rod_length);

  print_result(num_pieces, piece_counts, pieces, max_rodcut, remainder);
}