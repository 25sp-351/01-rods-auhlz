#include "rodcut.h"
#include "vec.h"

int rod_cutting(int rod_length, PieceLengthValue pieces[], int num_pieces,
                Vec piece_counts, int *remainder) {

  if (rod_length == 0)
    return 0;

  int max_value = 0;
  int best_remainder = rod_length;

  // Use a vec to keep track of the counts in the best solution
  Vec best_counts_vec = vec_copy(piece_counts);

  for (int index = 0; index < num_pieces; index++) {

    if (pieces[index].length <= rod_length) {
      Vec temp_counts_vec = vec_copy(piece_counts);

      int current_remainder = rod_length - pieces[index].length;
      int current_value = pieces[index].value +
                          rod_cutting(current_remainder, pieces, num_pieces,
                                      temp_counts_vec, &current_remainder);

      if (current_value > max_value) {
        max_value = current_value;
        best_remainder = current_remainder;

        // Found a better solution, so update the counts
        vec_free(best_counts_vec);
        best_counts_vec = vec_copy(temp_counts_vec);
        int *counts = vec_items(best_counts_vec);
        counts[index]++;
      }

      vec_free(temp_counts_vec);
    }
  }

  *remainder = best_remainder;

  int *final_counts = vec_items(piece_counts);
  int *best_counts = vec_items(best_counts_vec);
  for (int index = 0; index < num_pieces; index++)
    final_counts[index] = best_counts[index];

  vec_free(best_counts_vec);
  return max_value;
}