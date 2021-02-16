# Análise da função fill 


```c
void *fill(void *nr)
{
    while (1)
    {
        //pthread_mutex_lock(&mut);
        if (pos >= npos)
        {
            //pthread_mutex_unlock(&mut);
            return NULL;
        }
        //a posição pos tem de ter o mesmo val 
        buf[pos] = val;
        pos++;          //1 
        val++;          //2
        //pthread_mutex_unlock(&mut);
        *(int *)nr += 1;
    }
}
```

O buf[pos] = val, necessárimente diz que pos deve ser igual a val. Ou seja, foram incrementados ao mesmo tempo. 
Se pos != val para um determinado buf[pos], isto quer dizer que alguma thread foi executada entre os passos 1 e 2. 
Por o mecanismo erro foi acionado: 

```c
void *verify(void *arg)
{
    int k;
    for (k = 0; k < npos; k++)
        if (buf[k] != k)
            // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
    return NULL;
}

```

Ele verifica a condição de que buf[pos] == val. 
