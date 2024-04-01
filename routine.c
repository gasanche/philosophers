void eat()
{

}

void sleep()
{

}

int food_supervisor(t_agora *agora)
{

}

long int    time_passed(struct timeval start)
{
    struct timeval  end;
    suseconds_t time;

    gettimeofday(&end, NULL);
    time = (end.tv_usec / 1000 + end.tv_sec * 1000)
            - (start.tv_usec / 1000 + start.tv_sec * 1000);
    return (time);
}

void    sargent(t_agora *agora)
{
    int i;
    int time;

    i = 0;
    while (i < agora->n_phils)
    {
        pthread_mutex_lock(&agora->philo[i].died);
        time = agora->philo[i].dead;
        pthread_mutex_unlock(&agora->philo[i].died);
        if (time_passed(agora->start) > time)
        {
            pthread_mutex_lock(&agora->end);
            agora->end = 1;
            pthread_mutex_unlock(&agora->end);
            //show status
            break ;
        }
        if (agora->min_meals > 0 && food_supervisor(agora))
            break ;
        i++;
        if (i == agora->n_phils)
            i = 0;
        usleep(60); //hay que comprobarlo
    }
}

void routine(void *philo)
{

}