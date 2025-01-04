/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** split string
*/

#include "my_str_to_word_array.h"
#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"

int check_special_one(char i)
{
    if ((i >= 32 && i <= 47) ||
        (i >= 91 && i <= 96) ||
        (i >= 58 && i <= 64)) {
            return 1;
    }
    return 0;
}

int count_words(char const *str)
{
    int nb_word = 0;
    int i = 0;
    int switch_word = 0;

    while (str[i] != '\0') {
        if (check_special_one(str[i]) == 0 && switch_word == 0) {
            switch_word = 1;
            nb_word++;
        }
        if (check_special_one(str[i]) == 1) {
            switch_word = 0;
        }
        i++;
    }
    return nb_word;
}

void fill_the_array(parsing_t *parsing, char const *str, char **word_array)
{
    for (parsing->index = 0; parsing->index < parsing->len;
        parsing->index++) {
            word_array[parsing->stk][parsing->index] =
            str[parsing->i - parsing->len + parsing->index];
    }
    word_array[parsing->stk][parsing->len] = '\0';
    parsing->stk++;
}

void extract_word(parsing_t *parsing, char const *str)
{
    parsing->len = 0;
    while (check_special_one(str[parsing->i]) == 1 &&
        str[parsing->i] != '\0') {
        parsing->i++;
    }
    while (check_special_one(str[parsing->i]) == 0 &&
        str[parsing->i] != '\0') {
        parsing->len++;
        parsing->i++;
    }
}

char *alloc_memory_for_the_words(parsing_t *parsing, char **word_array)
{
    if (parsing->len > 0) {
        word_array[parsing->stk] = malloc(sizeof(char) * (parsing->len + 1));
        if (word_array[parsing->stk] == NULL)
            return NULL;
    }
    return NULL;
}

char **my_str_to_word_array(char const *str)
{
    parsing_t parsing = {0};
    int nb_words = count_words(str);
    char **word_array = malloc(sizeof(char *) * (nb_words + 1));

    if (word_array == NULL)
        return NULL;
    while (str[parsing.i] != '\0') {
        extract_word(&parsing, str);
        alloc_memory_for_the_words(&parsing, word_array);
        fill_the_array(&parsing, str, word_array);
    }
    word_array[parsing.stk] = NULL;
    return word_array;
}

int main(void)
{
    char *str = "O what can ail thee, knight-at-arms,"
                "Alone and palely loitering?"
                "The sedge has withered from the lake,"
                "And no birds sing"
    char **word_array = my_str_to_word_array(str);

    for(int i = 0; word_array[i] != NULL; i++) {
        printf("%s\n", word_array[i]);
    }
    return 0;
}
