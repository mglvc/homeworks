#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//--- --- --- STRING --- --- ---

struct String {
    char* bbase;
    size_t sz;
    size_t reserved;
};


void spread(struct String* s) {

    s->bbase = realloc(s->bbase, s->reserved * 2);
    s->reserved *= 2;
}


void push_back(struct String* s, char c) {
    if (s->sz == s->reserved) {
        spread(s);
    }
    s->bbase[s->sz] = c;
    s->sz++;
}

struct String * initString() {
    struct String* s = calloc(1, sizeof(struct String));
    s->bbase = calloc(1, 1);
    s->sz = 0;
    s->reserved = 1;
    return s;
}

// --- --- --- NODE --- --- ---

struct Node {
    struct String * s;
    struct Node* next;
};

struct Node* make_node(struct String * val) {
    struct Node* nd = calloc(1, sizeof(struct Node));
    
    nd->s = val;
    nd->next = NULL;

    return nd;
}

// --- --- --- LIST --- --- ---

struct List {
    struct Node* head;
    struct Node* tail;
    size_t size;
};

struct List* create_list() {
    struct List* lst = calloc(1, sizeof(struct List));

    lst->head = NULL;
    lst->tail = NULL;
    lst->size = 0;

    return lst;
}

void delete_list(struct List* a) {
    struct Node* cur = a->head;
    struct Node* prev = NULL;

    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(a);
}


void print_list(struct List* a) {
    fprintf(stderr, "--- --- ---\n");
    fprintf(stderr, "List:\n");
    struct Node* cur = a->head;
    while (cur != NULL) {
        fprintf(stderr, "  | %s \n", cur->s->bbase);
        cur = cur->next;
    }
    fprintf(stderr, "___ ___ ___\n");
}

// --- --- --- LIST-NODE --- --- ---

void add_node(struct List* lst, struct Node* nd) {
    if (lst->tail == NULL) {
        lst->head = nd;
    } else {
        lst->tail->next = nd;
    }
    lst->tail = nd;
    lst->size++;
}

struct Node* remove_node(struct List* lst) {
    struct Node* removed = lst->head;
    lst->head = lst->head->next;
    if (lst->head == NULL) {
        lst->tail = NULL;
    }
    lst->size--;
    removed->next = NULL;
    return removed;
}

// --- --- --- MERGESORT --- --- ---

void split(struct List* lst, struct List* a, struct List* b) {
    int id = 0;
    while (lst->size > 0) {
        add_node((id != 0 ? a : b), remove_node(lst));
        //printf("тест 90\n");
        id ^= 1;
    }
}


void merge(struct List* lst, struct List* a, struct List* b) {
    while (a->size > 0 && b->size > 0) {
        if (strcmp(a->head->s->bbase, b->head->s->bbase) <= 0) {
            add_node(lst, remove_node(a));
        } else {
            add_node(lst, remove_node(b));
        }
    }
    while (a->size > 0) {
        add_node(lst, remove_node(a));
        //printf("тест 106\n");
    }
    while (b->size > 0) {
        add_node(lst, remove_node(b));
        //printf("тест 110\n");
    }
}


void merge_sort(struct List* lst) {
    if (lst->size == 1) {
        return;
    }

    struct List* a = create_list();
    struct List* b = create_list();
    
    split(lst, a, b);
    merge_sort(a);
    merge_sort(b);
    merge(lst, a, b);

    //print_list(a);
    //print_list(b);

    delete_list(a);
    delete_list(b);
    return;
}

// --- --- --- MERGE REVERSE SORT --- --- ---

void merger(struct List* lst, struct List* a, struct List* b) {
    while (a->size > 0 && b->size > 0) {
        if (strcmp(a->head->s->bbase, b->head->s->bbase) > 0) {
            add_node(lst, remove_node(a));
        } else {
            add_node(lst, remove_node(b));
        }
        //printf("тест 137\n");
    }
    while (a->size > 0) {
        add_node(lst, remove_node(a));
        //printf("тест 145\n");
    }
    while (b->size > 0) {
        add_node(lst, remove_node(b));
        //printf("тест 149\n");
    }
}


void merger_sort(struct List* lst) {
    if (lst->size == 1) {
        return;
    }
    struct List* a = create_list();
    struct List* b = create_list();
    
    split(lst, a, b);
    merger_sort(a);
    merger_sort(b);
    merger(lst, a, b);

    delete_list(a);
    delete_list(b);
    return;
}


// --- --- --- MERGESORT NUMS --- --- ---

void mergen(struct List* lst, struct List* a, struct List* b) {
    while (a->size > 0 && b->size > 0) {
        if (a->head->s<= b->head->s) {
            add_node(lst, remove_node(a));
        } else {
            add_node(lst, remove_node(b));
        }
        //printf("тест 177\n");
    }
    while (a->size > 0) {
        add_node(lst, remove_node(a));
        //printf("тест 185\n");
    }

    while (b->size > 0) {
        add_node(lst, remove_node(b));
        //printf("тест 190\n");
    }
}


void mergen_sort(struct List* lst) {
    if (lst->size == 1) {
        return;
    }
    struct List* a = create_list();
    struct List* b = create_list();
    
    split(lst, a, b);
    mergen_sort(a);
    mergen_sort(b);
    mergen(lst, a, b);

    delete_list(a);
    delete_list(b);
    return;
}

// --- --- --- MERGE REVERSE SORT NUMS --- --- ---


void mergern(struct List* lst, struct List* a, struct List* b) {
    while (a->size > 0 && b->size > 0) {
        if (a->head->s > b->head->s) {
            add_node(lst, remove_node(a));
        } else {
            add_node(lst, remove_node(b));
        }
        //printf("тест 218\n");
    }
    while (a->size > 0) {
        add_node(lst, remove_node(a));
        //printf("тест 226\n");
    }
    while (b->size > 0) {
        add_node(lst, remove_node(b));
        //printf("тест 230\n");
    }
}


void mergern_sort(struct List* lst) {
    if (lst->size == 1) {
        return;
    }
    struct List* a = create_list();
    struct List* b = create_list();
    
    split(lst, a, b);
    mergern_sort(a);
    mergern_sort(b);
    mergern(lst, a, b);

    delete_list(a);
    delete_list(b);
    return;
}


// --- --- --- MAIN --- --- ---

int main(int argc, char* argv[]) {

    char* file;
    char* ffile;

//--------------------------------------------
    int n = argc;

    char start = 1, num = 0, r = 0, o = 0;
    int fd = 1;
    if(argc<2){
        perror("мало аргументов\n");
        return 0;
    }
    int i = 1;
    char params = 1;
    while(i < n && params){
        char *end;
        switch (argv[i][0]){
            case'-':
            switch (argv[i][1]){
                case 'r':
                    r = 1;
                    
                    break;
                case 'n':
                    num = 1;
            
                    break;
                case 'o':
                        if(i == n){
                            perror("нет файла\n");
                            return 0;
                        }
                        i++;
                        if (fd != 1){
                            perror("ошибка\n");
                            return 0;
                        }
                        ffile = argv[i];
                      
                        fd = open(argv[i], O_CREAT| O_RDWR | O_TRUNC, S_IRWXU | S_IRWXG |S_IRWXO);
                        //fclose(ffile);
                        if (fd < 0){
                            fprintf(stderr, "невозможно открыт файл\n" );
                        }
                        o = 1;
                  
                    break;
                default:
                    fprintf(stderr, "невозможная операция\n");
                    return 0;
                    }
                i++;
                break;
            case '+':
                start = strtol(argv[i], &end, 10);
                if (*end != '\0'){
                    fprintf(stderr, "ошибка\n");
                    return 0;
                }
                i++;
                break;
            default:
                params = 0;
                break;


            }
        }

    if (i >= n){
        perror("потеряны имена файлов");
    }

    printf("числовой %d, обратный %d, начиная с %d, в файл %d\n", num, r, start,  o);


    int temp;

    while (i < n){
        file = argv[i];
        FILE* fsin = fopen(file, "r");
        
        struct List * base = create_list();

        printf("создали список\n");        
        
        char ch;
        temp = start;
        if (temp != 1){
            while(temp > 0 ) {
                ch = fgetc(fsin);
                    if (ch == '\n'){
                        temp --;
                    }
                }
            printf("перешли к нужной строке\n");
        }

        struct String * str = initString();
        while((ch=fgetc(fsin)) != EOF) {
            if (ch != '\n'){
                push_back(str, ch);
            } else {
                struct Node* nnode = make_node(str);
                add_node(base, nnode);
                str = initString();
            }
        }
        print_list(base);            
        printf("сортируем\n");
        if (r == 1){
            if (num == 1){
                mergern_sort(base);
            } else {

                merger_sort(base);
            }
        } else {
            if (num == 1){
                mergen_sort(base);
            } else {
                merge_sort(base);
            }
        }

        print_list(base);
        if (o == 1){
            FILE* fout = fopen(ffile, "w");
            struct Node* cur = base->head;
            while (cur != NULL) {
                fprintf(fout, "%s \n", cur->s->bbase);
                cur = cur->next;
            }
            fclose(fout);
        }
        i++;
        fclose(fsin);
    }
    return 0;
}



