#ifndef RODCUT_H
#define RODCUT_H

#include "vec.h"

typedef int PieceLength;
typedef int PieceValue;

typedef struct {
  PieceLength length;
  PieceValue value;
} PieceLengthValue;

int rod_cutting(int rod_length, PieceLengthValue pieces[], int num_pieces,
                int piece_counts[], int *remainder);

void print_result(int num_pieces, int piece_counts[], PieceLengthValue pieces[],
                  int max_rodcut, int remainder);
#endif
