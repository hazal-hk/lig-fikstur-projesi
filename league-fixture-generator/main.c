#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEAMS 20

void readTeams(char teams[][50], int *teamCount){
    FILE *file=fopen("takimlar.txt","r");
    if (!file) {
        printf("Could not open file takimlar.txt !\n");
        exit(1);
    }
    *teamCount=0;
    while (fgets(teams[*teamCount], 50, file)){
        teams[*teamCount][strcspn(teams[*teamCount], "\n")]='\0';
        (*teamCount)++;
    }
    fclose(file);

    if (*teamCount % 2 == 0) {
        printf("The number of teams must be odd! Please add or remove a team.\n");
        exit(1);
    }
}
void writeFixture(char teams[][50], int teamCount) {
    FILE *file = fopen("fikstur.txt", "w");
    if (!file) {
        printf("fikstur.txt file could not be created!\n");
        exit(1);
    }
    int rounds = teamCount - 1;
    int matchesPerRound = teamCount / 2;

    char tempTeams[MAX_TEAMS][50];
    for (int i = 0; i < teamCount; i++) {
        strcpy(tempTeams[i], teams[i]);
    }

    for(int round=0; round<rounds*2; round++){
        fprintf(file, "%d. Week \n", round + 1);
        printf("%d. Week \n",round + 1);

        for (int match = 0; match < matchesPerRound; match++) {
            int home = match;
            int away = teamCount - 1 - match;

            if (round >= rounds) {
                fprintf(file, "%s vs %s\n", tempTeams[away], tempTeams[home]);
                printf("%s vs %s\n", tempTeams[away], tempTeams[home]);
            } else {
                fprintf(file, "%s vs %s\n", tempTeams[home], tempTeams[away]);
                printf("%s vs %s\n", tempTeams[home], tempTeams[away]);
            }
        }
        fprintf(file, "Team that will not play this week: %s\n\n", tempTeams[round % (teamCount - 1)]);
        printf("Team that will not play this week: %s\n\n", tempTeams[round % (teamCount - 1)]);

        char temp[50];
        strcpy(temp, tempTeams[teamCount - 1]);
        for (int i = teamCount - 1; i > 1; i--) {
            strcpy(tempTeams[i], tempTeams[i - 1]);
        }
        strcpy(tempTeams[1], temp);
    }

    fclose(file);
    printf("Fixtures are written to the file 'fikstur.txt'.\n");
}

int main() {
    char teams[MAX_TEAMS][50];
    int teamCount;

    readTeams(teams, &teamCount);
    writeFixture(teams, teamCount);

    return 0;
}














