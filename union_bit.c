#include <stdio.h>

union decision {
    unsigned char flags;
    struct {
        unsigned int your_choice:1;
        unsigned int your_mothers_choice:1;
        unsigned int your_fathers_choice:1;
        unsigned int socially_acceptable:1;
        unsigned int financially_viable:1;
        unsigned int do_you_have_aptitude:1;
        unsigned int do_you_likeit:1;
        unsigned int final_decision:1;
    } field;
};

/* Input */
union decision input() {
    union decision d = {0};
    int temp;  // <-- VERY IMPORTANT

    printf("Enter your choice (0/1): ");
    scanf("%d", &temp);
    d.field.your_choice = temp;

    printf("Mother's choice (0/1): ");
    scanf("%d", &temp);
    d.field.your_mothers_choice = temp;

    printf("Father's choice (0/1): ");
    scanf("%d", &temp);
    d.field.your_fathers_choice = temp;

    printf("Socially acceptable (0/1): ");
    scanf("%d", &temp);
    d.field.socially_acceptable = temp;

    printf("Financially viable (0/1): ");
    scanf("%d", &temp);
    d.field.financially_viable = temp;

    printf("Do you have aptitude (0/1): ");
    scanf("%d", &temp);
    d.field.do_you_have_aptitude = temp;

    printf("Do you like it (0/1): ");
    scanf("%d", &temp);
    d.field.do_you_likeit = temp;

    return d;
}

/* Decision logic */
void make_decision(union decision *d) {
    d->field.final_decision =
        (d->field.do_you_likeit &&
         d->field.do_you_have_aptitude &&
         (d->field.your_choice ||
          d->field.your_mothers_choice ||
          d->field.your_fathers_choice) &&
         d->field.financially_viable &&
         d->field.socially_acceptable);
}

/* Print */
void print_decision(union decision d) {
    printf("\nFinal Decision: %s\n",
           d.field.final_decision ? "GO FOR IT" : "NOT RECOMMENDED");
}

/* Flags */
void print_conclusion_based_on_flags(union decision d) {
    int count = 0;

    for (int i = 0; i < 8; i++) {
        if (d.flags & (1 << i))
            count++;
    }

    printf("Positive factors: %d/8\n", count);
}

int main() {
    union decision d;

    d = input();
    make_decision(&d);
    print_decision(d);
    print_conclusion_based_on_flags(d);

    return 0;
}
