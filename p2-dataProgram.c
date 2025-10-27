// p2-dataProgram.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include "player.h"

#define PORT 8080
#define HASH_SIZE 10007
#define BUFFER_SIZE 4096

typedef struct Node {
    long offset;
    struct Node *next;
} Node;

Node *hash_table[HASH_SIZE];
//funcion hash
unsigned long hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c; // h * 33 + c
    return h % HASH_SIZE;
}

void add_to_hash(const char *key, long offset) {
    unsigned long h = hash(key);
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("malloc");
        exit(1);
    }
    new_node->offset = offset;
    new_node->next = hash_table[h];
    hash_table[h] = new_node;
}
// liberar
void free_hash() {
    for (int i = 0; i < HASH_SIZE; i++) {
        Node *node = hash_table[i];
        while (node) {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }
}
//Analisar la linea
int parse_csv_line(char *line, char **fields) {
    int count = 0;
    char *pos = line;
    char *start = line;
    int in_quote = 0;

    while (*pos) {
        if (*pos == '"') {
            in_quote = !in_quote;
        } else if (*pos == ',' && !in_quote) {
            *pos = '\0';
            if (start[0] == '"') {
                start++;
                pos[-1] = '\0';
            }
            fields[count++] = start;
            start = pos + 1;
        }
        pos++;
    }
    if (start[0] == '"') {
        start++;
        pos[-1] = '\0';
    }
    fields[count++] = start;
    return count;
}

void assign_fields_to_player(Player *player, char **fields) {
    player->player_id = atoi(fields[0]);
    strncpy(player->player_url, fields[1], MAX_STR - 1);
    player->fifa_version = atoi(fields[2]);
    player->fifa_update = atoi(fields[3]);
    strncpy(player->fifa_update_date, fields[4], MAX_STR - 1);
    strncpy(player->short_name, fields[5], MAX_STR - 1);
    strncpy(player->long_name, fields[6], MAX_STR - 1);
    strncpy(player->player_positions, fields[7], MAX_STR - 1);
    player->overall = atoi(fields[8]);
    player->potential = atoi(fields[9]);
    player->value_eur = atoll(fields[10]);
    player->wage_eur = atoll(fields[11]);
    player->age = atoi(fields[12]);
    strncpy(player->dob, fields[13], MAX_STR - 1);
    player->height_cm = atoi(fields[14]);
    player->weight_kg = atoi(fields[15]);
    player->league_id = atoi(fields[16]);
    strncpy(player->league_name, fields[17], MAX_STR - 1);
    player->league_level = atoi(fields[18]);
    player->club_team_id = atoi(fields[19]);
    strncpy(player->club_name, fields[20], MAX_STR - 1);
    strncpy(player->club_position, fields[21], MAX_STR - 1);
    player->club_jersey_number = atoi(fields[22]);
    strncpy(player->club_loaned_from, fields[23], MAX_STR - 1);
    strncpy(player->club_joined_date, fields[24], MAX_STR - 1);
    player->club_contract_valid_until_year = atoi(fields[25]);
    player->nationality_id = atoi(fields[26]);
    strncpy(player->nationality_name, fields[27], MAX_STR - 1);
    player->nation_team_id = atoi(fields[28]);
    strncpy(player->nation_position, fields[29], MAX_STR - 1);
    player->nation_jersey_number = atoi(fields[30]);
    strncpy(player->preferred_foot, fields[31], MAX_STR - 1);
    player->weak_foot = atoi(fields[32]);
    player->skill_moves = atoi(fields[33]);
    player->international_reputation = atoi(fields[34]);
    strncpy(player->work_rate, fields[35], MAX_STR - 1);
    strncpy(player->body_type, fields[36], MAX_STR - 1);
    strncpy(player->real_face, fields[37], MAX_STR - 1);
    player->release_clause_eur = atoll(fields[38]);
    strncpy(player->player_tags, fields[39], MAX_STR - 1);
    strncpy(player->player_traits, fields[40], MAX_STR - 1);
    player->pace = atoi(fields[41]);
    player->shooting = atoi(fields[42]);
    player->passing = atoi(fields[43]);
    player->dribbling = atoi(fields[44]);
    player->defending = atoi(fields[45]);
    player->physic = atoi(fields[46]);
    player->attacking_crossing = atoi(fields[47]);
    player->attacking_finishing = atoi(fields[48]);
    player->attacking_heading_accuracy = atoi(fields[49]);
    player->attacking_short_passing = atoi(fields[50]);
    player->attacking_volleys = atoi(fields[51]);
    player->skill_dribbling = atoi(fields[52]);
    player->skill_curve = atoi(fields[53]);
    player->skill_fk_accuracy = atoi(fields[54]);
    player->skill_long_passing = atoi(fields[55]);
    player->skill_ball_control = atoi(fields[56]);
    player->movement_acceleration = atoi(fields[57]);
    player->movement_sprint_speed = atoi(fields[58]);
    player->movement_agility = atoi(fields[59]);
    player->movement_reactions = atoi(fields[60]);
    player->movement_balance = atoi(fields[61]);
    player->power_shot_power = atoi(fields[62]);
    player->power_jumping = atoi(fields[63]);
    player->power_stamina = atoi(fields[64]);
    player->power_strength = atoi(fields[65]);
    player->power_long_shots = atoi(fields[66]);
    player->mentality_aggression = atoi(fields[67]);
    player->mentality_interceptions = atoi(fields[68]);
    player->mentality_positioning = atoi(fields[69]);
    player->mentality_vision = atoi(fields[70]);
    player->mentality_penalties = atoi(fields[71]);
    player->mentality_composure = atoi(fields[72]);
    player->defending_marking_awareness = atoi(fields[73]);
    player->defending_standing_tackle = atoi(fields[74]);
    player->defending_sliding_tackle = atoi(fields[75]);
    player->goalkeeping_diving = atoi(fields[76]);
    player->goalkeeping_handling = atoi(fields[77]);
    player->goalkeeping_kicking = atoi(fields[78]);
    player->goalkeeping_positioning = atoi(fields[79]);
    player->goalkeeping_reflexes = atoi(fields[80]);
    player->goalkeeping_speed = atoi(fields[81]);
    strncpy(player->ls, fields[82], MAX_STR - 1);
    strncpy(player->st, fields[83], MAX_STR - 1);
    strncpy(player->rs, fields[84], MAX_STR - 1);
    strncpy(player->lw, fields[85], MAX_STR - 1);
    strncpy(player->lf, fields[86], MAX_STR - 1);
    strncpy(player->cf, fields[87], MAX_STR - 1);
    strncpy(player->rf, fields[88], MAX_STR - 1);
    strncpy(player->rw, fields[89], MAX_STR - 1);
    strncpy(player->lam, fields[90], MAX_STR - 1);
    strncpy(player->cam, fields[91], MAX_STR - 1);
    strncpy(player->ram, fields[92], MAX_STR - 1);
    strncpy(player->lm, fields[93], MAX_STR - 1);
    strncpy(player->lcm, fields[94], MAX_STR - 1);
    strncpy(player->cm, fields[95], MAX_STR - 1);
    strncpy(player->rcm, fields[96], MAX_STR - 1);
    strncpy(player->rm, fields[97], MAX_STR - 1);
    strncpy(player->lwb, fields[98], MAX_STR - 1);
    strncpy(player->ldm, fields[99], MAX_STR - 1);
    strncpy(player->cdm, fields[100], MAX_STR - 1);
    strncpy(player->rdm, fields[101], MAX_STR - 1);
    strncpy(player->rwb, fields[102], MAX_STR - 1);
    strncpy(player->lb, fields[103], MAX_STR - 1);
    strncpy(player->lcb, fields[104], MAX_STR - 1);
    strncpy(player->cb, fields[105], MAX_STR - 1);
    strncpy(player->rcb, fields[106], MAX_STR - 1);
    strncpy(player->rb, fields[107], MAX_STR - 1);
    strncpy(player->gk, fields[108], MAX_STR - 1);
    strncpy(player->player_face_url, fields[109], MAX_STR - 1);
}

void build_index_from_csv(FILE *bin, const char *csv_filename) {
    FILE *csv = fopen(csv_filename, "r");
    if (csv == NULL) {
        perror("fopen csv");
        exit(1);
    }
    char line[BUFFER_SIZE * 4];
    char *fields[110];
    fgets(line, sizeof(line), csv);
    int records = 0;

    while (fgets(line, sizeof(line), csv)) {
        //agregar al indexador cada linea valida.
        line[strcspn(line, "\n")] = 0; 
        if (strlen(line) == 0) continue;
        int count = parse_csv_line(line, fields);
        if (count < 109) {
            continue
        }
        Player player;
        assign_fields_to_player(&player, fields);
        long offset = ftell(bin);
        if (fwrite(&player, sizeof(Player), 1, bin) != 1) {
            perror("fwrite");
            exit(1);
        }
        add_to_hash(player.short_name, offset);
        if(records%100000==0){
            printf("%d",records);
        }
        records++;
    }
    printf("Total records processed: %d\n", records);
    fclose(csv);
}

void build_index_from_bin(FILE *bin) {
    Player player;
    long offset = 0;
    int records = 0;
    while (fread(&player, sizeof(Player), 1, bin) == 1) {
        add_to_hash(player.short_name, offset);
        offset = ftell(bin);
        records++;
    }
    printf("Total records indexed from bin: %d\n", records);
}
//salida a peticiones de busqueda
char *format_player(const Player *player) {
    char *buf = malloc(BUFFER_SIZE);
    if (buf == NULL) return NULL;
    snprintf(buf, BUFFER_SIZE, "Player: %s (%s), Overall: %d, Club: %s, Nationality: %s\n",player->short_name, player->long_name, player->overall, player->club_name, player->nationality_name);
    return buf;
}
//buscar
void handle_search(int sock, FILE *bin, char *key) {
    unsigned long h = hash(key);
    Node *node = hash_table[h];
    char response[BUFFER_SIZE * 10] = {0};
    int found = 0;
    while (node) {
        fseek(bin, node->offset, SEEK_SET);
        Player player;
        if (fread(&player, sizeof(Player), 1, bin) == 1) {
            if (strcmp(player.short_name, key) == 0) {
                char *fmt = format_player(&player);
                strncat(response, fmt, sizeof(response) - strlen(response) - 1);
                free(fmt);
                found++;
            }
        }
        node = node->next;
    }
    if (found == 0) {
        strcpy(response, "No players found.\n");
    }
    int len = strlen(response);
    send(sock, &len, sizeof(int), 0);
    send(sock, response, len, 0);
}
//escribe
void handle_write(int sock, FILE *bin) {
    Player player;
    if (recv(sock, &player, sizeof(Player), 0) != sizeof(Player)) {
        return;
    }
    fseek(bin, 0, SEEK_END);
    long offset = ftell(bin);
    if (fwrite(&player, sizeof(Player), 1, bin) != 1) {
        return;
    }
    add_to_hash(player.short_name, offset);
    char msg[] = "Record written.\n";
    int len = strlen(msg);
    send(sock, &len, sizeof(int), 0);
    send(sock, msg, len, 0);
}
//buscar por numero
void handle_read_record(int sock, FILE *bin, int rec_num) {
    long offset = (long)rec_num * sizeof(Player);
    fseek(bin, offset, SEEK_SET);
    Player player;
    if (fread(&player, sizeof(Player), 1, bin) != 1) {
        char msg[] = "NA\n";
        int len = strlen(msg);
        send(sock, &len, sizeof(int), 0);
        send(sock, msg, len, 0);
        return;
    }
    char *fmt = format_player(&player);
    int len = strlen(fmt);
    send(sock, &len, sizeof(int), 0);
    send(sock, fmt, len, 0);
    free(fmt);
}

int main() {
    memset(hash_table, 0, sizeof(hash_table));
    //archivo .bin 
    FILE *bin = fopen("/mnt/f/players.bin", "rb+"); 
    if (bin == NULL) {
        bin = fopen("/mnt/f/players.bin", "wb+");
        if (bin == NULL) {
            perror("fopen bin");
            exit(1);
        }
        printf("Building index from CSV...\n");
        build_index_from_csv(bin, "players.csv");
    } else {
        printf("Building index from existing bin...\n");
        build_index_from_bin(bin);
    }

    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(1);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);
    //esperar a cliente
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(1);
        }

        int choice;
        while (recv(new_socket, &choice, sizeof(int), 0) == sizeof(int)) {
            //recv recibe la accion requerida
            if (choice == 1) {
                char key[MAX_STR];
                recv(new_socket, key, MAX_STR, 0);
                printf("Buscando a: %s\n", key);
                handle_search(new_socket, bin, key);
            } else if (choice == 2) {
                handle_write(new_socket, bin);
            } else if (choice == 3) {
                int rec_num;
                recv(new_socket, &rec_num, sizeof(int), 0);
                printf("Buscando por numero: %d\n", rec_num);
                handle_read_record(new_socket, bin, rec_num);
            } else if (choice == 4) {
                break;
            }
        }
        close(new_socket);
    }

    free_hash();
    fclose(bin);
    return 0;
}