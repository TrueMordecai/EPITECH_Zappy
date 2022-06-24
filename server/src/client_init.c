/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** client_init
*/

#include "server.h"

static char *const NAME[] = {"Peppa_Pig", "Bender", "Larry", "Angelica", "Jhonny_Bravo", // 5
                             "Felix_The_Cat", "Arthur", "Daffy_Duck", "Ed", "Stewie", // 5
                             "Popeye", "Phineas", "Muscle_Man", "Rigby", "Mordecai", // 5
                             "Garnet", "Betty_Boop", "Korra", "Bart", "Harley_Quinn", // 5
                             "Spiderman", "Emile", "Mathias", "Covidman", "Le_S", // 5
                             "???", "#UwU#", "Comte_Harebourg", "Rick", "Micron", // 5
                             "Zinedine", "SAKEEEN!!", "Dr.Doofenshmirtz", "The Rock", "Sardo", // 5
                             "EricCartman", "Kc_Deku", "SUPLINK", "Liza_Monet", "Captain_Morgan", // 5
                             "Steven_Universe", "Kralamoure_Géant", "Sponge_Bob", "Tom", "Giga_Chad", // 5
                             "Anal_Genocide", "Arko", "Mia_Khalifa", "Mireille_Matué", "Alkapote", // 5
                             "BibleBlack_Lover", "David_Assezlouche", "Daddy_Issue", "Samira_On_Cocaine", "U_W0T_M8T3", // 5
                             "Fuck_Belvet", "Simic_Lover", "La_Grosse_Jambe_De_Shrek", "Gitano", "Moulaga", // 5
                             "JazzTheGooze", "Kendrick_Lamar", "Batman", "GoD", "GotaGa", // 5
                             "Jean_Lasalle", "Poutine", "Poulidor", "DatBoi", "Zyzz", // 5
                             "Ricardo_Milos", "ayyLmao", "MoonMan", "Risitas", "Pillon_Magique",
                            "Dr.Juiph", "L'illuminax", "Guigui_Georges", "ahmed", "Mr.Fouch", //5
                             "BasedBoi", "Kekistan_Villager", "smile.jpg", "KaarisLeChef", "Le_Racisme"}; // 5

void add_client(my_server_t *serv, my_client_t *client)
{
    my_client_t *tail = serv->clients;

    client->next = NULL;
    if (serv->clients == NULL) {
        serv->clients = client;
        return;
    }
    while (tail->next)
        tail = tail->next;
    tail->next = client;
    tail->next->next = NULL;
}

void del_client(my_server_t *serv, int fd)
{
    my_client_t *tmp = serv->clients;
    my_client_t *rem = NULL;

    if (serv->clients->fd == fd) {
        rem = serv->clients;
        serv->clients = serv->clients->next;
        decon_client(rem);
        if (fd > 0)
            FD_CLR(fd, &serv->fds);
        return;
    }
    if (serv->clients == NULL)
        return;
    for (; tmp->next && tmp->next->fd != fd; tmp = tmp->next);
    if (tmp->next == NULL)
        return;
    rem = tmp->next;
    tmp->next = tmp->next->next;
    decon_client(rem);
    if (fd > 0)
        FD_CLR(fd, &serv->fds);
}

void decon_client(my_client_t *client)
{
    if (client->fd > 0)
        close(client->fd);
    if (client->team_name)
        free(client->team_name);
    for (uint i = 0; i < client->message_queue_size; i++)
        free(client->message_queue[i]);
    free(client->message_queue);
    free(client);
}

char **init_message_queue(void)
{
    char **ret = malloc(sizeof(char*) * 11);

    for (uint i = 0; i < 11; i++)
        ret[i] = NULL;
    return ret;
}

my_client_t *make_client(int fd, int x, int y)
{
    my_client_t *client = malloc(sizeof(my_client_t));

    client->fd = fd;
    client->team_name = NULL;
    client->level = 1;
    client->x = rand() % x;
    client->y = rand() % y;
    client->x = 1; // TEMP
    client->y = 1; // TEMP
    client->direction = rand() % 4;
    client->direction = 2; // TEMP
    client->name = strdup(NAME[rand() % 86]);
    client->inventory = generate_inventory();
    client->food = 1260;
    client->cooldown = 0;
    client->message_queue = init_message_queue();
    client->message_queue_size = 0;
    client->next = NULL;
    client->dead = false;
    client->func = NULL;
    client->cur = NULL;
    
    dprintf(fd, "WELCOME\n");
    return client;
}
