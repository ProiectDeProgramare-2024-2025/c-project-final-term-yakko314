#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

struct Materie{
    char name[100];
    int noGrades;
    double grade[100];
};


struct Student{
    char clasa[100];
    char name[100];
    int noSubjects;
    /*char subject[100];
    int noGrades;
    float grade[100];*/
    struct Materie subjects[100];
};
struct Clasa {
    char name[100];
    int noStudents;
    struct Student students[100];
} clase[100];

struct StudentSimple {
    char name[100];
    double medianGrade;
    char clasa[100];
} studentsSimple[100];

void noStudent() {
    printf("Studentul " RED "nu exista " RESET "in baza de date!\n");
}
void noGrade() {
    printf("Nota " RED "nu exista " RESET "in baza de date!\n");
}
void noSubject() {
    printf("Materia " RED "nu exista " RESET "pentru elevul respectiv!\n");
}

int clasa_count;

void printGrades() {
    for (int i = 0; i < clasa_count; i++) {
        printf(MAG "===%s===\n" RESET, clase[i].name);
        // printf("%s\t|%s\t|", clase[i].name, clase[i].students[m].name);
        for (int m = 0; m < clase[i].noStudents; m++) {
            printf(BLU "%s\t\t" RESET "|", clase[i].students[m].name);
            for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                if(j > 0){
                    printf("\t\t\t|");
                }
                printf(RED "%s\t" RESET "|", clase[i].students[m].subjects[j].name);
                for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
                    printf(GRN "%.2f" RESET ", ", clase[i].students[m].subjects[j].grade[k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}
void addGrade(const char * argv[]) {
    int existaStudent = 0, existaMaterie = 0;
    for(int i = 0; i < clasa_count; i++){
        for (int m = 0; m < clase[i].noStudents; m++) {
            if(strcmp(argv[2], clase[i].name) == 0 && strcmp(argv[3], clase[i].students[m].name) == 0){
                existaStudent=1;
                for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                    if(strcmp(argv[4], clase[i].students[m].subjects[j].name) == 0){
                        existaMaterie = 1;
                        printf("Nota " GRN "%.2f " RESET
                            "i s-a adaugat elevului "
                            BLU "%s " RESET "din "
                            MAG "%s " RESET "la materia "
                            RED"%s" RESET ".\n",
                            atof(argv[5]), clase[i].students[m].name, clase[i].name, clase[i].students[m].subjects[j].name);
                        clase[i].students[m].subjects[j].grade[clase[i].students[m].subjects[j].noGrades++] = atof(argv[5]);
                    }
                }
            }
        }
    }
    if(!existaStudent){
        noStudent();
    }
    else{
        if(!existaMaterie){
            noSubject();
        }
    }
}
void modGrade(const char * argv[]) {
    int existaStudent = 0;
    int existaMaterie = 0;
    int existaNota = 0;
    for(int i = 0; i < clasa_count; i++){
        for (int m = 0; m < clase[i].noStudents; m++) {
            if(strcmp(argv[2], clase[i].name) == 0 && strcmp(argv[3], clase[i].students[m].name) == 0){
                existaStudent=1;
                for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                    if(strcmp(argv[4], clase[i].students[m].subjects[j].name) == 0){
                        existaMaterie = 1;
                        for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
                            if(clase[i].students[m].subjects[j].grade[k] == atof(argv[5])){
                                existaNota=1;
                                printf("Nota " GRN "%.2f " RESET "a elevului "
                                    BLU "%s "RESET "din "
                                    MAG "%s " RESET "la materia "
                                    RED "%s " RESET "a fost modificata in nota "
                                    GRN "%.2f" RESET".\n",
                                       clase[i].students[m].subjects[j].grade[k], clase[i].students[m].name, clase[i].name, clase[i].students[m].subjects[j].name, atof(argv[6]));
                                clase[i].students[m].subjects[j].grade[k] = atof(argv[6]);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if(!existaStudent){
        noStudent();
    }
    else{
        if(!existaMaterie){
            noSubject();
        }
        else if(!existaNota){
            noGrade();
        }
    }
}
void delGrade(const char * argv[]) {
    int existaStudent = 0;
    //fprintf(grades_file, "%d\n", clasa_count);
    int existaMaterie = 0;
    int existaNota = 0;
    for(int i = 0; i < clasa_count; i++){
        //(grades_file, "%s %d ", clase[i].name, clase[i].noStudents);
        for (int m = 0; m < clase[i].noStudents; m++) {
            //fprintf(grades_file, "%s %d ", clase[i].students[m].name, clase[i].students[m].noSubjects);
            if(strcmp(argv[2], clase[i].name) == 0 && strcmp(argv[3], clase[i].students[m].name) == 0){
                existaStudent=1;
                for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                    if(strcmp(argv[4], clase[i].students[m].subjects[j].name) == 0){
                        existaMaterie = 1;
                        for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
                            //printf("%.2f\n", clase[i].students[m].subjects[j].grade[k]);
                            //printf("%f %f\n", clase[i].students[m].subjects[j].grade[k], atof(argv[5]));
                            if(clase[i].students[m].subjects[j].grade[k] == atof(argv[5])){
                                existaNota=1;
                                printf("Nota "
                                    GRN "%.2f " RESET"a elevului "
                                    BLU"%s "RESET "din "
                                    MAG "%s " RESET "la materia "
                                    RED "%s " RESET "a fost stearsa.\n",
                                       clase[i].students[m].subjects[j].grade[k],
                                       clase[i].students[m].name,
                                       clase[i].name,
                                       clase[i].students[m].subjects[j].name);
                                //clase[i].students[m].subjects[j].grade[k] = 0;
                                for(int l = k; l < clase[i].students[m].subjects[j].noGrades - 1; l++){
                                    clase[i].students[m].subjects[j].grade[l] = clase[i].students[m].subjects[j].grade[l+1];
                                }
                                clase[i].students[m].subjects[j].noGrades--;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if(!existaStudent){
        noStudent();
    }
    else{
        if(!existaMaterie){
            noSubject();
        }
        else if(!existaNota){
            noGrade();
        }
    }
}
int validateGrade(double const grade) {
    if (grade >= 1 && grade <= 10) {
        return 1;
    }
    printf(RED "Nota invalida!" RESET " Notele trebuie sa se afla in intervalul " GRN "1.00" RESET " - "GRN "10.00.\n" RESET);
    return 0;
}

void populateStudentsSimple(int student_count, int i, int m) {
    // printf("Suntem la studentul %d\n", student_count);
    strcpy(studentsSimple[student_count].name, clase[i].students[m].name);
    strcpy(studentsSimple[student_count].clasa, clase[i].name);
    studentsSimple[student_count].medianGrade = 0;
    // printf("%s\t|%s\t|\n\n", clase[i].name, clase[i].students[m].name);
    for(int j = 0; j < clase[i].students[m].noSubjects; j++){
        double mediaMica = 0;
        for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
            mediaMica += clase[i].students[m].subjects[j].grade[k];
        }
        if (clase[i].students[m].subjects[j].noGrades != 0) {
            mediaMica = mediaMica / clase[i].students[m].subjects[j].noGrades;
        }
        else
            mediaMica = 0;
        //printf("Se adauga media %.2f de la disciplina %s lui %s\n", mediaMica, clase[i].students[m].subjects[j].name, clase[i].students[m].name);
        studentsSimple[student_count].medianGrade += mediaMica;
        // printf("Media a devenit %.2f de la disciplina %s lui %s\n", studentsSimple[student_count].medianGrade, "aaa", studentsSimple[student_count].name);
    }
    studentsSimple[student_count].medianGrade /= clase[i].students[m].noSubjects;
    // printf("%s are media %.2f.\n", studentsSimple[student_count].name, studentsSimple[student_count].medianGrade);
}

void sortStudentByMedian(int student_count) {
    for (int i = 0; i < student_count; i++) {
        for (int j = 0 ; j < student_count-i; j++) {
            if (studentsSimple[j].medianGrade < studentsSimple[j+1].medianGrade) {
                struct StudentSimple temp = studentsSimple[j];
                studentsSimple[j] = studentsSimple[j+1];
                studentsSimple[j+1] = temp;
            }
        }
    }
}
void printSortedStudents(int student_count) {
    for (int i = 0; i < student_count+1; i++) {
        printf(BLU "%s \t " RESET "|"
                    MAG " %s \t " RESET "|"
                    GRN " %.2f \n" RESET,
                    studentsSimple[i].name, studentsSimple[i].clasa, studentsSimple[i].medianGrade);
    }
}

void readFile(){
    FILE* grades_file = fopen("students.txt", "r");
    fscanf(grades_file, "%d ", &clasa_count);
    for (int i = 0; i < clasa_count; i++) {
        fscanf(grades_file, "%s %d", clase[i].name, &clase[i].noStudents);
        //printf("%s %d\n", clase[i].name, clase[i].noStudents);
        for (int m = 0; m < clase[i].noStudents; m++) {
            fscanf(grades_file, "%s", clase[i].students[m].name);
            fscanf(grades_file, "%d", &clase[i].students[m].noSubjects);
            //printf("%s\t|%s\t|", clase[i].name, clase[i].students[m].name);
            for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                fscanf(grades_file, "%s", clase[i].students[m].subjects[j].name);
                fscanf(grades_file, "%d", &clase[i].students[m].subjects[j].noGrades);
                /*if(j > 0){
                    printf("\t\t\t|");
                }*/
                //printf("%s\t|", clase[i].students[m].subjects[j].name);
                for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
                    fscanf(grades_file, "%lf", &clase[i].students[m].subjects[j].grade[k]);
                    //printf("%.2f, ", clase[i].students[m].subjects[j].grade[k]);
                }
                // printf("\n");
            }
            // printf("\n");
        }
        // printf("\n");
    }
    fclose(grades_file);
}
void writeFile() {
    FILE* grades_file = fopen("students.txt", "w");
    fprintf(grades_file, "%d\n", clasa_count);
    for(int i = 0; i < clasa_count; i++){
        fprintf(grades_file, "%s %d \n", clase[i].name, clase[i].noStudents);
        for (int m = 0; m < clase[i].noStudents; m++) {
            fprintf(grades_file, "%s %d\n", clase[i].students[m].name, clase[i].students[m].noSubjects);
            for(int j = 0; j < clase[i].students[m].noSubjects; j++){
                fprintf(grades_file, "%s %d ", clase[i].students[m].subjects[j].name, clase[i].students[m].subjects[j].noGrades);
                for(int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++){
                    fprintf(grades_file, "%.2f ", clase[i].students[m].subjects[j].grade[k]);
                }
            }
            fprintf(grades_file, "\n");
        }
        fprintf(grades_file, "\n");
    }
    fclose(grades_file);
}

void genClassMedian(int i, double *mediaClasa) {
    for (int m = 0; m < clase[i].noStudents; m++) {
        double media = 0;
        for(int j = 0; j < clase[i].students[m].noSubjects; j++) {
            double mediaMat = 0;
            for (int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++) {
                mediaMat += clase[i].students[m].subjects[j].grade[k];
            }
            mediaMat /= clase[i].students[m].subjects[j].noGrades;
            media += mediaMat;
        }
        media /= clase[i].students[m].noSubjects;
        //printf("Se adauga media %.2f a studentului %s\n", media, clase[i].students[m].name);
        *mediaClasa += media;
    }
}
void genStudentMedian(int i, int m, double *media) {
    for(int j = 0; j < clase[i].students[m].noSubjects; j++) {
        double mediaMat = 0;
        for (int k = 0; k < clase[i].students[m].subjects[j].noGrades; k++) {
            mediaMat += clase[i].students[m].subjects[j].grade[k];
        }
        mediaMat /= clase[i].students[m].subjects[j].noGrades;
        *media += mediaMat;
    }
}

void notYetImplemented(){
    printf(RED "Nu este inca implementat.\n" RESET);
}
void cmdHelpTypes();
void cmdHelp(){
    printf(RESET "Comenzile disponibile sunt:\n" RESET);
    printf("show_grades" RESET " - " BLU "Afiseasa toate notele\n" RESET);
    printf("add_grade" GRN " <clasa> <elev> <materie> <nota>" RESET " - " BLU "Adauga o nota\n" RESET);
    printf("mod_grade" GRN " <clasa> <elev> <materie> <nota_veche> <nota_noua>"RESET" - "BLU"Modifica o nota\n"RESET);
    printf("del_grade" GRN " <clasa> <elev> <materie> <nota>"RESET" - "BLU" Sterge o nota\n"RESET);
    printf("\tNotele introduse trebuie sa se afle in intervalul " GRN "1.00 "RESET "- "GRN "10.00.\n" RESET);
    printf("stats" GRN " <tip>"RESET" - "BLU "Afiseaza diverste statistici. Tipuri disponibile:\n" RESET);
    cmdHelpTypes();
}
void cmdHelpTypes() {
    printf(GRN "\t top_student_median" RESET " - " BLU "Top elevi in functie de medie\n" RESET);
    printf(GRN "\t best_in_class" RESET " - " BLU "Cel mai bun elev din fiecare clasa\n" RESET);
    printf(GRN "\t average_per_class" RESET " - " BLU "Media generala a fiecarei clase\n" RESET);
}

int main(int argc, const char * argv[]) {
    if(argc == 1){
        cmdHelp();
        return 0;
    }
    if(strcmp(argv[1], "help") == 0){
        cmdHelp();
    }
    else if (strcmp(argv[1], "show_grades") == 0) {
        readFile();
        printGrades();
    } else
    if (strcmp(argv[1], "add_grade") == 0) {
        if (argc != 6) {
            printf(RED "Sintaxa invalida! " RESET
                "Corecta: " GRN "add_grade <clasa> <elev> <materie> <nota>\n" RESET);
            return 1;
        }
        if (!validateGrade(atof(argv[5]))) return 1;
        readFile();
        addGrade(argv);
        writeFile();
        } else
    if (strcmp(argv[1], "mod_grade") == 0) {
        if (argc != 7) {
            printf(RED "Sintaxa invalida! " RESET
                "Corecta: " GRN "mod_grade <clasa> <elev> <materie> <nota_veche> <nota_noua>\n" RESET);
            return 1;
        }
        if (!validateGrade(atof(argv[6]))) return 1;
        readFile();
        modGrade(argv);
        writeFile();
    } else
    if (strcmp(argv[1], "del_grade") == 0) {
        if (argc != 6) {
            printf(RED "Sintaxa invalida! " RESET
                "Corecta: " GRN "del_grade <clasa> <elev> <materie> <nota>\n" RESET);
            return 1;
        }
        if (!validateGrade(atof(argv[5]))) return 1;
        readFile();
        delGrade(argv);
        writeFile();
    } else
    if (strcmp(argv[1], "stats") == 0) {
        if (argc != 3) {
            printf(RED "Sintaxa invalida! " RESET
                "Corecta: " GRN "stats <tip>" RESET ". Tipuri disponibile:\n");
            cmdHelpTypes();
            return 1;
        }
        if(strcmp(argv[2], "top_student_median") == 0){
            readFile();
            int student_count = -1;
            for (int i = 0; i < clasa_count; i++) {
                for (int m = 0; m < clase[i].noStudents; m++) {
                    student_count++;
                    populateStudentsSimple(student_count, i,m);
                }
            }
            sortStudentByMedian(student_count);
            printSortedStudents(student_count);
        }
        else if(strcmp(argv[2], "best_in_class") == 0){
            readFile();
            for (int i = 0; i < clasa_count; i++) {
                printf(MAG "============%s===========\n" RESET, clase[i].name);
                double max = 0; char maxName[100];
                for (int m = 0; m < clase[i].noStudents; m++) {
                    double media = 0;
                    genStudentMedian(i, m, &media);
                    media /= clase[i].students[m].noSubjects;
                    //printf("%.2f %s\n", media, clase[i].students[m].name);
                    if (media > max) {
                        max = media;
                        strcpy(maxName, clase[i].students[m].name);
                    }
                }
                printf(BLU "%s \t " RESET "|"
                    GRN " %.2f \n" RESET,
                    maxName, max);

            }

        }
        else if(strcmp(argv[2], "average_per_class") == 0){
            readFile();
            for (int i = 0; i < clasa_count; i++) {
                printf(MAG "===%s===\n" RESET, clase[i].name);
                double mediaClasa = 0;
                genClassMedian(i, &mediaClasa);
                mediaClasa /= clase[i].noStudents;
                printf(GRN "%.2f\n" RESET, mediaClasa);
            }
        }
        else{
            printf(RED "Tip indisponibil! " RESET
                "Tipuri disponibile:\n");
            cmdHelpTypes();
            return 1;
        }

    }
    else{
        printf(RED "Opțiune lipsă! " RESET
            "Pentru a vedea o listă cu toate comenzile accesibile folosiți opțiunea " GRN "help" RESET "!\n");
    }
}
