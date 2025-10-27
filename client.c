// client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "player.h"

#define PORT 8080
#define BUFFER_SIZE 4096

void read_string(char *prompt, char *buf, int size) {
    printf("%s", prompt);
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = 0;
}

int main() {
    //realizando la conexion
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address\n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int choice;
    while (true) {
        //menu
        printf("Bienvenido\n");
        printf("1. Realizar busqueda (por short_name)\n");
        printf("2. Escribir un registro\n");
        printf("3. Leer a partir de numero de registro\n");
        printf("4. Salir\n");
        scanf("%d", &choice);
        getchar();

        send(sock, &choice, sizeof(int), 0);

        if (choice == 1) {
            char key[MAX_STR];
            read_string("Enter short name: ", key, MAX_STR);
            //envio al srvr
            send(sock, key, MAX_STR, 0);
            int len;
            //recivir los datos del srvr
            recv(sock, &len, sizeof(int), 0);
            char *response = malloc(len + 1);
            recv(sock, response, len, 0);
            response[len] = 0;
            printf("%s\n", response);
            free(response);
        } else if (choice == 2) {
            Player player;
            // Solicitar todos los campos al usuario
            printf("Enter player_id: ");
            scanf("%d", &player.player_id);
            getchar(); 
            read_string("Enter player_url: ", player.player_url, MAX_STR);
            printf("Enter fifa_version: ");
            scanf("%d", &player.fifa_version);
            getchar(); 
            printf("Enter fifa_update: ");
            scanf("%d", &player.fifa_update);
            getchar();
            read_string("Enter fifa_update_date: ", player.fifa_update_date, MAX_STR);
            read_string("Enter short_name: ", player.short_name, MAX_STR);
            read_string("Enter long_name: ", player.long_name, MAX_STR);
            read_string("Enter player_positions: ", player.player_positions, MAX_STR);
            printf("Enter overall: ");
            scanf("%d", &player.overall);
            getchar(); 
            printf("Enter potential: ");
            scanf("%d", &player.potential);
            getchar(); 
            printf("Enter value_eur: ");
            scanf("%lld", &player.value_eur);
            getchar(); 
            printf("Enter wage_eur: ");
            scanf("%lld", &player.wage_eur);
            getchar(); 
            printf("Enter age: ");
            scanf("%d", &player.age);
            getchar(); 
            read_string("Enter dob: ", player.dob, MAX_STR);
            printf("Enter height_cm: ");
            scanf("%d", &player.height_cm);
            getchar(); 
            printf("Enter weight_kg: ");
            scanf("%d", &player.weight_kg);
            getchar(); 
            printf("Enter league_id: ");
            scanf("%d", &player.league_id);
            getchar(); 
            read_string("Enter league_name: ", player.league_name, MAX_STR);
            printf("Enter league_level: ");
            scanf("%d", &player.league_level);
            getchar(); 
            printf("Enter club_team_id: ");
            scanf("%d", &player.club_team_id);
            getchar();
            read_string("Enter club_name: ", player.club_name, MAX_STR);
            read_string("Enter club_position: ", player.club_position, MAX_STR);
            printf("Enter club_jersey_number: ");
            scanf("%d", &player.club_jersey_number);
            getchar();
            read_string("Enter club_loaned_from: ", player.club_loaned_from, MAX_STR);
            read_string("Enter club_joined_date: ", player.club_joined_date, MAX_STR);
            printf("Enter club_contract_valid_until_year: ");
            scanf("%d", &player.club_contract_valid_until_year);
            getchar();
            printf("Enter nationality_id: ");
            scanf("%d", &player.nationality_id);
            getchar();
            read_string("Enter nationality_name: ", player.nationality_name, MAX_STR);
            printf("Enter nation_team_id: ");
            scanf("%d", &player.nation_team_id);
            getchar();
            read_string("Enter nation_position: ", player.nation_position, MAX_STR);
            printf("Enter nation_jersey_number: ");
            scanf("%d", &player.nation_jersey_number);
            getchar();
            read_string("Enter preferred_foot: ", player.preferred_foot, MAX_STR);
            printf("Enter weak_foot: ");
            scanf("%d", &player.weak_foot);
            getchar();
            printf("Enter skill_moves: ");
            scanf("%d", &player.skill_moves);
            getchar();
            printf("Enter international_reputation: ");
            scanf("%d", &player.international_reputation);
            getchar();
            read_string("Enter work_rate: ", player.work_rate, MAX_STR);
            read_string("Enter body_type: ", player.body_type, MAX_STR);
            read_string("Enter real_face: ", player.real_face, MAX_STR);
            printf("Enter release_clause_eur: ");
            scanf("%lld", &player.release_clause_eur);
            getchar();
            read_string("Enter player_tags: ", player.player_tags, MAX_STR);
            read_string("Enter player_traits: ", player.player_traits, MAX_STR);
            printf("Enter pace: ");
            scanf("%d", &player.pace);
            getchar();
            printf("Enter shooting: ");
            scanf("%d", &player.shooting);
            getchar(); 
            printf("Enter passing: ");
            scanf("%d", &player.passing);
            getchar(); 
            printf("Enter dribbling: ");
            scanf("%d", &player.dribbling);
            getchar();  
            printf("Enter defending: ");
            scanf("%d", &player.defending);
            getchar();  
            printf("Enter physic: ");
            scanf("%d", &player.physic);
            getchar();  
            printf("Enter attacking_crossing: ");
            scanf("%d", &player.attacking_crossing);
            getchar();  
            printf("Enter attacking_finishing: ");
            scanf("%d", &player.attacking_finishing);
            getchar();  
            printf("Enter attacking_heading_accuracy: ");
            scanf("%d", &player.attacking_heading_accuracy);
            getchar();  
            printf("Enter attacking_short_passing: ");
            scanf("%d", &player.attacking_short_passing);
            getchar();  
            printf("Enter attacking_volleys: ");
            scanf("%d", &player.attacking_volleys);
            getchar();  
            printf("Enter skill_dribbling: ");
            scanf("%d", &player.skill_dribbling);
            getchar();  
            printf("Enter skill_curve: ");
            scanf("%d", &player.skill_curve);
            getchar();  
            printf("Enter skill_fk_accuracy: ");
            scanf("%d", &player.skill_fk_accuracy);
            getchar();  
            printf("Enter skill_long_passing: ");
            scanf("%d", &player.skill_long_passing);
            getchar();  
            printf("Enter skill_ball_control: ");
            scanf("%d", &player.skill_ball_control);
            getchar();  
            printf("Enter movement_acceleration: ");
            scanf("%d", &player.movement_acceleration);
            getchar();  
            printf("Enter movement_sprint_speed: ");
            scanf("%d", &player.movement_sprint_speed);
            getchar();  
            printf("Enter movement_agility: ");
            scanf("%d", &player.movement_agility);
            getchar();  
            printf("Enter movement_reactions: ");
            scanf("%d", &player.movement_reactions);
            getchar();  
            printf("Enter movement_balance: ");
            scanf("%d", &player.movement_balance);
            getchar();  
            printf("Enter power_shot_power: ");
            scanf("%d", &player.power_shot_power);
            getchar();  
            printf("Enter power_jumping: ");
            scanf("%d", &player.power_jumping);
            getchar();  
            printf("Enter power_stamina: ");
            scanf("%d", &player.power_stamina);
            getchar();  
            printf("Enter power_strength: ");
            scanf("%d", &player.power_strength);
            getchar();  
            printf("Enter power_long_shots: ");
            scanf("%d", &player.power_long_shots);
            getchar();  
            printf("Enter mentality_aggression: ");
            scanf("%d", &player.mentality_aggression);
            getchar();  
            printf("Enter mentality_interceptions: ");
            scanf("%d", &player.mentality_interceptions);
            getchar();  
            printf("Enter mentality_positioning: ");
            scanf("%d", &player.mentality_positioning);
            getchar();  
            printf("Enter mentality_vision: ");
            scanf("%d", &player.mentality_vision);
            getchar();  
            printf("Enter mentality_penalties: ");
            scanf("%d", &player.mentality_penalties);
            getchar();  
            printf("Enter mentality_composure: ");
            scanf("%d", &player.mentality_composure);
            getchar();  
            printf("Enter defending_marking_awareness: ");
            scanf("%d", &player.defending_marking_awareness);
            getchar();  
            printf("Enter defending_standing_tackle: ");
            scanf("%d", &player.defending_standing_tackle);
            getchar();  
            printf("Enter defending_sliding_tackle: ");
            scanf("%d", &player.defending_sliding_tackle);
            getchar();  
            printf("Enter goalkeeping_diving: ");
            scanf("%d", &player.goalkeeping_diving);
            getchar();  
            printf("Enter goalkeeping_handling: ");
            scanf("%d", &player.goalkeeping_handling);
            getchar();  
            printf("Enter goalkeeping_kicking: ");
            scanf("%d", &player.goalkeeping_kicking);
            getchar();  
            printf("Enter goalkeeping_positioning: ");
            scanf("%d", &player.goalkeeping_positioning);
            getchar();  
            printf("Enter goalkeeping_reflexes: ");
            scanf("%d", &player.goalkeeping_reflexes);
            getchar();  
            printf("Enter goalkeeping_speed: ");
            scanf("%d", &player.goalkeeping_speed);
            getchar();  
            read_string("Enter ls: ", player.ls, MAX_STR);
            read_string("Enter st: ", player.st, MAX_STR);
            read_string("Enter rs: ", player.rs, MAX_STR);
            read_string("Enter lw: ", player.lw, MAX_STR);
            read_string("Enter lf: ", player.lf, MAX_STR);
            read_string("Enter cf: ", player.cf, MAX_STR);
            read_string("Enter rf: ", player.rf, MAX_STR);
            read_string("Enter rw: ", player.rw, MAX_STR);
            read_string("Enter lam: ", player.lam, MAX_STR);
            read_string("Enter cam: ", player.cam, MAX_STR);
            read_string("Enter ram: ", player.ram, MAX_STR);
            read_string("Enter lm: ", player.lm, MAX_STR);
            read_string("Enter lcm: ", player.lcm, MAX_STR);
            read_string("Enter cm: ", player.cm, MAX_STR);
            read_string("Enter rcm: ", player.rcm, MAX_STR);
            read_string("Enter rm: ", player.rm, MAX_STR);
            read_string("Enter lwb: ", player.lwb, MAX_STR);
            read_string("Enter ldm: ", player.ldm, MAX_STR);
            read_string("Enter cdm: ", player.cdm, MAX_STR);
            read_string("Enter rdm: ", player.rdm, MAX_STR);
            read_string("Enter rwb: ", player.rwb, MAX_STR);
            read_string("Enter lb: ", player.lb, MAX_STR);
            read_string("Enter lcb: ", player.lcb, MAX_STR);
            read_string("Enter cb: ", player.cb, MAX_STR);
            read_string("Enter rcb: ", player.rcb, MAX_STR);
            read_string("Enter rb: ", player.rb, MAX_STR);
            read_string("Enter gk: ", player.gk, MAX_STR);
            read_string("Enter player_face_url: ", player.player_face_url, MAX_STR);
            //enviar datos
            send(sock, &player, sizeof(Player), 0);
            int len;
            //recibir datos
            recv(sock, &len, sizeof(int), 0);
            char response[BUFFER_SIZE];
            recv(sock, response, len, 0);
            response[len] = 0;
            printf("%s\n", response);
        } else if (choice == 3) {
            int rec_num;
            printf("Enter record number: ");
            scanf("%d", &rec_num);
            //enviar datos
            send(sock, &rec_num, sizeof(int), 0);
            int len;
            recv(sock, &len, sizeof(int), 0);
            char *response = malloc(len + 1);
            recv(sock, response, len, 0);
            response[len] = 0;
            printf("%s\n", response);
            free(response);
        } else if (choice == 4) {
            break;
        }
    }

    close(sock);
    return 0;
}