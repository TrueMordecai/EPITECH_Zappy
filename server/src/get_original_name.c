/*
** EPITECH PROJECT, 2022
** B-YEP-410-NAN-4-1-zappy-emile.ettel
** File description:
** get_original_name
*/

#include "server.h"

static char *const NAME[] = {
    "Peppa_Pig", "Bender", "Larry", "Angelica", "Jhonny_Bravo",
    "Felix_The_Cat", "Arthur", "Daffy_Duck", "Ed", "Stewie",
    "Popeye", "Phineas", "Muscle_Man", "Rigby", "Mordecai",
    "Garnet", "Betty_Boop", "Korra", "Bart", "Harley_Quinn",
    "Spiderman", "Emile", "Mathias", "Covidman", "Le_S",
    "???", "#UwU#", "Comte_Harebourg", "Rick", "Micron",
    "Zinedine", "SAKEEEN!!", "Dr.Doofenshmirtz", "The Rock", "Sardo",
    "EricCartman", "Kc_Deku", "SUPLINK", "Liza_Monet", "Captain_Morgan",
    "Steven_Universe", "Kralamoure_Géant", "Sponge_Bob", "Tom", "Giga_Chad",
    "Anal_Genocide", "Arko", "Mia_Khalifa", "Mireille_Matué", "AlCapone",
    "Rambo", "David_Assezlouche", "Daddy_Issue",
    "Samira_On_Caffeine", "U_W0T_M8T3", "Fuck_Belvet",
    "Simic_Lover", "La_Grosse_Jambe_De_Shrek", "Gitano", "Moulaga",
    "JazzTheGooze", "Kendrick_Lamar", "Batman", "GoD", "GotaGa",
    "Jean_Lasalle", "Poutine", "Poulidor", "DatBoi", "Zyzz",
    "Ricardo_Milos", "ayyLmao", "MoonMan", "Risitas", "Pillon_Magique",
    "Dr.Juiph", "L'illuminax", "Guigui_Georges", "ahmed", "Mr.Fouch",
    "BasedBoi", "Kekistan_Villager", "smile.jpg", "KaarisLeChef", "Jean"
};

char *get_original_name(my_server_t *serv)
{
    char *name = NAME[rand() % 85];
    my_client_t *client = serv->clients;

    while (client) {
        if (!strcmp(client->name, name)) {
            name = NAME[rand() % 85];
            client = serv->clients;
        } else
            client = client->next;
    }
    return name;
}
