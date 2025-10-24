#include <_stdio.h>
#include <_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 4096
#define EXO_NUMBER 48


// Fonction pour lire un fichier et afficher la réponse à une question spécifique
int afficher_reponse(FILE *file, int question_num) {
    char line[MAX_LINE_LENGTH];
    int current_question = 0;
    int found_question = 0;
    int multiLineAnswer = 0;
    while (fgets(line, sizeof(line), file)) {
        // Vérification de la question avec la chaîne "- []"
        if (strncmp(line, "- [ ]", 5) == 0 || strncmp(line, "- [x]", 4) == 0) {
            current_question++;
            if (current_question == question_num) {
                found_question = 1;
            }
            else if (found_question){
                found_question = 0;
                multiLineAnswer = 0;
                return 0;
            }

        }

        // Si la question est trouvée, afficher la réponse jusqu'à la prochaine question
        if (found_question) {
            if (multiLineAnswer){
                printf("%s",line);
            }
            else{
                int done = !(strncmp(line, "- [x]", 5));
                printf("Question %i : %s \n", question_num, done ? "Faite" : "Non faite" );
                char* fResponse = line+5;
                printf("Réponse - %s",fResponse);
                multiLineAnswer = 1;
            }

        }
    }
    if (!found_question) {
        printf("Question %d introuvable.\n", question_num);
        return -1;
    }

    return -1;
}

// Cette fonction sert à vérifier les exercices finis
int checkAllResponses(FILE *file){
    char line[MAX_LINE_LENGTH];
    int current_question = 0;
    int found_question = 0;
    while (fgets(line, sizeof(line), file)) {
        // Vérification de la question avec la chaîne "- []"
        if (strncmp(line, "- [ ]", 5) == 0 || strncmp(line, "- [x]", 4) == 0) {
            current_question++;
            if (!(strncmp(line, "- [x]", 5))) {
                found_question++;
            }
        }
        }
    return found_question;
}



// mad stands for mark as done
// Cette fonction sert à cocher un exercice en particulier dans le fichier passé en argument
int madQuestion(char* fname, int exo_number){
    if (exo_number > EXO_NUMBER){
        return 0;
    }
    FILE *file = fopen(fname, "r");
    int fd = fileno(file);
    struct stat fInfo;
    int stResult = fstat(fd, &fInfo);
    int fSize = stResult == 0 ? fInfo.st_size : 0;
    char line[MAX_LINE_LENGTH];
    char *buffer = (char*)calloc(1,fSize+1);
    int current_exo = 0;

    // Boucle lisant le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)){
        if (strncmp(line, "- [ ]", 5) == 0 || strncmp(line, "- [x]", 5) == 0){
            if (current_exo == exo_number-1){
                if (strncmp(line, "- [x]", 5) == 0){
                    printf("Cette question à déjà été cochée \n");
                    return 0;
                }
                else{
                    strlcat(buffer, "- [x]", fSize+1);
                    int taille = strlcat(buffer, line+5, fSize+1);
                }
            }
            else{
                 int taille = strlcat(buffer, line, fSize+1);
            }

            current_exo++;
        }
        else{
                 int taille = strlcat(buffer, line, fSize+1);
        }
    }
    fclose(file);
    file = fopen(fname, "w");
    // écriture du buffer vers le fichier
    fwrite(buffer, fSize,1,file);
    fclose(file);
    return 0;
}

// maud stands for Marks as not done
// Cette fonction sert à décocher un exercice en particulier dans le fichier passé en argument
int mandQuestion(char* fname, int exo_number){
    if (exo_number > EXO_NUMBER){
        printf("Cette question n'existe pas \n");
        return 1;
    }
    FILE *file = fopen(fname, "r");
    int fd = fileno(file);
    struct stat fInfo;
    int stResult = fstat(fd, &fInfo);
    int fSize = stResult == 0 ? fInfo.st_size : 0;
    char line[MAX_LINE_LENGTH];
    char *buffer = (char*)calloc(1,fSize+1);
    int current_exo = 0;
    int questionOffset = 0;
    //printf("contenu de la str %s \n", line);
    //Boucle qui lit le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)){
        questionOffset += strlen(line);
        if (strncmp(line, "- [ ]", 5) == 0 || strncmp(line, "- [x]", 5) == 0){
            if (current_exo == exo_number-1){
                if (strncmp(line, "- [ ]", 5) == 0){
                    printf("Cette question à déjà été décochée \n");
                    return 0;
                }
                else{
                    strlcat(buffer, "- [ ]", fSize+1);
                    int taille = strlcat(buffer, line+5, fSize+1);
                }
            }
            else{
                 int taille = strlcat(buffer, line, fSize+1);
            }

            current_exo++;
        }
        else{
                 int taille = strlcat(buffer, line, fSize+1);
        }
    }
    fclose(file);
    file = fopen(fname, "w");
    // écriture du buffer vers le fichier
    fwrite(buffer, fSize,1,file);
    fclose(file);
    return 0;
}

int addResponse(char* fname, int exo_number, char* response){
    if (exo_number > EXO_NUMBER){
        printf("Cette question n'existe pas \n");
        return 1;
    }
    FILE *file = fopen(fname, "r");
    int fd = fileno(file);
    struct stat fInfo; int stResult = fstat(fd, &fInfo); int fSize = stResult == 0 ? fInfo.st_size : 0;
    char line[MAX_LINE_LENGTH];
    char *buffer = (char*)calloc(1,fSize+1+strlen(response));
    int current_exo = 0; int questionOffset = 0;
    //Boucle qui lit le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)){
        questionOffset += strlen(line);
        if (strncmp(line, "- [ ]", 5) == 0 || strncmp(line, "- [x]", 5) == 0){
            if (current_exo == exo_number-1){
                if (strncmp(line, "- [x]", 5) == 0){
                    printf("Question déjà cochée, ajout d'une réponse\n");
                    int taille = strlcat(buffer, line, fSize+1);
                    int taille2 = strlcat(buffer, response, fSize+1+strlen(response));
                }
                else{
                    printf("Question non cochée, ajout d'une réponse\n");
                    strlcat(buffer, "- [x]", fSize+1);
                    int taille = strlcat(buffer, line+5, fSize+1);
                    int taille2 = strlcat(buffer, response, fSize+1+strlen(response));
                }
            }
            else{
                 int taille = strlcat(buffer, line, fSize+1);
            }

            current_exo++;
        }
        else{
                 int taille = strlcat(buffer, line, fSize+1);
        }
    }
    fclose(file);
    file = fopen(fname, "w");
    // écriture du buffer vers le fichier
    fwrite(buffer, fSize,1,file);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilisation: %s <fichier.txt> -q <numéro de question>\n", argv[0]);
        return 1;
    }
    int question_num = 0;
    char* mode = argv[1];
    // Vérification de l'option -q et récupération du numéro de question
    if (!(strcmp(argv[1], "q"))){
        if (strcmp(argv[1], "q") != 0 || argc != 3) {
            printf("Argument invalide. Utilisation: -q <numéro de question>\n");
             return 1;
        }
        else{
            question_num = atoi(argv[2]);
        }
    }


    if (question_num <= 0 && !(strcmp(argv[1], "q"))) {
        printf("Le numéro de question doit être un entier positif.\n");
        return 1;
    }


    if (!strcmp(argv[1], "chk")){
        if (strcmp(argv[1], "chk") != 0 || argc != 3){
            printf("Argument invalide. Utilisation: -check <numéro de question>\n");
            return 1;
        }
        else{
           question_num = atoi(argv[2]);
        }
    }

    if (!strcmp(argv[1], "uchk")){
        if (strcmp(argv[1], "uchk") != 0 || argc != 3){
            printf("Argument invalide. Utilisation: -ucheck <numéro de question>\n");
            return 1;
        }
        else{
            question_num = atoi(argv[2]);
        }
    }

    if (question_num <= 0 && (!(strcmp(argv[1], "chk")) ||!(strcmp(argv[1], "-ucheck")) )) {
        printf("Le numéro de question doit être un entier positif.\n");
        return 1;
    }

    if (!strcmp(argv[1], "add")){
        if (strcmp(argv[1], "add") || argc != 4){
            printf("Argument invalide. Utilisation: add <numéro de question> \"<contenu de la reponse>\" \n");
            return 1;
        }
        else{
           question_num = atoi(argv[2]);
        }
    }

    // Ouverture du fichier
    FILE *file = fopen("README.txt", "r");

    if (file == NULL) {
        write(2, "ERREUR OUVERTURE", 25);
        return 1;
    }
    if (!strcmp(argv[1], "q") && argc == 3){
        if (afficher_reponse(file, question_num) != 0){
            fclose(file);
            return 1;
        }
        else{
            fclose(file);
            return 0;
        }
    }
    if (!strcmp(argv[1], "chk") && argc == 3){
        if (madQuestion("README.txt", question_num) != 0){
            perror("ERROR");
            fclose(file);
            return 1;
        }
        else{
            fclose(file);
            return 0;
        }
    }

    if (!strcmp(argv[1], "uchk") && argc == 3){
        if (mandQuestion("README.txt", question_num) != 0){
            perror("ERROR");
            fclose(file);
            return 1;
        }
        else{
            fclose(file);
            return 0;
        }
    }

    if (!strcmp(argv[1], "add") && argc == 4){
        if (addResponse("README.txt", question_num, argv[3]) != 0){
            perror("ERROR");
            fclose(file);
            return 1;
        }
        else{
            fclose(file);
            return 0;
        }
    }
    if (!strcmp(argv[1], "qAll") && argc==2){
        int nbExoFait = checkAllResponses(file);
        printf(
            "%s \n%i/%i exos de faits \n",
            nbExoFait == EXO_NUMBER ? "Tout les exos ont été faits" : "Il manque des exos",
            nbExoFait,
            EXO_NUMBER);
    }
    // Affichage de la réponse à la question demandée

    // Fermeture du fichier
    fclose(file);
    return 0;
}