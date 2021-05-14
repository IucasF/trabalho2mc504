#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_CLIENTES 10
#define N_BARBEIROS 2
#define N_CADEIRAS 5


sem_t sem_cadeiras;
sem_t sem_cad_barbeiro[N_BARBEIROS];
sem_t sem_cabelo_cortado[N_BARBEIROS];
sem_t sem_cliente_cadeira[N_BARBEIROS];

sem_t sem_escreve_painel, sem_le_painel;

int painel;
//se esta em 0, cabeleireiro esta dormindo
int cabeleireiro[2] = {0,0};
int cadeiras[5] = {0,0,0,0,0};
int clienteNovo = 0;

void* escrevePainel(){
  printf("                      BARBEARIA                 \n");

  if(cabeleireiro[0] == 0){
    printf("   /                                           zzz");
  }
  else{
    printf("                                               %d", cabeleireiro[0]);
  }

  if(cabeleireiro[1] == 0){
    printf("  zzz \n");
  }
  else{
    printf("   %d\n",cabeleireiro[1]);
  }


  if(clienteNovo != 0){
    printf("%d", clienteNovo);
  }


  if(cadeiras[0] == 0){
    printf(" |  ");
  }
  else{
    printf(" | %d  ",cadeiras[0]);
  }
  if(cadeiras[1] == 0){
    printf("      ");
  }
  else{
    printf("    %d  ",cadeiras[1]);
  }
  if(cadeiras[2] == 0){
    printf("      ");
  }
  else{
    printf("    %d  ",cadeiras[2]);
  }
  if(cadeiras[3] == 0){
    printf("      ");
  }
  else{
    printf("    %d  ",cadeiras[3]);
  }
  if(cadeiras[4] == 0){
    printf("      \n");
  }
  else{
    printf("    %d      \n",cadeiras[4]);
  }

  printf("\  CC00  CC01  CC02  CC03  CC04\n");
  printf("\n\n");


}

void* f_barbeiro(void *v) {
  int id = *(int*)v;

  while(1) {
    sem_wait(&sem_escreve_painel);
    painel = id;
    sem_post(&sem_le_painel);
    sem_wait(&sem_cliente_cadeira[id]);
    sem_post(&sem_cabelo_cortado[id]);

    sem_wait(&sem_escreve_painel);
    escrevePainel();
    cabeleireiro[id] = 0;
    sem_post(&sem_escreve_painel);
    sleep(random()%3);
  }
  return NULL;
}

void* f_cliente(void* v) {
  int id = *(int*) v;
  int minha_cadeira;



  sleep(random()%3);
  if (sem_trywait(&sem_cadeiras) == 0) {

    sem_wait(&sem_escreve_painel);
    clienteNovo = id;
    escrevePainel();
    sem_post(&sem_escreve_painel);

    int cadeira;
    int i = 0;

    while(cadeiras[i] != 0 && i < 5){
      i++;
    }

    clienteNovo = 0;
    cadeiras[i] = id;
    sem_wait(&sem_escreve_painel);
    escrevePainel();
    sem_post(&sem_escreve_painel);


    sem_wait(&sem_le_painel);
    minha_cadeira = painel;
    sem_post(&sem_escreve_painel);
    sem_wait(&sem_cad_barbeiro[minha_cadeira]);
    cabeleireiro[minha_cadeira] = id;
    cadeiras[i] = 0;
    escrevePainel();
    sem_post(&sem_cliente_cadeira[minha_cadeira]);
    sem_post(&sem_cadeiras);
    sem_wait(&sem_cabelo_cortado[minha_cadeira]);
    sem_post(&sem_cad_barbeiro[minha_cadeira]);

    sem_wait(&sem_escreve_painel);
    escrevePainel();
    sem_post(&sem_escreve_painel);
  } else{
    sem_wait(&sem_escreve_painel);
    clienteNovo = id;
    escrevePainel();
    clienteNovo = 0;
    escrevePainel();
    sem_post(&sem_escreve_painel);
    }
  return NULL;
}


int main(){
  //criar threads para clientes e barbeiros
  pthread_t thr_clientes[N_CLIENTES], thr_barbeiros[N_BARBEIROS];
  int i, id_cl[N_CLIENTES], id_bar[N_BARBEIROS];
  //iniciar os semáforos das cadeiras dos clientes e os semáforos para escrever e ler o painel
  sem_init(&sem_cadeiras, 0, 6);
  sem_init(&sem_escreve_painel, 0, 1);
  sem_init(&sem_le_painel, 0, 0);


  //iniciar os semáforos dos barbeiros
  for (i = 0; i < N_BARBEIROS; i++) {
    sem_init(&sem_cad_barbeiro[i], 0, 1);
    sem_init(&sem_cliente_cadeira[i], 0, 0);
    sem_init(&sem_cabelo_cortado[i], 0, 0);
  }

  //criar as threads dos clientes
  for (i = 0; i < N_CLIENTES; i++) {
    id_cl[i] = i;
    pthread_create(&thr_clientes[i], NULL, f_cliente, (void*) &id_cl[i]);
  }

  //criar as threads dos barbeiros
  for (i = 0; i < N_BARBEIROS; i++) {
    id_bar[i] = i;
    pthread_create(&thr_barbeiros[i], NULL, f_barbeiro, (void*) &id_bar[i]);
  }

  for (i = 0; i < N_CLIENTES; i++)
    pthread_join(thr_clientes[i], NULL);


}
