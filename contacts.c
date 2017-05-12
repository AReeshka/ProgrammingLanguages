#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct Contact {
    int id;
    char *number, *name;
} contact;


char *filename;


char *read_string(FILE *in) {
    char *a = (char *) malloc(sizeof(char) * 2);
    unsigned size = 2, ind = 0;
    char c;
    do {
        c = fgetc(in);
    } while (c == '\0' || c == '\n' || c == ' ');
    while (c != '\0' && c != '\n' && c != ' ' && c != EOF) {
        if (ind + 1 >= size) {
            a = realloc(a, size * 2);
            size *= 2;
        }
        a[ind++] = c;
        c = fgetc(in);
    }
    a[ind] = '\0';
    return a;
}


void normal_number(contact *con) {
    char *new_number = (char *) malloc(2 * sizeof(char));
    unsigned size = 2, ind = 0;
    for (int i = 0; con->number[i] != '\0'; i++) {
        if (con->number[i] >= '0' && con->number[i] <= '9') {
            if (ind + 1 >= size) {
                new_number = realloc(new_number, size * 2);
                size *= 2;
            }
            new_number[ind++] = con->number[i];
        }
    }
    new_number[ind] = '\0';
    free(con->number);
    con->number = new_number;
}

contact *read_contact(FILE *in) {
    contact *con = (contact *) malloc(sizeof(contact));
    fscanf(in, "%d", &(con->id));
    con->name = read_string(in);
    con->number = read_string(in);
    normal_number(con);
    return con;
}


void delete_contact(contact *contact) {
    free(contact->name);
    free(contact->number);
    free(contact);
}

unsigned count_contacts() {
    FILE *f = fopen(filename, "r");
    unsigned size = 0;
    while (!feof(f)) {
        contact *now = read_contact(f);
        size++;
        delete_contact(now);
    }
    fclose(f);
    return size - 1;
}


void create() {
    contact *new_con = read_contact(stdin);
    FILE *f = fopen(filename, "r");
    int id = 0;
    if (f == 0) {
        f = fopen(filename, "w");
        fclose(f);
        f = fopen(filename, "r");
    }
    unsigned cnt_con = count_contacts();
    for (unsigned i = 0; i < cnt_con; i++) {
        contact *now = read_contact(f);
        if (id < now->id)
            id = now->id;
        delete_contact(now);
    }
    fclose(f);
    f = fopen(filename, "a");
    fprintf(f, "%d %s %s\n", id + 1, new_con->name, new_con->number);
    fclose(f);
    delete_contact(new_con);
}


contact **read_contacts() {
    FILE *f = fopen(filename, "r");
    unsigned size = count_contacts();
    contact **contacts = (contact **) malloc(size * sizeof(contact *));
    for (int i = 0; i < size; i++) {
        contacts[i] = read_contact(f);
    }
    fclose(f);
    return contacts;
}

void delete(int id) {
    int q = 0;
    contact **contacts = read_contacts();
    unsigned size = count_contacts();
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < size; i++) {
        if (id != contacts[i]->id) {
            fprintf(f, "%d %s %s\n", contacts[i]->id, contacts[i]->name, contacts[i]->number);
            q = 1;
        }
        delete_contact(contacts[i]);
    }
    if (q == 0) {
        printf("ERROR! Incorrect name or number \n");
    }
    free(contacts);
    fclose(f);
}


void change_number(int id, char *number) {
    int q = 0;
    contact **contacts = read_contacts();
    unsigned size = count_contacts();
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < size; i++) {
        if (id == contacts[i]->id) {
            free(contacts[i]->number);
            contacts[i]->number = number;
            q = 1;
        }
        fprintf(f, "%d %s %s\n", contacts[i]->id, contacts[i]->name, contacts[i]->number);
        delete_contact(contacts[i]);
    }
    if (q == 0) {
        printf("ERROR! No such number\n");
    }
    fclose(f);
    free(contacts);
}


void change_name(int id, char *name) {
    int q = 0;
    contact **contacts = read_contacts();
    unsigned size = count_contacts();
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < size; i++) {
        if (id == contacts[i]->id) {
            free(contacts[i]->name);
            contacts[i]->name = name;
            q = 1;
        }
        fprintf(f, "%d %s %s\n", contacts[i]->id, contacts[i]->name, contacts[i]->number);
        delete_contact(contacts[i]);
    }
    if (q == 0) {
        printf("ERROR! No such name\n");
    }
    fclose(f);
    free(contacts);
}

char *substr(char *s, unsigned size) {
    char *new_s = (char *) malloc((size + 1) * sizeof(char));
    memcpy(new_s, s, sizeof(char) * size);
    new_s[size] = '\0';
    return new_s;
}

unsigned string_size(char *s) {
    unsigned size = 0;
    while (s[size] != '\0') size++;
    return size;
}


void find_contact(char *str) {
    int q = 0;
    contact **contacts = read_contacts();
    unsigned size = count_contacts();
    for (int i = 0; i < size; i++) {
        if (strcmp(contacts[i]->number, str) == 0) {
            printf("%d %s %s\n", contacts[i]->id, contacts[i]->name, contacts[i]->number);
            q = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        unsigned name_size = string_size(contacts[i]->name);
        for (int j = 0; j < name_size; j++) {
            for (int sz = 1; sz <= name_size - j; sz++) {
                char *s = substr(contacts[i]->name + j, sz);
                if (strcmp(s, str) == 0) {
                    printf("%d %s %s\n", contacts[i]->id, contacts[i]->name, contacts[i]->number);
                    q = 1;
                }
                free(s);
            }
        }
        delete_contact(contacts[i]);
    }
    if (q == 0) {
        printf("ERROR! Incorrect name or number \n");
    }
    free(contacts);
}


int main(int argc, char **argv) {
    filename = argv[1];
    while (0 == 0) {
        char *q = read_string(stdin);
        if (strcmp(q, "create") == 0) {
            create();
        }
        if (strcmp(q, "exit") == 0) {
            free(q);
            break;
        }
        if (strcmp(q, "delete") == 0) {
            int id;
            scanf("%d", &id);
            delete(id);
        }
        if (strcmp(q, "change") == 0) {
            int id;
            scanf("%d", &id);
            char *s = read_string(stdin);
            if (strcmp(s, "number") == 0) {
                char *num = read_string(stdin);
                change_number(id, num);
            } else {
                char *name = read_string(stdin);
                change_name(id, name);
            }
            free(s);
        }
        if (strcmp(q, "find") == 0) {
            char *s = read_string(stdin);
            find_contact(s);
            free(s);
        }
        free(q);
    }
    return 0;
}