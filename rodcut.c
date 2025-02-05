#include "rodcut.h"
#include "vec.h"

#include <stdio.h>
#include <string.h>

int rod_cutting(int rod_length, PieceLengthValue pieces[], int num_pieces,
                int piece_counts[], int *remainder) {

  if (rod_length == 0)
    return 0;

  int max_value = 0;
  int best_remainder = rod_length;
  int best_counts[num_pieces];

  // Keeps track of the counts in the best solution
  memset(best_counts, 0, num_pieces * sizeof(int));

  for (int index = 0; index < num_pieces; index++) {

    if (pieces[index].length <= rod_length) {
      int temp_counts[num_pieces];
      memcpy(temp_counts, piece_counts, sizeof(num_pieces));

      int current_remainder = rod_length - pieces[index].length;
      int current_value = pieces[index].value +
                          rod_cutting(current_remainder, pieces, num_pieces,
                                      temp_counts, &current_remainder);
      temp_counts[index]++;

      if (current_value > max_value) {
        max_value = current_value;
        best_remainder = current_remainder;

        // Found a better solution, so update the counts
        memcpy(best_counts, temp_counts, num_pieces * sizeof(int));
      }
    }
  }
  *remainder = best_remainder;

  memcpy(piece_counts, best_counts, num_pieces * sizeof(int));
  return max_value;
}

void print_result(int num_pieces, int piece_counts[], PieceLengthValue pieces[],
                  int max_rodcut, int remainder) {
  for (int index = 0; index < num_pieces; index++) {
    if (piece_counts[index] > 0) {
      int total_piece_value = piece_counts[index] * pieces[index].value;
      printf("%d @ %d = %d\n", piece_counts[index], pieces[index].length,
             total_piece_value);
    }
  }
  printf("Total Value: %d\n", max_rodcut);
  printf("Remainder: %d\n", remainder);
}