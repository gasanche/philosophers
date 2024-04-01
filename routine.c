void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->left);
    print_status(philo, "has taken a fork", 0);
    if (philo->agora->n_phils == 1)
    {
      print_status(philo, "died", 1);
      pthread_mutex_unlock(&philo->left);
      return ;
    }
    pthread_mutex_lock(&philo->right);
    print_status(philo, "has taken a fork", 0);
    pthread_mutex_lock(&philo->died);
    philo->died = time_passed(philo->agora->start) + philo->agora->ttdie;
    pthread_mutex_unlock(&philo->died);
    if (philo->lst_eat != 0) //amigo dannyel del pasado, parsea mejor lolololol
        print_status(philo, "is eating", 0);
    //hacer una funcion del tiempo de comida
    //hacer una funcion del tiempo de sueño
    pthread_mutex_unlock(&philo->left);
    pthread_mutex_unlock(&philo->right);
    if (philo->lst_eat != 0) //amigo dannyel del pasado, parsea mejor lolololol
        print_status(philo, "is sleeping", 0);
    sleeping(philo->agora->ttsleep, philo->agora);
    if (philo->lst_eat != 0)
        print_status(philo, "is thinking", 0);
    }

void sleeping(int ttsleep, t_agora *agora)
{

}

int food_supervisor(t_agora *agora)
{
    int i;
    int aux;

    i = 0;
    pthread_mutex_lock(&agora->end_ph);
    aux = agora->min_meals;
    pthread_mutex_unlock(&agora->end_ph);
    if (aux == agora->n_phils)
    {
        pthread_mutex_lock(&agora->end);
        agora->end = 1;
        pthread_mutex_unlock(&agora->end);
        return (1);
    }
    return (0);
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
            print_status(&agora->philo[i], "died", 1);
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