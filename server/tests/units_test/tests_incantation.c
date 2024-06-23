/*
** EPITECH PROJECT, 2024
** server
** File description:
** tests_incantation
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "commands_ai.h"

static char **get_args(void)
{
    srand(time(NULL));
    char tmp[512];

    int port = (rand() % 5000) + 1000;
    snprintf(tmp, 512, "./zappy_server -p %i -x 10 -y 10 -n team1 team2 -c 2 -f 100", port);

    return my_str_to_word_array(tmp, " ");
}

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}


static int *add_players_on_incantation(int num, int *players)
{
    int *save = players;
    int size = 0;

    if (players == NULL) {
        players = malloc(sizeof(int) * 2);
        players[0] = num;
        players[1] = -1;
        return players;
    }
    for (; players[size] != -1; size++);
    players = realloc(players, sizeof(int) * (size + 2));
    if (players == NULL)
        return save;
    players[size] = num;
    players[size + 1] = -1;
    return players;
}

Test(incantation_command, incantation_command_no_object)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    tile->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);


    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client2->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "ko\n"), 0);
    delete_server(server_s);
}

static void open_write_in_file(void)
{
    int fd = open("test.txt", O_CREAT | O_WRONLY, 0666);
    if (fd == -1)
        cr_assert_fail("error open\n");

    write(fd, "Hello\n", 6);
    close(fd);
}

static void delete_file(void)
{
    remove("test.txt");
}

Test(incantation_command, incantation_main_player_dd, redirect_all_stdout)
{
    server_t *server_s = create_server(get_args());

    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    (void)client1;
    tile->object.linemate = 0;
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);
    

    open_write_in_file();
    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        int fd = open("test.txt", O_RDONLY);
        if (fd == -1)
            cr_assert_fail("error open\n");
        tmp->fd = fd;
        tmp->buff_out = NULL;
    }
    read_ai_list(server_s, server_s->ai_clients);
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);
    write_ai_list(server_s, server_s->ai_clients);
    incantation_end(server_s, incantation);
    delete_server(server_s);
    delete_file();
}

Test(manage_pending_client, manage_pending_client)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);

    client_t *client1 = create_client(1);
    client_t *client2 = create_client(2);

    add_client_to_list(server_s->pending_clients, client1);
    add_client_to_list(server_s->pending_clients, client2);

    client1->buffer_in = my_strdup("team1\n");
    client2->buffer_in = my_strdup("GRAPHIC\n");

    manage_pending_client(server_s, client1);
    manage_pending_client(server_s, client2);
    delete_server(server_s);
}

Test(exec_ai_list, test)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    add_client_ai_to_list(server_s->ai_clients, client1);
    client1->buff_in = my_strdup("Incantation\n");
    exec_ai_list(server_s);
    delete_server(server_s);
}

Test(exec_ai_list, test2)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});

    client1->TTL = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);
    client1->buff_in = my_strdup("Incantation\n");
    exec_ai_list(server_s);
    delete_server(server_s);
}

Test(exec_ai_list, test3)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    int fd_devnull = open("/dev/null", O_WRONLY);
    if (fd_devnull == -1)
        cr_assert_fail("error open\n");
    init_game(server_s);
    client_ai_t *client1 = create_client_ai(fd_devnull, "team1", (position_t){0, 0, NORTH});

    client1->TTL = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);
    client1->buff_in = my_strdup("Connect_nbr\n");
    exec_ai_list(server_s);
    write_ai_list(server_s, server_s->ai_clients);
    delete_server(server_s);
    close(fd_devnull);
}

Test(incantation_end, incantation_end)
{
    server_t *server_s = create_server(get_args());

    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team2", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team3", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team4", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team5", (position_t){0, 0, SOUTH});

    tile->object.linemate = 1;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "Current level: 2\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "Current level: 2\n"), 0);
    delete_server(server_s);
}

Test(incantation_end, incantation_end_max)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team1", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team1", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client6 = create_client_ai(6, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client7 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});

    tile->object.linemate = 10;
    tile->object.deraumere = 10;
    tile->object.sibur = 10;
    tile->object.mendiane = 10;
    tile->object.phiras = 10;
    tile->object.thystame = 10;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);
    add_client_ai_to_list(server_s->ai_clients, client6);
    add_client_ai_to_list(server_s->ai_clients, client7);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
        tmp->level = 7;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);
    incantation->players = add_players_on_incantation(5, incantation->players);
    incantation->players = add_players_on_incantation(6, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client6->buff_out, "Current level: 8\n"), 0);
    cr_assert_eq(my_strcmp(client7->buff_out, "Current level: 8\n"), 0);
    delete_server(server_s);
}

Test(incantation_end, incantation_end_player_died)
{
    server_t *server_s = create_server(get_args());
    if (server_s == NULL)
        cr_assert_fail("error create_server\n");
    init_game(server_s);
    tile_t *tile = &server_s->world->tiles[0];
    client_ai_t *client1 = create_client_ai(1, "team1", (position_t){0, 0, NORTH});
    client_ai_t *client2 = create_client_ai(2, "team1", (position_t){0, 0, WEST});
    client_ai_t *client3 = create_client_ai(3, "team1", (position_t){0, 0, EAST});
    client_ai_t *client4 = create_client_ai(4, "team1", (position_t){0, 0, EAST});
    client_ai_t *client5 = create_client_ai(5, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client6 = create_client_ai(6, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client7 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});
    client_ai_t *client8 = create_client_ai(7, "team1", (position_t){0, 0, SOUTH});

    tile->object.linemate = 10;
    tile->object.deraumere = 10;
    tile->object.sibur = 10;
    tile->object.mendiane = 10;
    tile->object.phiras = 10;
    tile->object.thystame = 10;
    add_client_ai_to_list(server_s->ai_clients, client1);
    add_client_ai_to_list(server_s->ai_clients, client2);
    add_client_ai_to_list(server_s->ai_clients, client3);
    add_client_ai_to_list(server_s->ai_clients, client4);
    add_client_ai_to_list(server_s->ai_clients, client5);
    add_client_ai_to_list(server_s->ai_clients, client6);
    add_client_ai_to_list(server_s->ai_clients, client7);
    add_client_ai_to_list(server_s->ai_clients, client8);

    for (client_ai_t *tmp = server_s->ai_clients->head; tmp != NULL; tmp = tmp->next) {
        tmp->buff_out = NULL;
        tmp->level = 7;
    }
    incantation_t *incantation = create_incantation(0, 1, (position_t){0, 0, NORTH});
    incantation->players = add_players_on_incantation(1, incantation->players);
    incantation->players = add_players_on_incantation(2, incantation->players);
    incantation->players = add_players_on_incantation(3, incantation->players);
    incantation->players = add_players_on_incantation(4, incantation->players);
    incantation->players = add_players_on_incantation(55, incantation->players);
    incantation->players = add_players_on_incantation(15, incantation->players);

    incantation_end(server_s, incantation);
    cr_assert_eq(my_strcmp(client1->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client2->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client3->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client4->buff_out, "ko\n"), 0);
    cr_assert_eq(my_strcmp(client5->buff_out, "ko\n"), 0);
    delete_server(server_s);
}