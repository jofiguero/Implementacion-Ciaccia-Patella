typedef struct{
    Entry *List;
    int limit;
} Node;

typedef struct {
    double p;
    double cr;
    Node *a;
} Entry;