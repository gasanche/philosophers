//header lol

void    print_status(t_philo *philo, char *str, int status)
{
    int time;
    int the_end;

    the_end = 0;
    pthread_mutex_lock(&philo->agora->print); //probar estos mutex raros
    pthread_mutex_lock(&philo->agora->end); //cosas raras del dannyel del pasado. se pueden borrar?
    the_end = philo->agora->ended;
    pthread_mutex_unlock(&philo->agora->end);
    time = time_passed(philo->agora->start);
    if (the_end != 1 || status == 1)
        printf("%d %d %s\n", time, philo->n_philo + 1, str);
    pthread_mutex_unlock(&philo->agora->print);
}