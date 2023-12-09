#include <stdio.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>

/// number -> that number
/// J -> 1
/// T, Q, K, A -> 10, 11, 12, 13
/// other -> -1
int card_value(char card) {
    if (isdigit(card)) return (int)(card - '0');

    switch (card) {
        case 'J': return 1;
        case 'T': return 10;
        case 'Q': return 11;
        case 'K': return 12;
        case 'A': return 13;
        default: return -1;
    }
}

/// Hand `a` wins lexographically -> `-1`
/// Hand `b` wins lexographically -> `1`
/// `a == b` -> 0
int lex_compare(char a[6], char b[6]) {
    int al = 0, bl = 0;
    int i = 0;

    while (al == bl && i < 5) {
        al += card_value(a[i]);
        bl += card_value(b[i]);
        i++;
    }

    if (al > bl) return -1;
    if (bl > al) return 1;
    return 0;
}

/// Hand `a` wins -> `-1`
/// Hand `b` wins -> `1`
int compare(char a[6], char b[6]) {
    // index `i` stores the number of cards in the hand with `card_value` `i+2`
    int a_set[13] = {0}, b_set[13] = {0};

    int a_jokers = 0, b_jokers = 0;

    // # of unique cards in each hand
    int a_unique = 0;
    int b_unique = 0;
    // biggest number of the same card in each hand
    int a_max = 0;
    int b_max = 0;

    for(int i=0; i<5; i++) {
        if (card_value(a[i]) == 1) {
            a_jokers ++;
            continue;
        }
        int av = card_value(a[i]) - 2;
        if (!a_set[av]) a_unique ++;

        a_set[av] ++;
        if (a_set[av] > a_max) a_max = a_set[av];
    }

    for(int i=0; i<5; i++) {
        if (card_value(b[i]) == 1) {
            b_jokers ++;
            continue;
        }
        int bv = card_value(b[i]) - 2;
        if (!b_set[bv]) b_unique ++;

        b_set[bv] ++;
        if (b_set[bv] > b_max) b_max = b_set[bv];
    }

    if (a_max + a_jokers > b_max + b_jokers) return -1;
    if (a_max + a_jokers < b_max + b_jokers) return 1;

    if (a_unique > b_unique && b_unique > 0) return 1;
    if (a_unique < b_unique && a_unique > 0) return -1;

    return lex_compare(a, b);
}

typedef struct {
    char* cards;
    uint64_t bet;
} Hand;

/// Binary heap of card hands
///
/// Root node is strongest hand
typedef struct {
    /// Number of hands in the heap
    int size;
    Hand* data;
} BinaryHeap;

void add(BinaryHeap* heap, Hand hand) {
    heap->size ++;
    heap->data = realloc(heap->data, heap->size*sizeof(Hand));

    int hand_i = heap->size - 1;
    heap->data[hand_i] = hand;

    while (hand_i > 0 && compare(hand.cards, heap->data[(hand_i-1)/2].cards) == -1) {
        heap->data[hand_i] = heap->data[(hand_i-1)/2];
        hand_i = (hand_i-1)/2;
        heap->data[hand_i] = hand;
    }
}

void swap(Hand* data, int i, int j) {
    Hand tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

/// If the heap is empty, returns a `Hand` with `.cards = NULL`
Hand pop_root(BinaryHeap* heap) {
    if (heap->size == 0) {
        Hand null_hand = { .cards = NULL, .bet = 0 };
        return null_hand;
    }

    Hand root = heap->data[0];

    heap->data[0] = heap->data[heap->size - 1];
    heap->size --;
    heap->data = realloc(heap->data, sizeof(Hand) * heap->size);

    int i = 0;

    while (1) {
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l >= heap->size) break;
        if (r >= heap->size) {
            // left node exists but right doesn't
            if (compare(heap->data[i].cards, heap->data[l].cards) == 1) {
                swap(heap->data, i, l);
                i = l;
                continue;
            } else break;
        }

        int cr = compare(heap->data[i].cards, heap->data[r].cards) == 1;
        int cl = compare(heap->data[i].cards, heap->data[l].cards) == 1;

        if (cr && cl) {
            if (compare(heap->data[r].cards, heap->data[l].cards) == -1) {
                swap(heap->data, i, r);
                i = r;
            } else {
                swap(heap->data, i, l);
                i = l;
            }
        } else if (cl) {
            swap(heap->data, i, l);
            i = l;
        } else if (cr) {
            swap(heap->data, i, r);
            i = r;
        } else {
            break;
        }
    }

    return root;
}

int main() {
    FILE* input_file = fopen("input/7.txt", "r");

    BinaryHeap heap = {
        .size = 0,
        .data = NULL,
    };

    uint64_t num = 0;
    do {
        char* cards = malloc(6);
        uint64_t bet;

        fscanf(input_file, "%s %lu \n", cards, &bet);

        Hand current = {
            .cards = cards,
            .bet = bet,
        };

        add(&heap, current);
        num ++;
    } while (!feof(input_file));
    
    uint64_t winnings = 0;
    while(num > 0) {
        Hand h = pop_root(&heap);
        winnings += num * h.bet;
        num --;
    }
    printf("%lu\n", winnings);

    fclose(input_file);
    return 0;
}
